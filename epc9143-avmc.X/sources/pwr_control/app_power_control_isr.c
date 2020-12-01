/*
 * File:   app_power_control_isr.c
 * Author: M91406
 *
 * Created on May 26, 2020, 7:32 PM
 */


#include "config/hal.h"
#include "app_power_control.h"

/**
 * @addtogroup power-handler-functions
 * @{
 */
/*********************************************************************************
 * @fn void _BUCK_VLOOP_Interrupt(void)
 * @brief Main Control Interrupt
 * 
 * @param NONE
 * 
 * @return NONE
 *   
 * <b>Description<b><br>
 * The control interrupt is calling the control loop. The point in time where
 * this interrupt is thrown is determined by selecting the BUCK_VOUT_TRIGGER_MODE
 * option. 
 * 
 *********************************************************************************/

void __attribute__((__interrupt__, auto_psv, context))_BUCK_VLOOP_Interrupt(void)
{
    #ifdef DBGPIN1_Set
    DBGPIN1_Set();
    #endif
    
    buck.status.bits.adc_active = true;
    #if (PLANT_MEASUREMENT == false)
    buck.v_loop.ctrl_Update(buck.v_loop.controller);
    #else
    v_loop_PTermUpdate(&v_loop);
    #endif
    
    Nop(); // Debugging break point anchors
    Nop();
    Nop();
    
    // Clear the ADCANx interrupt flag 
    _BUCK_VLOOP_ISR_IF = 0;  
    
    #ifdef DBGPIN1_Set
    DBGPIN1_Clear();
    #endif
    
}
/**@}*/