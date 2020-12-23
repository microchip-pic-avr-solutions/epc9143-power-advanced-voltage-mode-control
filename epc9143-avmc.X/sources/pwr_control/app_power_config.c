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
 * File:   app_power_config.c
 * Author: M91406
 *
 * Created on December 9, 2020, 5:01 PM
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "config/hal.h" // include hardware abstraction layer declarations
#include "app_power_control.h"
#include "./devices/dev_buck_converter.h" // include buck converter device

#include "./drivers/v_loop.h" // include voltage control loop object
#include "./drivers/v_loop_agc.h" // include voltage control loop adaptive gain control object

#include "fault_handler/app_fault_monitor.h" // include fault monitor application object declarations


/*******************************************************************************
 * @ingroup app-layer-power-control-functions-private
 * @fn	volatile uint16_t appPowerSupply_ConverterObjectInitialize(void)
 * @brief  This function initializes the buck converter device driver instance
 * @return unsigned integer (0=failure, 1=success)
 *  
 * @details
 *  This function initialize the buck converter object status, reset the buck state 
 *  machine, set reference values, clear the runtime data, initialize the switch node,
 *  and setup the feedback channels and start-up settings.
 *********************************************************************************/

volatile uint16_t appPowerSupply_ConverterObjectInitialize(void)
{
    volatile uint16_t retval = 1;
    volatile uint16_t _i = 0;
    volatile bool adc_trigger_mode=false;
    
    // Initialize Buck Converter Object Status
    buck.status.bits.ready = false; // Clear Converter Ready flag
    buck.status.bits.adc_active = false; // Clear ADC STARTED flag
    buck.status.bits.pwm_active = false; // clear PWM STARTED flag
//    buck.status.bits.power_source_detected = false; // Clear POWER SOURCE DETECTED flag // ToDo: remove
    buck.status.bits.cs_calib_complete = false; // Clear Current Sense Calibration flag
    buck.status.bits.fault_active = true; // Set global FAULT flag
    buck.status.bits.cs_calib_enable = BUCK_ISNS_OFFSET_CALIBRATION_ENABLE; // Topology current sensors need to be calibrated
    buck.status.bits.autorun = true;  // Allow the buck converter to run when cleared of faults
    buck.status.bits.enabled = false; // Disable buck converter
    buck.status.bits.suspend = true; // Set SUSPEND flag bit to keep power supply on hold until startup conditions are cleared

    // Set Initial State Machine State
    buck.state_id.value = (uint32_t)BUCK_OPSTATE_INITIALIZE; // Reset Buck State Machine
    
    // Set Reference values
    buck.set_values.control_mode = BUCK_CONTROL_MODE_VMC; // Set Control Mode
    buck.set_values.i_ref = BUCK_ISNS_REF; // Set current loop reference
    buck.set_values.v_ref = BUCK_VOUT_REF; // Set voltage loop reference
    buck.set_values.no_of_phases = BUCK_NO_OF_PHASES; // Set number of converter phases
    
    // Clear Runtime Data
    for (_i=0; _i<buck.set_values.no_of_phases; _i++) // Reset phase current values
    { buck.data.i_sns[0] = 0; }
    buck.data.i_out = 0; // Reset output current value
    buck.data.v_out = 0; // Reset output voltage value
    buck.data.v_in = 0;  // Reset input voltage value
    buck.data.temp = 0;  // Reset output temperature value
    
    // Initialize Switch Node of PWM #1
    buck.sw_node[0].pwm_instance = BUCK_PWM1_CHANNEL;
    buck.sw_node[0].gpio_instance = BUCK_PWM1_GPIO_INSTANCE;
    buck.sw_node[0].gpio_high = BUCK_PWM1_GPIO_PORT_PINH;
    buck.sw_node[0].gpio_low = BUCK_PWM1_GPIO_PORT_PINL;
    buck.sw_node[0].master_period_enable = false; ///< Master time base is disabled, synchronization is established among PWM generators
	buck.sw_node[0].high_resolution_enable = true;
    buck.sw_node[0].period = BUCK_PWM_PERIOD;
    buck.sw_node[0].phase = 0; ///< Master phase starts at timebase counot of =0
    buck.sw_node[0].duty_ratio_min = BUCK_PWM_DC_MIN;
    buck.sw_node[0].duty_ratio_init = BUCK_PWM_DC_MIN;
    buck.sw_node[0].duty_ratio_max = BUCK_PWM_DC_MAX;
    buck.sw_node[0].dead_time_rising = BUCK_PWM_DEAD_TIME_LE;
    buck.sw_node[0].dead_time_falling = BUCK_PWM_DEAD_TIME_FE;
    buck.sw_node[0].leb_period = BUCK_LEB_PERIOD;
    buck.sw_node[0].trigger_offset = BUCK_PWM1_ADTR1OFS;
    buck.sw_node[0].trigger_scaler = BUCK_PWM1_ADTR1PS;

    // Initialize Switch Node of PWM #1
    buck.sw_node[1].pwm_instance = BUCK_PWM2_CHANNEL;
    buck.sw_node[1].gpio_instance = BUCK_PWM2_GPIO_INSTANCE;
    buck.sw_node[1].gpio_high = BUCK_PWM2_GPIO_PORT_PINH;
    buck.sw_node[1].gpio_low = BUCK_PWM2_GPIO_PORT_PINL;
    buck.sw_node[1].master_period_enable = false; ///< Master time base is disabled, synchronization is established among PWM generators
	buck.sw_node[1].high_resolution_enable = true;
    buck.sw_node[1].period = BUCK_PWM_PERIOD;
    buck.sw_node[1].phase = BUCK_PWM_PHASE_SHIFT; 
    buck.sw_node[1].duty_ratio_min = BUCK_PWM_DC_MIN;
    buck.sw_node[1].duty_ratio_init = BUCK_PWM_DC_MIN;
    buck.sw_node[1].duty_ratio_max = BUCK_PWM_DC_MAX;
    buck.sw_node[1].dead_time_rising = BUCK_PWM_DEAD_TIME_LE;
    buck.sw_node[1].dead_time_falling = BUCK_PWM_DEAD_TIME_FE;
    buck.sw_node[1].leb_period = BUCK_LEB_PERIOD;
    buck.sw_node[1].trigger_offset = BUCK_PWM2_ADTR1OFS;
    buck.sw_node[1].trigger_scaler = BUCK_PWM2_ADTR1PS;
    
    // Initialize additional GPIOs 
    
    // ~~~ EXTERNAL ENABLE INPUT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    buck.gpio.EnableInput.enabled = false; // this converter doesn't support external enable control
    // ~~~ EXTERNAL ENABLE INPUT END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ~~~ POWER GOOD OUTPUT ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    buck.gpio.PowerGood.enabled = true; // This converter supports an additional POWER GOOD output
    buck.gpio.PowerGood.port = PWRGOOD_PORT; // Number of the GPIO port (0=Port RA, 0=Port RB, 0=Port RC, etc.)
    buck.gpio.PowerGood.pin = PWRGOOD_PIN; // Number of the GPIO port pin
    buck.gpio.PowerGood.polarity = 0;   // This pin is ACTIVE HIGH (only required if io_type = OUTPUT)
    buck.gpio.PowerGood.io_type = 0;    // This pin is configured as OUTPUT
    
    // ~~~ POWER GOOD OUTPUT END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // Initialize Feedback Channels
    
    // ~~~ OUTPUT VOLTAGE FEEDBACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    buck.feedback.ad_vout.enabled = true;   // Use this channel
    adc_trigger_mode = (bool)(BUCK_VOUT_TRIGGER_MODE == BUCK_VOUT_TRIG_ADC);

    buck.feedback.ad_vout.adc_input = BUCK_VOUT_ADCIN;
    buck.feedback.ad_vout.adc_core = BUCK_VOUT_ADCCORE;
    buck.feedback.ad_vout.adc_buffer = &BUCK_VOUT_ADCBUF;
    buck.feedback.ad_vout.trigger_source = BUCK_VOUT_TRGSRC;

    buck.feedback.ad_vout.differential_input = false;
    buck.feedback.ad_vout.interrupt_enable = adc_trigger_mode;
    buck.feedback.ad_vout.early_interrupt_enable = adc_trigger_mode;
    buck.feedback.ad_vout.level_trigger = false;
    buck.feedback.ad_vout.signed_result = false;
    
    buck.feedback.ad_vout.scaling.factor = BUCK_VOUT_NORM_FACTOR;
    buck.feedback.ad_vout.scaling.scaler = BUCK_VOUT_NORM_SCALER;
    buck.feedback.ad_vout.scaling.offset = BUCK_VOUT_OFFSET;
    
    BUCK_VOUT_ANSEL = (int)buck.feedback.ad_vout.enabled;
    
    // ~~~ OUTPUT VOLTAGE FEEDBACK END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ~~~ INPUT VOLTAGE FEEDBACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    buck.feedback.ad_vin.enabled = true;   // Use this channel

    buck.feedback.ad_vin.adc_input = BUCK_VIN_ADCIN;
    buck.feedback.ad_vin.adc_core = BUCK_VIN_ADCCORE;
    buck.feedback.ad_vin.adc_buffer = &BUCK_VIN_ADCBUF;
    buck.feedback.ad_vin.trigger_source = BUCK_VIN_TRGSRC;

    buck.feedback.ad_vin.differential_input = false;
    buck.feedback.ad_vin.interrupt_enable = false;
    buck.feedback.ad_vin.early_interrupt_enable = false;
    buck.feedback.ad_vin.level_trigger = false;
    buck.feedback.ad_vin.signed_result = false;

    buck.feedback.ad_vin.scaling.factor = BUCK_VIN_NORM_FACTOR;
    buck.feedback.ad_vin.scaling.scaler = BUCK_VIN_NORM_SCALER;
    buck.feedback.ad_vin.scaling.offset = BUCK_VIN_OFFSET;
    
    BUCK_VIN_ANSEL = (int)buck.feedback.ad_vin.enabled;
    
    // ~~~ INPUT VOLTAGE FEEDBACK END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~ OUTPUT CURRENT FEEDBACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    buck.feedback.ad_isns[0].enabled = true;   // Use this channel

    buck.feedback.ad_isns[0].adc_input = BUCK_ISNS1_ADCIN;
    buck.feedback.ad_isns[0].adc_core = BUCK_ISNS1_ADCCORE;
    buck.feedback.ad_isns[0].adc_buffer = &BUCK_ISNS1_ADCBUF;
    buck.feedback.ad_isns[0].trigger_source = BUCK_ISNS1_TRGSRC;

    buck.feedback.ad_isns[0].differential_input = false;
    buck.feedback.ad_isns[0].interrupt_enable = false;
    buck.feedback.ad_isns[0].early_interrupt_enable = false;
    buck.feedback.ad_isns[0].level_trigger = false;
    buck.feedback.ad_isns[0].signed_result = false;

    buck.feedback.ad_isns[0].scaling.factor = BUCK_ISNS_NORM_FACTOR;
    buck.feedback.ad_isns[0].scaling.scaler = BUCK_ISNS_NORM_SCALER;
    buck.feedback.ad_isns[0].scaling.offset = BUCK_ISNS1_OFFFSET;
    
    
    BUCK_ISNS1_ANSEL = (int)buck.feedback.ad_isns[0].enabled;

    
    buck.feedback.ad_isns[1].enabled = true;   // Use this channel

    buck.feedback.ad_isns[1].adc_input = BUCK_ISNS2_ADCIN;
    buck.feedback.ad_isns[1].adc_core = BUCK_ISNS2_ADCCORE;
    buck.feedback.ad_isns[1].adc_buffer = &BUCK_ISNS2_ADCBUF;
    buck.feedback.ad_isns[1].trigger_source = BUCK_ISNS2_TRGSRC;

    buck.feedback.ad_isns[1].differential_input = false;
    buck.feedback.ad_isns[1].interrupt_enable = false;
    buck.feedback.ad_isns[1].early_interrupt_enable = false;
    buck.feedback.ad_isns[1].level_trigger = false;
    buck.feedback.ad_isns[1].signed_result = false;

    BUCK_ISNS2_ANSEL = (int)buck.feedback.ad_isns[1].enabled;

    
    // ~~~ OUTPUT CURRENT FEEDBACK END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Initialize Startup Settings
    
    buck.startup.power_on_delay.counter = 0;
    buck.startup.power_on_delay.period = BUCK_POD;
    buck.startup.power_on_delay.ref_inc_step = 0;
    buck.startup.power_on_delay.reference = 0;
    
    buck.startup.v_ramp.counter = 0;
    buck.startup.v_ramp.period = BUCK_VRAMP_PER;
    buck.startup.v_ramp.ref_inc_step = BUCK_VREF_STEP;
    if (buck.startup.v_ramp.ref_inc_step == 0)
        buck.startup.v_ramp.ref_inc_step = 1;
    buck.startup.v_ramp.reference = 0;
    
    if (buck.set_values.control_mode == BUCK_CONTROL_MODE_ACMC) 
    {
        buck.startup.i_ramp.counter = 0;
        buck.startup.i_ramp.period = BUCK_IRAMP_PER;
        buck.startup.i_ramp.ref_inc_step = BUCK_IREF_STEP;
        buck.startup.i_ramp.reference = 0;
    }
    
    buck.startup.power_good_delay.counter = 0;
    buck.startup.power_good_delay.period = BUCK_PGD;
    buck.startup.power_good_delay.ref_inc_step = 0;
    buck.startup.power_good_delay.reference = BUCK_VOUT_REF;
    
    
    return(retval);
}


