/*
 * File:   init_gpio.c
 * Author: M91406
 *
 * Created on July 8, 2019, 6:26 PM
 */


#include <xc.h>
#include "config/init/init_gpio.h"

volatile uint16_t init_gpio(void) {
    
    volatile uint16_t retval=1;
    
    // Reset all analog inputs to be Digital I/Os
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    
    // Initialize debugging Pins
    DBGPIN_1_INIT; ///< Device pin #1  (not routed)
    DBGPIN_2_INIT; ///< Device pin #2  (not routed)
    DBGPIN_3_INIT; ///< Device pin #25 (not routed)

    return(retval);
}
