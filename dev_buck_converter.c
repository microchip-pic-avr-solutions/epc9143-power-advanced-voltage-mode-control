/*
 * File:   dev_buck_converter.c
 * Author: M91406
 *
 * Created on July 9, 2019, 1:10 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "pwr_control/devices/dev_buck_typedef.h"
#include "pwr_control/devices/dev_buck_converter.h"

// Private function prototypes of state functions

volatile uint16_t __attribute__((always_inline)) State_Error(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) State_Initialize(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) State_Reset(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) State_Standby(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) State_PowerOnDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) State_PrepareVRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) State_VRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) State_IRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) State_PowerGoodDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) State_Online(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);

// Function pointer array defining the state machine execution sequence

volatile uint16_t (*BuckConverterStateMachine[])(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) = {

    State_Error,        // That's the blank "undefined default state", causing the state machine to reset
    State_Initialize,   // Initialize state machine by resetting all runtime flags to default
    State_Reset,        // Reset key runtime flags when power converter was already turned on
    State_Standby,      // After successful initialization, power converter waits to be launched
    State_PowerOnDelay, // Wait programmed number of state machine ticks until startup is triggered
    State_PrepareVRampUp, // Determine ramp up condition, pre-charge controllers and program PWM/Peripherals
    State_VRampUp,      // Output voltage ramp up
    State_IRampUp,      // Output current ramp up (optional, for startup current limiting only)
    State_PowerGoodDelay, // Wait until power good delay has expired and optionally set a GPIO
    State_Online,       // During normal operation the converter responds to changes in reference
/*
    State_Start,
    State_Stop,
    State_Resume,
    State_Suspend
 */ 
};

// buck converter function pointer array size
volatile uint16_t StateList_size = (sizeof(BuckConverterStateMachine)/sizeof(BuckConverterStateMachine[0])); 


/*@@drv_BuckConverter_Execute
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * 
 * *********************************************************************************/
volatile uint16_t drv_BuckConverter_Execute(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) {
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* DISABLE-RESET                                                                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    // When enable status has changed from ENABLED to DISABLED, reset the state machine
    if ((!buckInstance->status.bits.enabled) || 
        (buckInstance->status.bits.fault_active))
    {
        if (!buckInstance->status.bits.ready)
            buckInstance->mode = BUCK_STATE_INITIALIZE;
        else
            buckInstance->mode = BUCK_STATE_RESET;
    }    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* FUNCTION CALL PROTECTION                                                           */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(buckInstance->mode >= StateList_size)
        buckInstance->mode = BUCK_STATE_INITIALIZE;
    
    if(buckInstance == NULL)
        return(0);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    // Call state machine
    buckInstance->mode = BuckConverterStateMachine[buckInstance->mode](buckInstance);


    return(1);
}

/*@@drv_BuckConverter_Start
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * 
 * *********************************************************************************/
volatile uint16_t drv_BuckConverter_Start(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) {

    volatile uint16_t retval=1;
    
    // Start PWM with its outputs disabled
    retval &= buckPWM_Start(buckInstance->sw_node.pwm_instance);
    
    buckInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    buckInstance->v_loop.ctrl_Reset(buckInstance->v_loop.controller); // Reset voltage loop histories

    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC) { // In current mode...
        buckInstance->i_loop.controller->status.bits.enabled = false; // Disable current loop
        buckInstance->i_loop.ctrl_Reset(buckInstance->i_loop.controller); // Reset current loop histories
    }
    
    buckInstance->status.bits.enabled = true;   // Enable Buck Converter
    buckInstance->mode = BUCK_STATE_INITIALIZE; // Reset state machine

    return(retval);
}

/*@@drv_BuckConverter_Stop
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * 
 * *********************************************************************************/
volatile uint16_t drv_BuckConverter_Stop(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) {

    volatile uint16_t retval=1;
    
    // Stop PWM completely (shuts down PWM generator)
    retval &= buckPWM_Stop(buckInstance->sw_node.pwm_instance); // Stop PWM
    
    buckInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    
    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC) // In current mode...
        buckInstance->i_loop.controller->status.bits.enabled = false; // Disable current loop
    
    buckInstance->status.bits.enabled = false;  // Disable Buck Converter
    buckInstance->mode = BUCK_STATE_INITIALIZE; // Reset state machine

    return(retval);
}

/*@@drv_BuckConverter_Suspend
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * 
 * *********************************************************************************/
