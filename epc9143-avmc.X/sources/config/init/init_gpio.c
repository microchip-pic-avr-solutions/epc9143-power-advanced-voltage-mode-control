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
    DBGPIN_1_INIT;
    DBGPIN_2_INIT;
    DBGPIN_3_INIT;

    // Map PWM4H/L outputs to pins RB8/9
    // ToDo: Move hard-coded peripheral and pin assignments to hardware abstraction layer files
    _LATB8 = 0;
    _TRISB8 = 0;
    _LATB9 = 0;
    _TRISB9 = 0;
    
    __builtin_write_RPCON(0x0000); // unlock PPS
    _RP41R = 34; // Map PWM4H to RP44 (tied to RB9 Output)
    _RP40R = 35; // Map PWM4L to RP45 (tied to RB8 Output)
    __builtin_write_RPCON(0x0800); // lock PPS
    
    return(retval);
}
