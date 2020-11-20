/*
 * File:   main.c
 * Author: M91406
 *
 * Created on July 8, 2019, 1:52 PM
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer types header file
#include <stdbool.h> // include standard boolean types header file

#include "main.h"

volatile bool run_main = true; // Flag allowing to terminate the main loop and restart the CPU

#define  TMR1_TIMEOUT 30000   // Timeout protection for Timer1 interrupt flag bit
volatile bool LOW_PRIORITY_GO = false;  // Flag allowing low priority tasks to be executed

/**
 * @addtogroup Firmware_Flow
 * @{
 * @dotfile 
 */
/*******************************************************************************
 * @fn int main(void)
 * @param	(none)
 * @return  Signed Integer (0=failure, 1=success)
 *
 * @brief   Application main function executed after device comes out of RESET
 * 
 * <b>Description</b> 
 * This function is the starting point of the firmware. It is called after the
 * device is coming out of RESET, starting to execute code. The startup sequence 
 * is as follows:
 * 
 * 1) SYSTEM_Initialize:
 * 
 * a) Configures the fundamental system components such as 
 * 
 * Fundamental components are peripherals which are essential for the CPU to run,
 * such as
 * 
 * - system oscillator
 * - auxiliary oscillator
 * - general purpose input/output configuration
 * - task timer (used as time base for task control)
 *      
 * b) User-defined Peripheral Module Configurations
 * 
 * This hardware requires some specific peripheral modules to support circuit 
 * functions, such as
 * 
 * - Digital-To-Analog Converter (DAC):
 * This peripheral instance is used to provide the reference voltage 
 * to two external shunt amplifier devices U61 and U62 (PartNo. MCP6C02)
 * 
 * - Operational Amplifier (OPA)
 * This reference signal generated by the DAC  is buffered by one of the 
 * internal operational amplifiers to stabilize the reference voltage when 
 * routed across the board.
 *          
 * 2) Software Modules Initialization
 * 
 * This application runs two major tasks:
 * 
 * - Power Supply State Machine & Control 
 * - System Fault Handler & Diagnostics
 * 
 * Each 'Task' is an independent process which is called with a fixed execution
 * frequency. The default frequency set in this code version is 100 usec (= 10 kHz).
 * In each step both tasks are executed one after another in one sequence. 
 * 
 *********************************************************************************/
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
    while (run_main) {

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

/**@}*/
// ______________________________________
// END OF FILE