volatile uint16_t drv_BuckConverter_Suspend(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) {
    
    volatile uint16_t retval=1;

    // Reset state machine state and enforce a state switch
    buckInstance->mode = BUCK_STATE_RESET;
    retval &= drv_BuckConverter_Execute(buckInstance);
    
    return(retval);
}

/*@@drv_BuckConverter_Resume
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * 
 * *********************************************************************************/
volatile uint16_t drv_BuckConverter_Resume(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) {
    
    volatile uint16_t retval=1;
    
    // Reset state machine state and enforce a state switch
    buckInstance->mode = BUCK_STATE_STANDBY;
    retval &= drv_BuckConverter_Execute(buckInstance);
    
    return(retval);
}

/* ============================================================================== */
/*  PRIVATE STATE FUNCTIONS                                                       */
/* ============================================================================== */

/*@@State_Initialize
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * If the controller has not been run yet, the POWER ON and POWER GOOD delay
 * counters are reset and all conditional flag bits are cleared. Status of 
 * power source, ADC and current sensor calibration have to be set during
 * runtime by system check routines. 
 * *********************************************************************************/
volatile uint16_t State_Initialize(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    buckInstance->startup.power_on_delay.counter = 0;   // Reset power on counter
    buckInstance->startup.power_good_delay.counter = 0; // Reset power good counter

    // Reset all status bits
    buckInstance->status.bits.adc_active = false;

    // Initiate current sensor calibration flag bit
    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_VMC)
        buckInstance->status.bits.cs_calib_ready = true; 
    else
        buckInstance->status.bits.cs_calib_ready = false; 

    // Disable control loops
    buckInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    
    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC) // In current mode...
        buckInstance->i_loop.controller->status.bits.enabled = false; // Disable current loop
    
    // Clear busy bit
    buckInstance->status.bits.fault_active = true; // set fault bit to be cleared by fault handler
    buckInstance->status.bits.ready = false; // Clear ready bit
    buckInstance->status.bits.busy = false; // Clear BUSY bit
    
    // Transition to STATE_RESET
    return(BUCK_STATE_RESET); 
    
}

/*@@State_Reset
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * After successful initialization or after an externally triggered state machine reset,
 * the state machine returns to this RESET mode, re-initiating control mode, references 
 * and status bits before switching further into STANDBY mode. 
 * *********************************************************************************/
volatile uint16_t State_Reset(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t retval=0;
    
    // Disable PWM outputs & control loops (immediate power cut-off)
    retval &= buckPWM_Suspend(buckInstance->sw_node.pwm_instance); // Disable PWM outputs

    // Disable voltage loop controller and reset control loop histories
    buckInstance->v_loop.controller->status.bits.enabled = false; // disable voltage control loop
    buckInstance->v_loop.ctrl_Reset(buckInstance->v_loop.controller); // Reset control histories of outer voltage controller
    *buckInstance->v_loop.controller->Ports.Target.ptrAddress = 
        buckInstance->v_loop.controller->Limits.MinOutput;

    // Disable current loop controller and reset control loop histories
    if (buck.set_values.control_mode == BUCK_CONTROL_MODE_ACMC) 
    {   // Disable all current control loops and reset control loop histories
        buckInstance->i_loop.controller->status.bits.enabled = false; 
        buckInstance->i_loop.ctrl_Reset(buckInstance->i_loop.controller); 
        *buckInstance->i_loop.controller->Ports.Target.ptrAddress = 
            buckInstance->i_loop.controller->Limits.MinOutput;
    }

    // If any sub-function calls went unsuccessful, reset state machine
    // else, move on to next state
    
    if (retval)
        return(BUCK_STATE_STANDBY);
    else
        return(BUCK_STATE_INITIALIZE);
    
}
                
/*@@State_Standby
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * After a successful state machine reset, the state machine waits in  
 * STANDBY mode until all conditional flag bits are set/cleared allowing  
 * the converter to run. 
 * *********************************************************************************/
volatile uint16_t State_Standby(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    // if the 'autorun' option is set, automatically set the GO bit when the 
    // converter is enabled
    if ((buckInstance->status.bits.enabled) && (buckInstance->status.bits.autorun))
    { buckInstance->status.bits.GO = true; }

    // Wait for all startup conditions to be met
    if ((buckInstance->status.bits.enabled) &&          // state machine needs to be enabled
        (buckInstance->status.bits.GO) &&               // GO-bit needs to be set
        (buckInstance->status.bits.adc_active) &&       // ADC needs to be running
        (buckInstance->status.bits.pwm_active) &&       // PWM needs to be running 
        (!buckInstance->status.bits.fault_active) &&    // No active fault is present
        (buckInstance->status.bits.cs_calib_ready)      // Current Sensor Calibration complete
        )
    {
        buckInstance->status.bits.GO = false;
        buckInstance->status.bits.ready = true;
        return(BUCK_STATE_POWER_ON_DELAY);
    }
    else
    // Remain in current state until bit-test becomes true
    {
        return(BUCK_STATE_STANDBY);
    }
    
}

