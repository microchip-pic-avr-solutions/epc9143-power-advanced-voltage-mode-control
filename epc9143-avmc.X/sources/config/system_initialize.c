/*
 * File:   system_initialize.c
 * Author: M91406
 *
 * Created on November 12, 2020, 10:33 AM
 */

#include "hal.h"
#include "system_initialize.h"

/**
 * 
 * @addtogroup power_handler_function 
 * @{
 */
/***********************************************************************************
 * @fn volatile uint16_t SYSTEM_Initialize(void) 
 * @brief  
 * @param  
 * @return 
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
volatile uint16_t SYSTEM_Initialize(void) 
{
    volatile uint16_t retval=1;
	
    retval &= init_fosc();        // Set up system oscillator for 100 MIPS operation
    retval &= init_aclk();        // Set up Auxiliary PLL for 500 MHz (source clock to PWM module)
    retval &= init_timer1();      // Set up Timer1 as scheduler time base
    retval &= init_gpio();        // Initialize common device GPIOs
    
    retval &= init_opa(); // Initialize op-amp #2 used to drive the reference voltage for current sense amplifiers
    
    retval &= init_dac_module();  // Initialize DAC module
    retval &= init_dac_channel(1); // Initialize DAC #1 used to generate the reference voltage for current sense amplifiers
    retval &= init_dac_enable(); // Enable DAC setting the reference for current sense amplifiers
    
    
	return(retval);

}
/**@}*/