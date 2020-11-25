/* 
 * File:   dev_buck_substates.h
 * Author: M91406
 * Comments: Buck converter operation states header file
 * Revision history: 
 *   10/28/20   1.0  initial version
 */



#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types

#include "dev_buck_pconfig.h" // include buck converter
#include "dev_buck_typedef.h" // include buck converter data object declarations

// Private function prototypes of sub-state functions

volatile uint16_t __attribute__((always_inline)) SubState_PowerOnDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) SubState_PrepareVRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) SubState_VRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) SubState_IRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);
volatile uint16_t __attribute__((always_inline)) SubState_PowerGoodDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);

/**
 * @addtogroup buck-state-machine-struct 
 * @{
*/
// Function pointer array of buck converter startup sub-states

/*******************************************************************************
 * @var volatile uint16_t (*BuckConverterRampUpSubStateMachine[])(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
 * @brief 
 * 
 * <b>Description</b> 
 * 
 *********************************************************************************/

volatile uint16_t (*BuckConverterRampUpSubStateMachine[])(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) = {

    SubState_PowerOnDelay,      ///< Sub-State #0: Wait programmed number of state machine ticks until startup is triggered
    SubState_PrepareVRampUp,    ///< Sub-State #1: Determine ramp up condition, pre-charge controllers and program PWM/Peripherals
    SubState_VRampUp,           ///< Sub-State #2: Output voltage ramp up
    SubState_IRampUp,           ///< Sub-State #3: Output current ramp up (optional, for startup current limiting only)
    SubState_PowerGoodDelay     ///< Sub-State #4: Wait until power good delay has expired and optionally set a GPIO

};

// buck converter sub-state machine function pointer array size
volatile uint16_t BuckRampUpSubStateList_size = (sizeof(BuckConverterRampUpSubStateMachine)/sizeof(BuckConverterRampUpSubStateMachine[0])); 
/**@}*/


/**
 * @addtogroup buck-state-machine-function 
 * @{
*/

/*******************************************************************************
 * @fn volatile uint16_t SubState_PowerOnDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
 * @brief
 * @param	BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * @return  0=failure
 * @return  1=success
 *
 * <b>Description</b><br> 
 * After the converter has been cleared to get started, the power-on 
 * delay counter until the defined power-on delay period has expired.  
 *********************************************************************************/
volatile uint16_t SubState_PowerOnDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
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

        retval = BUCK_OPSRET_COMPLETE; 
    }
    else
    // When the period has not expired yet, return to this function
    {
        retval = BUCK_OPSRET_REPEAT;
    }    

    return(retval);
}

/*******************************************************************************
 * @fn volatile uint16_t SubState_PrepareVRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
 * @brief
 * @param	BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * @return  0=failure
 * @return  1=success
 * 
 * <b>Description</b><br> 
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
 *********************************************************************************/
volatile uint16_t SubState_PrepareVRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t _i=0;
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
    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC) 
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

        // Protect against negative duty cycle results
        if (_vout < _vin) _vout = _vin;
        
        // CALCULATE BUCK CONVERTER STARTUP DUTY RATIO 
        // DC = (VOUT-VIN) / VOUT, where DC = D * PERIOD
        
        _start_dc = __builtin_muluu((_vout-_vin), buckInstance->sw_node[0].period);
        _start_dc = __builtin_divud(_start_dc, (uint16_t)_vout);
    }
    else
    // If there is no input voltage or no output voltage, start with minimum duty ratio
    {
        for (_i=0; _i<BUCK_NO_OF_PHASES; _i++) {
            _start_dc = (uint16_t)buckInstance->sw_node[_i].duty_ratio_min;
        }
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
        if(buckInstance->v_loop.controller->Ports.AltTarget.ptrAddress != NULL)
            *buckInstance->v_loop.controller->Ports.AltTarget.ptrAddress = _start_dc; // set initial PWM duty ratio

    }
    else if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC) 
    {   
        // Limit startup duty cycle to largest minimum/smallest maximum
        for (_i=0; _i<BUCK_NO_OF_PHASES; _i++) {
            
            if(_start_dc < buckInstance->i_loop[_i].minimum) 
            { _start_dc = buckInstance->i_loop[_i].minimum; }
            else if(_start_dc > buckInstance->i_loop[_i].maximum) 
            { _start_dc = buckInstance->i_loop[_i].maximum; }
        }
        
        // Set initial duty cycle
        for (_i=0; _i<BUCK_NO_OF_PHASES; _i++) 
        {
            // pre-charge current loop control histories with ideal duty cycle
            buckInstance->i_loop[_i].ctrl_Precharge(
                        buckInstance->i_loop[_i].controller, 0, _start_dc
                    );

            // pre-charge PWM outputs with ideal duty cycle
            *buckInstance->i_loop[_i].controller->Ports.Target.ptrAddress = _start_dc; // set initial PWM duty ratio
            if(buckInstance->i_loop[_i].controller->Ports.AltTarget.ptrAddress != NULL)
                *buckInstance->i_loop[_i].controller->Ports.AltTarget.ptrAddress = _start_dc; // set initial PWM duty ratio
        }
    }
    else
    {
        return(BUCK_OPSRET_ERROR);
    }

    return(BUCK_OPSRET_COMPLETE);
    
}