/*@@State_PowerOnDelay
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * After the converter has been cleared to get started, the power-on 
 * delay counter until the defined power-on delay period has expired. 
 * *********************************************************************************/
volatile uint16_t State_PowerOnDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t retval=0;

    // Set BUSY bit until process is complete
    buckInstance->status.bits.busy = true;
    
    // delay startup until POWER ON DELAY has expired
    if(buckInstance->startup.power_on_delay.counter++ > buckInstance->startup.power_on_delay.period)
    {
        // Clamp POD counter to EXPIRED
        buckInstance->startup.power_on_delay.counter = 
            (buckInstance->startup.power_on_delay.period + 1); // Saturate power on counter

        retval = BUCK_STATE_POWER_ON_DELAY; 
    }
    else
    // When the period has expired, move on to next state
    {
        retval = BUCK_STATE_PREPARE_V_RAMP;
    }    
    

    return(retval);
    
}

/*@@State_PrepareVRampUp
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * After the POWER ON DELAY has expired, the ramp up starting point is determined  
 * by measuring the input and output voltage and calculates the ideal duty ratio 
 * of the PWM. This value is then programmed into the PWM module duty cycle register 
 * and is also used to pre-charge the control loop output history. In addition the 
 * measured output voltage also set as reference to ensure the loop starts without 
 * jerks and jumps.
 * 
 * When voltage mode control is enabled, the voltage loop control history is 
 * charged, when average current mode control is enabled, the current loop control 
 * history is charged.
 * *********************************************************************************/
volatile uint16_t State_PrepareVRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint32_t _vout=0, _vin=0, _start_dc=0;

    // Set BUSY bit until process is complete
    buckInstance->status.bits.busy = true;
    
    // Hijack voltage loop controller reference
    buckInstance->startup.v_ramp.reference = 0; // Reset Soft-Start Voltage Reference
    buckInstance->startup.i_ramp.reference = 0; // Reset Soft-Start Current Reference
    buckInstance->v_loop.controller->Ports.ptrControlReference = 
        &buckInstance->startup.v_ramp.reference; // Voltage loop is pointing to Soft-Start Reference

    // Pre-charge reference
    // Never start above the pre-biased output voltage.
    // Always start at or slightly below the pre-biased output voltage
    buckInstance->startup.v_ramp.reference = buckInstance->data.v_out;

    // In average current mode, set current reference limit to max startup current level
    if (buck.set_values.control_mode == BUCK_CONTROL_MODE_ACMC) 
    {   // Disable all current control loops and reset control loop histories
        buckInstance->v_loop.maximum = buckInstance->set_values.i_ref;
        buckInstance->v_loop.controller->Limits.MaxOutput = buckInstance->v_loop.maximum;
    }

    // Pre-charge PWM and control loop history 
    if(((buckInstance->data.v_in - buckInstance->feedback.ad_vin.scaling.offset) > 0) &&
       ((buckInstance->data.v_out - buckInstance->feedback.ad_vout.scaling.offset) > 0) )
    {
        _vout = __builtin_muluu(
            (buckInstance->data.v_out - buckInstance->feedback.ad_vout.scaling.offset), 
            buckInstance->feedback.ad_vout.scaling.factor);
        _vout >>= (16 - buckInstance->feedback.ad_vout.scaling.scaler);

        _vin = __builtin_muluu(
            (buckInstance->data.v_in - buckInstance->feedback.ad_vin.scaling.offset), 
            buckInstance->feedback.ad_vin.scaling.factor);
        _vin >>= (16 - buckInstance->feedback.ad_vin.scaling.scaler);

        _start_dc = __builtin_muluu(_vout, buckInstance->sw_node.period);
        _start_dc = __builtin_divud(_start_dc, (uint16_t)_vin);
    }
    else
    // If there is no input voltage or no output voltage, start with minimum duty ratio
    {
        _start_dc = (uint16_t)buckInstance->sw_node.duty_ratio_min;
    }

    // Program PWM module and pre-charge control loop
    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_VMC)
    {
        if(_start_dc < buckInstance->v_loop.minimum) 
        { _start_dc = buckInstance->v_loop.minimum; }
        else if(_start_dc > buckInstance->v_loop.maximum) 
        { _start_dc = buckInstance->v_loop.maximum; }

        buckInstance->v_loop.ctrl_Precharge(buckInstance->v_loop.controller, 0, _start_dc);
        *buckInstance->v_loop.controller->Ports.Target.ptrAddress = _start_dc; // set initial PWM duty ratio
        *buckInstance->v_loop.controller->Ports.AltTarget.ptrAddress = _start_dc; // set initial PWM duty ratio

    }
    else if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC) 
    {   
        if(_start_dc < buckInstance->i_loop.minimum) 
        { _start_dc = buckInstance->i_loop.minimum; }
        else if(_start_dc > buckInstance->i_loop.maximum) 
        { _start_dc = buckInstance->i_loop.maximum; }

        buckInstance->i_loop.ctrl_Precharge(
                    buckInstance->i_loop.controller, 0, _start_dc
                );

        *buckInstance->i_loop.controller->Ports.Target.ptrAddress = _start_dc; // set initial PWM duty ratio
        *buckInstance->i_loop.controller->Ports.AltTarget.ptrAddress = _start_dc; // set initial PWM duty ratio
    }
    else
    {
        return(BUCK_STATE_INITIALIZE);
    }

    return(BUCK_STATE_V_RAMP_UP);
    
}

