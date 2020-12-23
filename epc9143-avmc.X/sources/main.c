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

/* PRIVATE FUNCTION CALL PROTOTYPES */
volatile uint16_t sysLowPriorityTasks_Execute(void);
volatile uint16_t __attribute__((always_inline)) sysHighPriorityTasks_Execute(void);

/*******************************************************************************
 * @fn int main(void)
 * @ingroup firmware-flow
 * @brief  Application main function executed after device comes out of RESET
 * @return Signed Integer (0=failure, 1=success)
 * @details
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
 * - Operating System Timer
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
    
    // Initialize special, application-specific peripherals 
    retval &= sysUserPeriperhals_Initialize();

    // Initialize software modules
    retval &= sysUserTasks_Initialize();

    // Enable OS Timer
    retval &= sysOsTimer_Enable(true, 1);
    
    // Last line of defense:
    // when configuration of any block failed...
    if (!retval)
        CPU_RESET();        // reset the CPU and try again

    // Main program execution
    while (run_main) {

        // wait for Timer1 to overrun and the high-priority task interrupt to 
        // be executed
        while ((!LOW_PRIORITY_GO) && (timeout++ < TMR1_TIMEOUT));
        LOW_PRIORITY_GO = false;
        timeout = 0;    // Reset timeout counter

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Execute non-time critical, low-priority tasks
            
        retval &= sysLowPriorityTasks_Execute();
            
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    }

    CPU_RESET();    // if the firmware ever ends up here, reset the CPU
    
    return (0);
}

/**********************************************************************************
 * @fn      uint16_t sysLowPriorityTasks_Execute(void)
 * @ingroup main-loop-low-priority
 * @brief   Low priority task sequence executed after the high priority task sequence execution is complete
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * This application executes different tasks of which some are time 
 * critical while others are insensitive to execution time jitter. 
 * This function is calling all non-time critical tasks. it is called
 * after all high-priority tasks have been executed. 
 * 
 * @note
 *  (this application does not execute low priority tasks)
 * 
 * ********************************************************************************/

volatile uint16_t sysLowPriorityTasks_Execute(void)
{
    volatile uint16_t retval=1;
    
    // (no low priority tasks)
    
    return(retval);
}


/**********************************************************************************
 * @fn      uint16_t sysHighPriorityTasks_Execute(void)
 * @ingroup main-loop-high-priority
 * @brief   High priority task sequence executed at a fixed repetition frequency
 * @return  unsigned integer (0=failure, 1=success)
 * 
 * @details
 * This application executes different tasks of which some are time 
 * critical while others are insensitive against execution period or
 * execution repetition frequency jitter. 
 * 
 * The following function calls a sequence of time critical tasks. This
 * function is called by an interrupt service routine at a higher priority
 * than the main loop, enforcing a more time stringent execution repetition 
 * frequency.
 * 
 * ********************************************************************************/

volatile uint16_t sysHighPriorityTasks_Execute(void)
{
    volatile uint16_t retval=1;
    
    // Execute high priority, time critical tasks
    retval &= appPowerSupply_Execute();   // Execute power supply state machine
    retval &= appFaultMonitor_Execute();  // Execute fault handler
    
    return(retval);
}


/**********************************************************************************
 * @fn     void _OsTimerInterrupt(void)
 * @brief  High priority task sequence executed on a fixed 100 usec pace
 * 
 * @details
 * This interrupt is used to call the high priority task sequence at a fixed
 * repetition frequency of 10 kHz (= 100 us period). 
 * 
 * ********************************************************************************/

void __attribute__((__interrupt__, context, no_auto_psv)) _OsTimerInterrupt(void)
{
    #ifdef DBGPIN2_Set
    DBGPIN2_Set();              // Set the CPU debugging pin HIGH
    #endif

    sysHighPriorityTasks_Execute(); // Execute list of high priority tasks
    
    LOW_PRIORITY_GO = true; // Set GO trigger for low priority tasks
    _OSTIMER_IF = 0; // Reset the interrupt flag bit

    #ifdef DBGPIN2_Set
    DBGPIN2_Clear();            // Clear the CPU debugging pin
    #endif
    
    return;
}

// ______________________________________
// end of file



