/*
 * File:   init_gpio.c
 * Author: M91406
 *
 * Created on July 8, 2019, 6:26 PM
 */


#include <xc.h>
#include "init_gpio.h"

/***********************************************************************************
 * @fn uint16_t sysGpio_Initialize(void)
 * @ingroup gpio-initialization
 * @brief  Resets the device input/output pins to digital inputs
 * @return unsigned integer (0=failure, 1=success)
 * 
 * @details
 *  When the device is coming out of RESET, all device pins are configured as
 *  inputs and all analog functions will be enabled. Enabled analog functions
 *  are a potential source for conflicts and are therefore turned off by default
 *  during device startup to allow all peripheral configuration drivers to start
 *  from a defined default state.
 *
 **********************************************************************************/

volatile uint16_t sysGpio_Initialize(void) {
    
    volatile uint16_t retval=1;

    // Reset all analog inputs to be Digital I/Os
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    
    return(retval);
}

// end of file
