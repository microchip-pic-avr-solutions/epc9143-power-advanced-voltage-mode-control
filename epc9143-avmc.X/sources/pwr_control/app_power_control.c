/**
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms, you may use Microchip software
 *  and any derivatives exclusively with Microchip products. You're responsible
 *  for complying with 3rd party license terms applicable to your use of 3rd
 *  party software (including open source software) that may accompany Microchip
 *  software.
 *
 *  SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 *  APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 *  MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
 *  HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
 *  THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 *  CLAIMS RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY,
 *  YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 *  @file    app_power_control.c
 *  @brief   This file contains APIs to for the power control
 *
 *  @note
 *  Microchip Technology Inc. has followed development methods required by
 *  IEC-60730 and performed extensive validation and static testing to ensure
 *  that the code operates as intended. Any modification to the code can
 *  invalidate the results of Microchip's validation and testing.
 *
 */
/*
 * File:   app_power_control.c
 * Author: M91406
 *
 * Created on March 12, 2020, 11:55 AM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "config/hal.h" // include hardware abstraction layer declarations
#include "app_power_control.h" // include applicaiton layer power control header file

#include "./devices/dev_buck_converter.h" // include buck converter device
#include "fault_handler/app_faults_monitor.h" // include fault monitor application object declarations


/**************************************************************************************************
 * @ingroup app-layer-power-control-properties-public
 * @var volatile struct BUCK_POWER_CONTROLLER_s  buck
 * @brief Global data object for a BUCK CONVERTER 
 * 
 * @details
 * The 'buck' data object holds all status, control and monitoring values of the BUCK power 
 * controller. The BUCK_POWER_CONTROLLER_s data structure is defined in dev_buck_converter.h.
 * Please refer to the comments on top of this file for further information.
 *  
 **************************************************************************************************/
volatile struct BUCK_POWER_CONTROLLER_s  buck;


/* PRIVATE FUNCTION PROTOTYPES */

extern volatile uint16_t appPowerSupply_ConverterObjectInitialize(void);
extern volatile uint16_t appPowerSupply_ControllerInitialize(void);
extern volatile uint16_t appPowerSupply_PeripheralsInitialize(void);

void __attribute__((always_inline)) appPowerSupply_CurrentBalancing(void); 


/* *************************************************************************************************
 * PUBLIC FUNCTIONS
 * ************************************************************************************************/


/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	volatile uint16_t appPowerSupply_Execute(void)
 * @brief This is the top-level function call triggering the most recent state 
 * machine of all associated power supply controllers
 * @return 0=failure
 * @return 1=success
 * 
 * @details 
 * After initialization, the proprietary user code has to call this function 
 * on a deterministic, constant time base. In each execution step this function
 * will call the power control state machines of each supported/included power
 * supply unit. 
 * 
 *********************************************************************************/