/*******************************************************************************
 * @ingroup app-layer-power-control-functions-private
 * @fn	volatile uint16_t appPowerSupply_ControllerInitialize(void)
 * @brief  This function initializes the control system feedback loop objects
 * @return 0=failure
 * @return 1=success
 * 
 * @details
 * This function allows the user to set up and initialize the loop configuration. This 
 * includes the following setup.
 *     - Initialize Default Loop Configuration
 *     - Set Controller Object of Voltage Loop
 *     - Configure Voltage Loop Controller Object
 *     - Configure controller input/output ports
 *     - Data Input/Output Limit Configuration
 *     - ADC Trigger Control Configuration
 *     - Data Provider Configuration
 *     - Cascaded Function Configuration
 *     - Initialize Advanced Control Settings 
 *     - Custom Advanced Control Settings
 *********************************************************************************/

volatile uint16_t appPowerSupply_ControllerInitialize(void)
{
    volatile uint16_t retval = 1;
    
    // ~~~ VOLTAGE LOOP CONFIGURATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // Initialize Default Loop Configuration
    buck.v_loop.feedback_offset = BUCK_VOUT_OFFSET;
    buck.v_loop.reference = BUCK_VOUT_REF;
    buck.v_loop.minimum = BUCK_PWM_DC_MIN;
    buck.v_loop.maximum = BUCK_PWM_DC_MAX;
    buck.v_loop.trigger_offset = ((BUCK_PWM_PERIOD >> 1) + BUCK_VOUT_ADC_TRGDLY);
    
     // Set Controller Object of Voltage Loop
    buck.v_loop.controller = &v_loop;
    buck.v_loop.ctrl_Initialize = &v_loop_Initialize;
    buck.v_loop.ctrl_Update = &v_loop_Update;
    buck.v_loop.ctrl_Reset = &v_loop_Reset;
    buck.v_loop.ctrl_Precharge = &v_loop_Precharge;
    
    // Configure Voltage Loop Controller Object
    buck.v_loop.ctrl_Initialize(&v_loop);   // Call Initialization Routine setting histories and scaling
    
    // Configure controller input ports
    buck.v_loop.controller->Ports.Source.ptrAddress = &BUCK_VOUT_ADCBUF; // Output Voltage is Common Source
    buck.v_loop.controller->Ports.Source.Offset = buck.v_loop.feedback_offset; // Output Voltage feedback signal offset 
    buck.v_loop.controller->Ports.Source.NormScaler = BUCK_VOUT_NORM_SCALER; // Output voltage normalization factor bit-shift scaler 
    buck.v_loop.controller->Ports.Source.NormFactor = BUCK_VOUT_NORM_FACTOR; // Output voltage normalization factor fractional
    
    buck.v_loop.controller->Ports.AltSource.ptrAddress = &BUCK_VIN_ADCBUF; // Input Voltage Is Alternate Source
    buck.v_loop.controller->Ports.AltSource.Offset = BUCK_VIN_OFFSET; // Input Voltage feedback signal offset 
    buck.v_loop.controller->Ports.AltSource.NormScaler = BUCK_VIN_NORM_SCALER; // Input voltage normalization factor bit-shift scaler 
    buck.v_loop.controller->Ports.AltSource.NormFactor = BUCK_VIN_NORM_FACTOR; // Input voltage normalization factor fractional

    // Configure controller output ports
    buck.v_loop.controller->Ports.Target.ptrAddress = &BUCK_PWM1_PDC; // PWM Duty Cycle is Control Target
    buck.v_loop.controller->Ports.Target.Offset = 0; // Static primary output value offset
    buck.v_loop.controller->Ports.Target.NormScaler = 0; // Primary control output normalization factor bit-shift scaler 
    buck.v_loop.controller->Ports.Target.NormFactor = 0x7FFF; // Primary control output normalization factor fractional 

    buck.v_loop.controller->Ports.AltTarget.ptrAddress = &BUCK_PWM2_PDC; // PWM Duty Cycle is Control Target
    buck.v_loop.controller->Ports.AltTarget.Offset = 0; // Static secondary output value offset
    buck.v_loop.controller->Ports.AltTarget.NormScaler = 0; // Secondary control output normalization factor bit-shift scaler
    buck.v_loop.controller->Ports.AltTarget.NormFactor = 0x7FFF; // Secondary control output normalization factor fractional 
    
    // Configure controller control ports
    buck.v_loop.controller->Ports.ptrControlReference = &buck.set_values.v_ref; // Set pointer to Reference
    
    // Data Input/Output Limit Configuration
    buck.v_loop.controller->Limits.MinOutput = buck.v_loop.minimum;
    buck.v_loop.controller->Limits.MaxOutput = buck.v_loop.maximum;
    buck.v_loop.controller->Limits.AltMinOutput = 0; // not used
    buck.v_loop.controller->Limits.AltMaxOutput = 0; // not used

    // ADC Trigger Control Configuration
    buck.v_loop.controller->ADCTriggerControl.ptrADCTriggerARegister = &BUCK_VOUT_ADCTRIG;    // Using PGxTRIGA = ADC Trigger 1
    buck.v_loop.controller->ADCTriggerControl.ADCTriggerAOffset = buck.v_loop.trigger_offset; // Triggering at 50% off-time
    buck.v_loop.controller->ADCTriggerControl.ptrADCTriggerBRegister = &BUCK_ISNS1_ADCTRIG;   // Using PGxTRIGB = ADC Trigger 2
    buck.v_loop.controller->ADCTriggerControl.ADCTriggerBOffset = BUCK_ISNS_ADC_TRGDLY; // Triggering at 50% on-time
    
    // Data Provider Configuration
    buck.v_loop.controller->DataProviders.ptrDProvControlInput = &buck.data.v_out;
    buck.v_loop.controller->DataProviders.ptrDProvControlError = NULL;
    buck.v_loop.controller->DataProviders.ptrDProvControlOutput = NULL;
    
    // Cascaded Function Configuration
    buck.v_loop.controller->CascadeTrigger.ptrCascadedFunction = NULL;
    buck.v_loop.controller->CascadeTrigger.CascadedFunctionParam = 0;
    
    // Initialize Advanced Control Settings (not used in this code example)
    buck.v_loop.controller->GainControl.AgcFactor = BUCK_AGC_NOM_FACTOR;
    buck.v_loop.controller->GainControl.AgcScaler = -BUCK_AGC_NOM_SCALER;
    buck.v_loop.controller->GainControl.AgcMedian = (int16_t)(BUCK_AGC_MEDIAN >> BUCK_AGC_NOM_SCALER);

    buck.v_loop.controller->GainControl.ptrAgcObserverFunction = (uint16_t)&v_loop_AGCFactorUpdate;

    // Custom Advanced Control Settings
    // Use proprietary control parameters to place VIN-2-VOUT scaling factor
    buck.v_loop.controller->Advanced.usrParam1 = (uint16_t)(-BUCK_AGC_IO_NORM_SCALER);
    buck.v_loop.controller->Advanced.usrParam2 = BUCK_AGC_IO_NORM_FACTOR;
    buck.v_loop.controller->Advanced.usrParam3 = 0; // No additional advanced control options used
    buck.v_loop.controller->Advanced.usrParam4 = 0; // No additional advanced control options used

    // Reset Controller Status
    buck.v_loop.controller->status.bits.enabled = false; // Keep controller disabled
    buck.v_loop.controller->status.bits.swap_source = false; // use SOURCE as major control input
    buck.v_loop.controller->status.bits.swap_target = false; // use TARGET as major control output
    buck.v_loop.controller->status.bits.invert_input = false; // Do not invert input value
    buck.v_loop.controller->status.bits.lower_saturation_event = false; // Reset Anti-Windup Minimum Status bit
    buck.v_loop.controller->status.bits.upper_saturation_event = false; // Reset Anti-Windup Maximum Status bits
    buck.v_loop.controller->status.bits.agc_enabled = false;   // Enable Adaptive Gain Modulation by default

    // ~~~ VOLTAGE LOOP CONFIGURATION END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    
    return(retval);
}