/*@@State_VRampUp
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * This is the essential step in which the output voltage is ramped up by 
 * incrementing the outer control loop reference. In voltage mode the output  
 * voltage will ramp up to the nominal regulation point. 
 * In average current mode the inner loop will limit the voltage as soon as the 
 * current reference limit is hit and the output is switched to constant current 
 * mode. 
 * *********************************************************************************/
volatile uint16_t State_VRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t retval=0;
    
    // Set BUSY bit until process is complete
    buckInstance->status.bits.busy = true;
    
    // ensure control loop is enabled
    if(!buckInstance->v_loop.controller->status.bits.enabled) {

        // Enable input power source
        retval &= buckPWM_Resume(buckInstance->sw_node.pwm_instance);  // Enable PWM outputs

        if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_VMC)
        {   
            buckInstance->v_loop.controller->status.bits.enabled = true; // enable voltage loop controller
        }
        else if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC)
        {
            buckInstance->v_loop.controller->status.bits.enabled = true; // enable voltage loop controller
            buckInstance->i_loop.controller->status.bits.enabled = true; // enable phase current loop controller
        }

    }

    // increment reference
    buckInstance->startup.v_ramp.reference += buckInstance->startup.v_ramp.ref_inc_step;

    // check if ramp is complete
    if (buckInstance->startup.v_ramp.reference > buckInstance->v_loop.reference) 
    {
        // Set reference to the desired level
        buckInstance->startup.v_ramp.reference = buckInstance->v_loop.reference;

        // Reconnect API reference to controller
        buckInstance->v_loop.controller->Ports.ptrControlReference = &buckInstance->v_loop.reference;

        if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_VMC)
            retval = BUCK_STATE_PWRGOOD_DELAY;
        else if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC)
            retval = BUCK_STATE_I_RAMP_UP;

    }
    else
    // remain in this state until ramp is complete
    {
        retval = BUCK_STATE_V_RAMP_UP;
    }

    
    return(retval);
    
}

/*@@State_IRampUp
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * This phase of the soft-start ramp is only executed in average current mode and 
 * will only take effect when the current limit is hit before the nominal voltage 
 * regulation point. In this case the constant output current is ramped up to from 
 * the startup current to the nominal constant charging current.
 * *********************************************************************************/
volatile uint16_t State_IRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t retval=0;
    
    // Set BUSY bit until process is complete
    buckInstance->status.bits.busy = true;

    // in average current mode if voltage limit is hit, increment 
    // voltage loop limit to ramp up current loop
    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC)
    {
        // increment current limit
        buckInstance->v_loop.controller->Limits.MaxOutput += buckInstance->startup.i_ramp.ref_inc_step; // Increment maximum current limit

        // check if ramp is complete
        if (buckInstance->v_loop.controller->Limits.MaxOutput >= buckInstance->set_values.i_ref)
        {
            buckInstance->v_loop.maximum = buckInstance->set_values.i_ref;
            buckInstance->v_loop.controller->Limits.MaxOutput = buckInstance->v_loop.maximum;
            retval = BUCK_STATE_PWRGOOD_DELAY;
        }
        else
        // if ramp is not complete yet, remain in this state
        {
            retval = BUCK_STATE_I_RAMP_UP;
        }
    }
    else // Non-Current Loops Ending up here need to be lifted to PG_DELAY
    { 
        buckInstance->v_loop.controller->Limits.MaxOutput = buckInstance->v_loop.maximum;
        retval = BUCK_STATE_PWRGOOD_DELAY; 
    }

    return(retval);
    
}