volatile uint16_t appPowerSupply_Execute(void)
{ 
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    volatile uint16_t i_dummy=0;

    // Capture most recent samples
    buck.data.v_in = BUCK_VIN_ADCBUF;
    buck.data.i_sns[0] = BUCK_ISNS1_ADCBUF;
    buck.data.i_sns[1] = BUCK_ISNS2_ADCBUF;
    
    // Accumulate phase currents
    for (_i=0; _i<buck.set_values.no_of_phases; _i++) 
    { i_dummy += buck.data.i_sns[_i]; }
    buck.data.i_out = i_dummy; // Set output current value

    // Execute buck converter state machine
    retval &= drv_BuckConverter_Execute(&buck);
    
    // Execute slower, advanced control options
//    appPowerSupply_CurrentBalancing();

    // Buck regulation error is only active while controller is running
    // and while being tied to a valid reference
    if((buck.state_id.bits.opstate_id >= BUCK_OPSTATE_RAMPUP) && 
       (buck.state_id.bits.substate_id >= BUCK_OPSTATE_V_RAMP_UP))
    {
        fltobj_BuckRegErr.ReferenceObject.ptrObject = buck.v_loop.controller->Ports.ptrControlReference;
        #if (PLANT_MEASUREMENT == false)
        fltobj_BuckRegErr.Status.bits.Enabled = buck.v_loop.controller->status.bits.enabled;
        #endif
    }
    else 
    {
        fltobj_BuckRegErr.Status.bits.Enabled = false;
    }
    
    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	volatile uint16_t appPowerSupply_Initialize(void)
 * @brief  Calls the application layer power controller initialization
 * @return 0=failure
 * @return 1=success
 * 
 * @details 
 * The power control application layer is the proprietary user code layer
 * used to tailor the generic power converter device driver to the specific 
 * hardware of this design. The initialization routine covers three levels
 * 
 * - Converter Object Configuration
 * - Controller Configuration
 * - Peripheral Set Configuration
 * - Interrupt Vector Configuration
 * 
 * Once all modules have been configured successfully, the power converter 
 * object is started with control loops and PWM outputs disabled. However, 
 * the PWM module will start triggering the ADC to allow the standby monitoring
 * of system conditions to allow the firmware to decide if it is safe to start
 * up the power converter.
 * 
 *********************************************************************************/

volatile uint16_t appPowerSupply_Initialize(void)
{ 
    volatile uint16_t retval=1;

    // Run initialization sequence
    retval &= appPowerSupply_ConverterObjectInitialize();
    retval &= appPowerSupply_ControllerInitialize();
    retval &= appPowerSupply_PeripheralsInitialize();

    // Initialize Control Interrupt
    _BUCK_VLOOP_ISR_IP = BUCK_VOUT_ISR_PRIORITY;
    _BUCK_VLOOP_ISR_IF = 0;
    _BUCK_VLOOP_ISR_IE = true;
    
    // Start power supply engine
    retval &= appPowerSupply_Start();
    
    // Enable Buck Converter
    buck.status.bits.enabled = true;
    
    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	volatile uint16_t appPowerSupply_Start(void)
 * @brief  This function calls the buck converter device driver function starting the power supply 
 * @return 0=failure
 * @return 1=success
 *  
 * @details 
 *  This function exposes the Power Converter Start function of the device driver.
 *********************************************************************************/

volatile uint16_t appPowerSupply_Start(void)
{
    volatile uint16_t retval=1;

    retval &= drv_BuckConverter_Start(&buck); // Start PWM with outputs disabled to start ADC triggering

    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	volatile uint16_t appPowerSupply_Stop(void)
 * @brief This function calls the buck converter device driver function stopping the power supply 
 * @return 0=failure
 * @return 1=success
 *  
 * @details
 *  This function exposes the Power Converter Stop function of the device driver.
 * 
 * @note
 *  The STOP function terminates the state machine and all peripherals used by
 *  the power controller. This includes the PWM and ADC peripheral modules and 
 *  will therefore also stop all data acquisition. 
 *  If you are trying to stop the power supply but keep its state machine and
 *  data acquisition running, use the SUSPEND function instead
 * 
 *********************************************************************************/

volatile uint16_t appPowerSupply_Stop(void)
{
    volatile uint16_t retval=1;

    retval &= drv_BuckConverter_Stop(&buck); // Shut down all power supply peripherals and data objects

    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	   volatile uint16_t appPowerSupply_Suspend(void)
 * @brief  This function stops the power supply operation
 * @return 0=failure
 * @return 1=success
 *  
 * @details
 *  The SUSPEND function stops the power supply operation but keep its state machine
 *  and data acquisition running.
 *********************************************************************************/

volatile uint16_t appPowerSupply_Suspend(void)
{ 
    volatile uint16_t retval=1;

    retval &= drv_BuckConverter_Suspend(&buck); // Shut down PWM immediately

    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-public
 * @fn	   volatile uint16_t appPowerSupply_Resume(void)
 * @brief  This function resumes the power supply operation
 * @return unsigned integer (0=failure, 1=success)
 *  
 * @details
 *  This function calls the buck converter device driver function recovering
 *  the power supply operation from a previously initiated shut-down.
 * 
 *********************************************************************************/

volatile uint16_t appPowerSupply_Resume(void)
{ 
    volatile uint16_t retval=0;

    retval &= drv_BuckConverter_Resume(&buck); // Shut down PWM immediately
    
    return(retval); 
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-private
 * @fn	void appPowerSupply_CurrentBalancing(void) 
 * @brief This function performs current balancing between the power supply phases
 * @return unsigned integer (0=failure, 1=success)
 *  
 * @details 
 * Current balancing in this design is performed on a 10 kHz frequency, triggered
 * by the general state machine execution period. In each step the current sense
 * feedback signals of each phase are compared. Phase #1 is considered to be the 
 * leading phase while all others are power multipliers. 
 * 
 * If the current sense feedback signal of phase #2 is lower than that of 
 * phase #1, a static duty ratio offset of one PWM time-base tick is added to 
 * the duty ratio of phase #2 forcing more current flowing through phase #2, 
 * effectively shifting current from phase #1 to phase #2. 
 * 
 * If the current sense feedback signal of phase #2 is higher than that of 
 * phase #1, the static duty ratio offset of phase #2 is reduced by one PWM 
 * time-base tick to force less current flowing through phase #2, effectively 
 * shifting current from phase #2 to phase #1. 
 * 
 * Over several current balancing cycles this offset will accumulate until the 
 * phase currents are balanced.
 * 
 * Additional noise-floor signal filters are used to ensure the current 
 * balancing does not respond to small differences in immediate ADC samples.
 * 
 * 
 *********************************************************************************/

inline void appPowerSupply_CurrentBalancing(void) 
{
    static int16_t offset=0;
    
    // Current balancing is only executed in nominal running mode
    if(buck.state_id.bits.opstate_id != BUCK_OPSTATE_ONLINE) 
        return;
    
    // if current in phase #1 is higher than phase current #2...
    if(buck.data.i_sns[0] > buck.data.i_sns[1]) 
    { // .. add 1 tick to phase #2 duty cycle
        offset = ((++offset>0x07) ? 0x07 : offset);
    }
    else 
    { // .. sub 1 tick from phase #2 duty cycle
        offset = ((--offset<0x00) ? 0x00 : offset);
    }

    buck.v_loop.controller->Ports.AltTarget.Offset = (uint16_t)offset;

}

// ____________________________
// end of file