/*******************************************************************************
 * @ingroup app-layer-power-control-functions-private
 * @fn	volatile uint16_t appPowerSupply_PeripheralsInitialize(void)
 * @brief  This function is used to load peripheral configuration templates from the power controller device driver
 * @return 0=failure
 * @return 1=success
 * 
 * @details
 * This function hand over the peripheral configuration to the buck converter driver
 *********************************************************************************/

volatile uint16_t appPowerSupply_PeripheralsInitialize(void)
{
    volatile uint16_t retval=1;
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Write standard configurations supported by BUCK_POWER_CONTROLLER_s
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    retval &= drv_BuckConverter_Initialize(&buck); // Hand over peripheral configuration to driver
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Write Custom Configuration of Remappable PWM Channel #4
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    BUCK_PWM2H_INIT;
    BUCK_PWM2L_INIT;

    retval &= PPS_UnlockIO();
    retval &= PPS_RemapOutput(BUCK_PWM2H_RPx, PPSOUT_PWM4H);
    retval &= PPS_RemapOutput(BUCK_PWM2L_RPx, PPSOUT_PWM4L);
    retval &= PPS_LockIO();
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Custom configurations
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    // ToDo: Incorporate hard coded register settings into generic data structure scheme, if possible
    ADCON4Hbits.C1CHS = 1; // Set ADC  input channel to read from ANA1
    
    // Synchronize PWM channels #1 and #2
    // => taken care of by the state machine automatically, when multiple phases are defined
    // If PWM channels need to be synchronized to other converter PWMs, this needs to be done 
    // manually here
    
    return(retval);
}


// end of file
