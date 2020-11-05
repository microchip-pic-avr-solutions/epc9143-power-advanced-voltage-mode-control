/*
 * File:   main.c
 * Author: M91406
 *
 * Created on July 8, 2019, 1:52 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"

#include "config/init/init_fosc.h"
#include "config/init/init_timer1.h"
#include "config/init/init_gpio.h"

#include "config/init/init_opa.h"
#include "config/init/init_dac.h"

#define  TMR1_TIMEOUT 30000   // Timeout protection for Timer1 interrupt flag bit
volatile bool LOW_PRIORITY_GO = false;  // Flag allowing low priority tasks to be executed

int main(void) {

    volatile uint16_t retval=1;
    volatile uint16_t timeout = 0;
    
    retval &= init_fosc();        // Set up system oscillator for 100 MIPS operation
    retval &= init_aclk();        // Set up Auxiliary PLL for 500 MHz (source clock to PWM module)
    retval &= init_timer1();      // Set up Timer1 as scheduler time base
    retval &= init_gpio();        // Initialize common device GPIOs
    
    DBGPIN_2_SET;         // Set the CPU debugging pin HIGH
    
    retval &= init_opa(); // Initialize op-amp #2 used to drive the reference voltage for current sense amplifiers
    
    retval &= init_dac_module();  // Initialize DAC module
    retval &= init_dac_channel(1); // Initialize DAC #1 used to generate the reference voltage for current sense amplifiers
    retval &= init_dac_enable(); // Enable DAC setting the reference for current sense amplifiers
    
    retval &= appPowerSupply_Initialize(); // Initialize BUCK converter object and state machine
    retval &= appFaultMonitor_Initialize(); // Initialize fault objects and fault handler task
    
    // Enable Timer1
    _T1IP = 0;  // Set interrupt priority to zero
    _T1IF = 0;  // Reset interrupt flag bit
    _T1IE = 0;  // Enable/Disable Timer1 interrupt
    T1CONbits.TON = 1; // Turn on Timer1
    retval &= T1CONbits.TON; // Add timer enable bit to list of checked bits
    
    DBGPIN_2_CLEAR;         // Clear the CPU debugging pin

    // Last line of defense: when configuration of any block failed 
    if (!retval)
        CPU_RESET();        // reset the CPU and try again

    // Main program execution
    while (1) {

        // wait for timer1 to overrun
        while ((!_T1IF) && (timeout++ < TMR1_TIMEOUT));
        _T1IF = 0;
        timeout = 0;    // Reset timeout counter

        // Execute main application tasks
        DBGPIN_2_SET;               // Set the CPU debugging pin HIGH

        appPowerSupply_Execute();   // Execute power supply state machine
        appFaultMonitor_Execute();        // Execute fault handler

        DBGPIN_2_CLEAR;             // Clear the CPU debugging pin
        
        Nop();                      // No-Operation instruction for placing breakpoints
    }

    CPU_RESET();    // if the firmware ever ends up here, reset the CPU
    
    return (0);
}

// END OF FILE


