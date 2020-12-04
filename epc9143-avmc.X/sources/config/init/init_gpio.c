/*
 * File:   init_gpio.c
 * Author: M91406
 *
 * Created on July 8, 2019, 6:26 PM
 */


#include <xc.h>
#include "config/init/init_gpio.h"

/**
 * @ingroup gpio-initialization
 * @{
 */

/***********************************************************************************
 * @fn DATA_TYPE FUNCTION_NAME
 * @brief  ADD_SHORT_DESCRIPTION/SUMMARY_HERE
 * @param  ADD_PARAMETER_HERE
 * @return DATA_TYPE SHORT_VALUE_DESCRIPTION
 * 
 * @details
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

volatile uint16_t sysGpio_Initialize(void) {
    
    volatile uint16_t retval=1;
    
    // Reset all analog inputs to be Digital I/Os
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    
    // Initialize debugging Pins
    #ifdef DBGPIN1_PIN
    DBGPIN1_Init(); ///< Device pin #1  (not routed)
    #endif
    #ifdef DBGPIN2_PIN
    DBGPIN2_Init(); ///< Device pin #2  (not routed)
    #endif
    #ifdef DBGPIN3_PIN
    DBGPIN3_Init(); ///< Device pin #25 (not routed)
    #endif

    return(retval);
}

/** @}*/ // end of group gpio-initialization

// end of file