/*******************************************************************************
 * @fn volatile uint16_t SubState_VRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
 * @brief
 * @param	BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * @return  0=failure
 * @return  1=success
 * 
 * <b>Description</b><br> 
 * This is the essential step in which the output voltage is ramped up by 
 * incrementing the outer control loop reference. In voltage mode the output  
 * voltage will ramp up to the nominal regulation point. 
 * In average current mode the inner loop will limit the voltage as soon as the 
 * current reference limit is hit and the output is switched to constant current 
 * mode.
 *********************************************************************************/

volatile uint16_t SubState_VRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    
    // Set BUSY bit until process is complete
    buckInstance->status.bits.busy = true;
    
    // ensure control loop is enabled
    if(!buckInstance->v_loop.controller->status.bits.enabled) {

        // Enable all PWM channels
        retval &= buckPWM_Resume(buckInstance);  // Enable PWM outputs

        // In voltage mode control...
        if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_VMC)
        {   // only enable voltage loop
            buckInstance->v_loop.controller->status.bits.enabled = true; // enable voltage loop controller
        }
        // In average current mode control...
        else if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC)
        {
            // enable voltage loop controller
            buckInstance->v_loop.controller->status.bits.enabled = true; 
            
            // enable all phase current loop controllers
            for (_i=0; _i<BUCK_NO_OF_PHASES; _i++) {
                buckInstance->i_loop[_i].controller->status.bits.enabled = true; 
            }
        }
        // IF control mode is set to unsupported control mode, return error
        else
        {
            return(BUCK_OPSRET_ERROR);
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

        retval = BUCK_OPSRET_COMPLETE;
        
    }
    else
    // remain in this state until ramp is complete
    {
        retval = BUCK_OPSRET_REPEAT;
    }

    
    return(retval);
    
}

/*******************************************************************************
 * @fn volatile uint16_t SubState_IRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
 * @brief
 * @param	BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * @return  0=failure
 * @return  1=success
 * 
 * <b>Description</b><br> 
 * This phase of the soft-start ramp is only executed in average current mode and 
 * will only take effect when the current limit is hit before the nominal voltage 
 * regulation point. In this case the constant output current is ramped up to from 
 * the startup current to the nominal constant charging current.
 *********************************************************************************/
volatile uint16_t SubState_IRampUp(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
{
    volatile uint16_t retval=0;
    
    // Set BUSY bit until process is complete
    buckInstance->status.bits.busy = true;

    // in average current mode if voltage limit is hit, increment 
    // voltage loop limit to ramp up current loop
    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC)
    {
        // Increment maximum current limit
        buckInstance->v_loop.controller->Limits.MaxOutput += buckInstance->startup.i_ramp.ref_inc_step; 

        if (buckInstance->v_loop.controller->Limits.MaxOutput >= buckInstance->set_values.i_ref)
        // check if ramp is complete
        {
            buckInstance->v_loop.maximum = buckInstance->set_values.i_ref;
            buckInstance->v_loop.controller->Limits.MaxOutput = buckInstance->v_loop.maximum;
            retval = BUCK_OPSRET_COMPLETE;
        }
        else
        // if ramp is not complete yet, remain in this state
        {
            retval = BUCK_OPSRET_REPEAT;
        }
    }
    else // Non-Current Loops Ending up here need to be lifted to PG_DELAY
    { 
        buckInstance->v_loop.controller->Limits.MaxOutput = buckInstance->v_loop.maximum;
        retval = BUCK_OPSRET_COMPLETE; 
    }

    return(retval);
    
}

/*******************************************************************************
 * @fn volatile uint16_t SubState_PowerGoodDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
 * @brief
 * @param	BUCK_POWER_CONTROLLER_s  pointer to buck converter data structure
 * @return  0=failure
 * @return  1=success
 * 
 * <b>Description</b><br> 
 * In this phase of the soft-start procedure a counter is incremented until the 
 * power good delay has expired before the soft-start process is marked as COMPLETED.
 * If option for driving a user-defined general purpose output (PG output) is enabled
 * in proprietary user code, this pin will be set automatically.
 *********************************************************************************/
volatile uint16_t SubState_PowerGoodDelay(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
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
                return(BUCK_OPSTATE_ERROR);
        }
        
        retval = BUCK_OPSRET_COMPLETE;
    }
    else
    // if period has not expired yet, remain in this state
    {
        retval = BUCK_OPSRET_REPEAT;
    }

    return(retval);
    
}

/**@}*/
// END OF FILE
