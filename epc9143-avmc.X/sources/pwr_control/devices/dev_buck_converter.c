/*
 * File:   dev_buck_converter.c
 * Author: M91406
 *
 * Created on July 9, 2019, 1:10 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer types header file
#include <stdbool.h> // include standard boolean types header file

#include "dev_buck_typedef.h"
#include "dev_buck_opstates.h"
#include "dev_buck_pconfig.h"

/**\fn drv_BuckConverter_Initialize
 * ********************************************************************************
 * \brief
 * 
 * \param
 * 
 * \return
 * 
 * Description:
 * 
 * See also:
 *   drv_BuckConverter_Execute
 * 
 * ********************************************************************************/



/* @@drv_BuckConverter_Initialize
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * See also:
 *   drv_BuckConverter_Execute
 * 
 * ********************************************************************************/

volatile uint16_t drv_BuckConverter_Initialize(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) 
{
    volatile uint16_t retval = 1;
    volatile uint16_t _i=0;
    
    retval &= buckPWM_ModuleInitialize(buckInstance); // Initialize PWM Module
    retval &= buckPWM_ChannelInitialize(buckInstance);  // Initialize PWM Channel of Buck Converter
    
    retval &= buckADC_ModuleInitialize();     // Initialize ADC Module
    
    retval &= buckADC_ChannelInitialize(&buckInstance->feedback.ad_temp); // Initialize Temperature Channel
    retval &= buckADC_ChannelInitialize(&buckInstance->feedback.ad_vin);  // Initialize Input Voltage Channel
    retval &= buckADC_ChannelInitialize(&buckInstance->feedback.ad_vout); // Initialize Output Voltage Channel
    
    for (_i=0; _i<buckInstance->set_values.phases; _i++) // Reset phase current values
        retval &= buckADC_ChannelInitialize(&buckInstance->feedback.ad_isns[_i]); // Initialize Phase Current Channel
    
    retval &= buckGPIO_Initialize(buckInstance); // Initialize additional control IOs

    
    buckInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    
    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC) { // In current mode...
     
        for (_i=0; _i<buckInstance->set_values.phases; _i++) // Reset phase current values
        { buckInstance->i_loop[_i].controller->status.bits.enabled = false; } // Disable current loop
    
    }
        
    buckInstance->status.bits.enabled = false;  // Disable Buck Converter
    buckInstance->state_id.value = BUCK_OPSTATE_INITIALIZE; // Reset state machine
    
    return(retval);
}

/* @@drv_BuckConverter_Execute
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t drv_BuckConverter_Execute(volatile struct BUCK_POWER_CONTROLLER_s * buckInstance) 
{
    volatile uint16_t retval=1;
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* DISABLE-RESET                                                                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    // When enable status has changed from ENABLED to DISABLED, reset the state machine
    if ((!buckInstance->status.bits.enabled) || 
        (buckInstance->status.bits.fault_active))
    {
        if (!buckInstance->status.bits.ready)
            buckInstance->state_id.value = BUCK_OPSTATE_INITIALIZE;
        else
            buckInstance->state_id.value = BUCK_OPSTATE_RESET;
    }    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* FUNCTION CALL PROTECTION                                                           */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(buckInstance->state_id.bits.opstate_id >= BuckStateList_size)
        buckInstance->state_id.value = BUCK_OPSTATE_INITIALIZE;
    
    if(buckInstance == NULL)
        return(0);
    
    if (BuckConverterStateMachine[buckInstance->state_id.bits.opstate_id] == NULL)
        return(0);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    // Execute state machine step
    retval = BuckConverterStateMachine[buckInstance->state_id.bits.opstate_id](buckInstance);
    
    switch (retval) 
    {
        /* If state machine state returns ERROR, switch to ERROR state in next execution cycle */
        case BUCK_OPSRET_ERROR:
            
            buckInstance->state_id.value = BUCK_OPSTATE_ERROR;
            retval = 0;
            break;
            
        /* IF state machine state signals state completion, move on to next state in line */
        case BUCK_OPSRET_COMPLETE:
            
            if (++buckInstance->state_id.value >= BuckStateList_size)
                buckInstance->state_id.value = BUCK_OPSTATE_RESET;

            retval = 1;
            break;
            
        /* When state machine state returns REPEAT, the recent state function will be called again */
        case BUCK_OPSRET_REPEAT:
            
            retval = 1;
            break;
            
        /* When state machine state returns an unknown result, the 
         * state machine will be reset to INITIALIZE again */
        default:
            
            buckInstance->state_id.value = BUCK_OPSTATE_INITIALIZE;
            retval = 0;
            break;
    }

    return(retval);
}

/* @@drv_BuckConverter_Start
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t drv_BuckConverter_Start(volatile struct BUCK_POWER_CONTROLLER_s * buckInstance) {

    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    
    // Disable control loops
    buckInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    buckInstance->v_loop.ctrl_Reset(buckInstance->v_loop.controller); // Reset voltage loop histories

    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC) { // In current mode...
        
        for (_i=0; _i<buckInstance->set_values.no_of_phases; _i++)
        { 
            buckInstance->i_loop[_i].controller->status.bits.enabled = false; // Disable current loop
            buckInstance->i_loop[_i].ctrl_Reset(buckInstance->i_loop[_i].controller); // Reset current loop histories
        }
    }
    
    // Sequence PWM and ADC peripheral startup
    retval &= buckPWM_Start(buckInstance);   // Start PWM (All Outputs Disabled)
    if (retval) buckInstance->status.bits.pwm_active = 1;
    retval &= buckADC_Start();              // Start ADC

    // Enable buck converter and reset state machine to INITIALIZE
    buckInstance->status.bits.enabled = true;   // Enable Buck Converter
    buckInstance->state_id.value = BUCK_OPSTATE_INITIALIZE; // Reset state machine

    return(retval);
}

/* @@drv_BuckConverter_Stop
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t drv_BuckConverter_Stop(volatile struct BUCK_POWER_CONTROLLER_s * buckInstance) {

    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    
    // Stop PWM completely (shuts down PWM generator)
    retval &= buckPWM_Stop(buckInstance); // Stop PWM
    
    buckInstance->v_loop.controller->status.bits.enabled = false; // Disable voltage loop
    
    if (buckInstance->set_values.control_mode == BUCK_CONTROL_MODE_ACMC) {// In current mode...
        for (_i=0; _i<buckInstance->set_values.no_of_phases; _i++)
        { buckInstance->i_loop[_i].controller->status.bits.enabled = false; } // Disable current loop
    }
    
    buckInstance->status.bits.enabled = false;  // Disable Buck Converter
    buckInstance->state_id.value = BUCK_OPSTATE_INITIALIZE; // Reset state machine

    return(retval);
}

/* @@drv_BuckConverter_Suspend
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t drv_BuckConverter_Suspend(volatile struct BUCK_POWER_CONTROLLER_s * buckInstance) {
    
    volatile uint16_t retval=1;
    
    buckInstance->state_id.value = BUCK_OPSTATE_RESET;  // Reset running state machine
    retval &= drv_BuckConverter_Execute(buckInstance);  // Enforce state switch immediately
    
    return(retval);
}

/* @@drv_BuckConverter_Resume
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t drv_BuckConverter_Resume(volatile struct BUCK_POWER_CONTROLLER_s * buckInstance) {
    
    volatile uint16_t retval=1;
    
    buckInstance->state_id.value = BUCK_OPSTATE_RESET;  // Reset running state machine
    retval &= drv_BuckConverter_Execute(buckInstance);  // Enforce state switch immediately
    
    return(retval);
}

// END OF FILE