/*@@State_PowerGoodDelay
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * In this phase of the soft-start procedure a counter is incremented until the 
 * power good delay has expired before the soft-start process is marked as COMPLETED
 * *********************************************************************************/
volatile uint16_t State_PowerGoodDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t retval=0;
    
    // Set BUSY bit until process is complete
    buckInstance->status.bits.busy = true;

    // increment delay counter until the GOWER GOOD delay has expired
    if(buckInstance->startup.power_good_delay.counter++ > buckInstance->startup.power_good_delay.period)
    {
        buckInstance->startup.power_good_delay.counter = 
            (buckInstance->startup.power_good_delay.period + 1); // Clamp to PERIOD_EXPIRED for future startups

        // If defined, set POWER_GOOD output
        if(buckInstance->gpio.PowerGood.enabled)
        {
            retval = buckGPIO_Set(&buckInstance->gpio.PowerGood);
            if(!retval)
                return(BUCK_STATE_ERROR);
        }
        
        retval = BUCK_STATE_ONLINE;
    }
    else
    // if period has not expired yet, remain in this state
    {
        retval = BUCK_STATE_PWRGOOD_DELAY;
    }

    return(retval);
    
}

/*@@State_Online
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * After soft-start and when state POWER_GOOD_DELAY has expired, the converter 
 * enters normal operation.
 * 
 * During normal operation the state machine scans the user reference setting. 
 * Once a change between the user reference setting and the most recent controller 
 * reference has been detected, the state machine will tune the controller 
 * reference to the new user control reference level in incremental steps,
 * applying the same ramp slope as during soft-start.
 * 
 * While ramping the output voltage up or down, the BUSY bit will be set and any 
 * new changes to the reference will be ignored until the ramp up/down is complete.
 * *********************************************************************************/
volatile uint16_t State_Online(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t retval=0;
    
    if(buckInstance->set_values.v_ref != buckInstance->v_loop.reference) 
    {
        // Set the BUSY bit indicating a delay/ramp period being executed
        buckInstance->status.bits.busy = true;

        // New reference value is less than controller reference value => ramp down
        if(buckInstance->set_values.v_ref < buckInstance->v_loop.reference){
            // decrement reference until new reference level is reached
            buckInstance->v_loop.reference -= buckInstance->startup.v_ramp.ref_inc_step; // decrement reference
            if(buckInstance->v_loop.reference < buckInstance->set_values.v_ref) { // check if ramp is complete
                buckInstance->v_loop.reference = buckInstance->set_values.v_ref; // clamp reference level to setting
            }

        }
        // New reference value is greater than controller reference value => ramp up
        else if(buckInstance->set_values.v_ref > buckInstance->v_loop.reference){
            // increment reference until new reference level is reached
            buckInstance->v_loop.reference += buckInstance->startup.v_ramp.ref_inc_step; // increment reference
            if(buckInstance->v_loop.reference > buckInstance->set_values.v_ref) { // check if ramp is complete
                buckInstance->v_loop.reference = buckInstance->set_values.v_ref; // clamp reference level to setting
            }

        }

    }
    else{
        // Clear the BUSY bit indicating "no state machine activity"
        buckInstance->status.bits.busy = false;
    }

    // remain in STATE_ONLINE
    retval = BUCK_STATE_ONLINE;

    return(retval);
    
}

/*@@State_Error
 * *********************************************************************************
 * Parameters:
 *   - BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * 
 * Returns:
 *   - uint16_t   16-bit unsigned integer
 *          0 = failure
 *          1 = success
 * 
 * Description:
 * This function is a default anchor in case task list index #0 is ever called.
 * This is the equivalent of a switch case "default".
 * *********************************************************************************/
volatile uint16_t State_Error(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t retval=0;
    
    // If this function is ever called, bring state machine back on track 
    // by resetting it to INITIALIZE
    buckInstance->status.bits.busy = false;
    buckInstance->mode = BUCK_STATE_INITIALIZE;
    
    return(retval);
}

// ______________________________________
// END OF FILE
