/*
 * File:   system_initialize.c
 * Author: M91406
 *
 * Created on November 12, 2020, 10:33 AM
 */

#include "hal.h"
#include "system.h"

/**
 * 
 * @addtogroup device-start-up
 * @{
 */
/***********************************************************************************
 * @fn volatile uint16_t SYSTEM_Initialize(void) 
 * @brief  Initializes essential chip resources and application task
 * @param  (none)
 * @return unsigned integer (0=failure, 1=success)
 * 
 * <b>Description</b>
 * The SYSTEM_Initialize function covers the initialization of essential chip 
 * resources such as main oscillator, auxiliary oscillator, watchdog timer and
 * general purpose I/Os (GPIO).
 * 
 * <p><b>Example:</b></p>
 *
 * <code>
 * ADD_CODE_EXAMPLE_HERE
 * </code>
 *
 * <p><b>Remarks:</b></p>
 * ADD_REMARKS_HERE
 *
 **********************************************************************************/
volatile uint16_t SYSTEM_Initialize(void) 
{
    volatile uint16_t retval=1;
	
    retval &= sysFosc_Initialize();        // Set up system oscillator for 100 MIPS operation
    retval &= sysAclk_Initialize();        // Set up Auxiliary PLL for 500 MHz (source clock to PWM module)
    retval &= sysOsTimer_Initialize();     // Set up Timer1 as scheduler time base (see MAIN_EXECUTION_PERIOD for details)
    retval &= sysGpio_Initialize();        // Initialize common device GPIOs
    
	return(retval);

}

/***********************************************************************************
 * @fn uint16_t sysUserTasks_Initialize
 * @brief  Initializes the user-defined tasks and chip resources
 * @param  (none)
 * @return unsigned integer (0=failure, 1=success)
 * 
 * <b>Description</b>
 * ADD_DESCRIPTION_HERE
 *
 * <p><b>Example:</b></p>
 *
 * <code>
 * ADD_CODE_EXAMPLE_HERE
 * </code>
 *
 * <p><b>Remarks:</b></p>
 * ADD_REMARKS_HERE
 *
 **********************************************************************************/
volatile uint16_t sysUserTasks_Initialize(void) {

    volatile uint16_t retval=1;
	
    retval &= init_opa(); // Initialize op-amp #2 used to drive the reference voltage for current sense amplifiers
    
    retval &= init_dac_module();  // Initialize DAC module
    retval &= init_dac_channel(1); // Initialize DAC #1 used to generate the reference voltage for current sense amplifiers
    retval &= init_dac_enable(); // Enable DAC setting the reference for current sense amplifiers

    // Initialize software modules
    retval &= appPowerSupply_Initialize(); // Initialize BUCK converter object and state machine
    retval &= appFaultMonitor_Initialize(); // Initialize fault objects and fault handler task

	return(retval);

}


/**@}*/