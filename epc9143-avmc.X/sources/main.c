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


#define  TMR1_TIMEOUT 30000   // Timeout protection for Timer1 interrupt flag bit
volatile bool LOW_PRIORITY_GO = false;  // Flag allowing low priority tasks to be executed

int main(void) {

    volatile uint16_t retval=1;
    volatile uint16_t timeout = 0;
    
    // Initialize basic system configuration
    retval &= SYSTEM_Initialize();
    
    // Initialize software modules
    retval &= appPowerSupply_Initialize(); // Initialize BUCK converter object and state machine
    retval &= appFaultMonitor_Initialize(); // Initialize fault objects and fault handler task
    
    // Enable Timer1
    _T1IP = 0;  // Set interrupt priority to zero
    _T1IF = 0;  // Reset interrupt flag bit
    _T1IE = 0;  // Enable/Disable Timer1 interrupt
    T1CONbits.TON = 1; // Turn on Timer1
    retval &= T1CONbits.TON; // Add timer enable bit to list of checked bits
    
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




