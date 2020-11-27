/*
 * File:   init_timer1.c
 * Author: M91406
 *
 * Created on July 8, 2019, 2:47 PM
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "config/hal.h"
#include "config/init/init_timer1.h"   

volatile uint16_t sysOsTimer_Initialize (void)
{
    volatile uint16_t retval=1;

    T1CONbits.TON = 0;  // Timer1 On: Stops 16-bit Timer1 during configuration
    T1CONbits.TSIDL = 0; // Timer1 Stop in Idle Mode: Continues module operation in Idle mode
    T1CONbits.TMWDIS = 0; // Asynchronous Timer1 Write Disable: Back-to-back writes are enabled in Asynchronous mode
    T1CONbits.TMWIP = 0; // Asynchronous Timer1 Write in Progress: Write to the timer in Asynchronous mode is complete
    T1CONbits.PRWIP = 0; // Asynchronous Period Write in Progress: Write to the Period register in Asynchronous mode is complete
    T1CONbits.TECS = 0b11; // Timer1 Extended Clock Select: FRC clock
    T1CONbits.TGATE = 0; // Timer1 Gated Time Accumulation Enable: Gated time accumulation is disabled when TCS = 0
    T1CONbits.TCKPS = 0; // Timer1 Input Clock Prescale Select: 1:1
    T1CONbits.TSYNC = 0; // Timer1 External Clock Input Synchronization Select: Does not synchronize the External Clock input
    T1CONbits.TCS = 0; // Timer1 Clock Source Select: Internal peripheral clock
    
    // Reset Timer Counter Register TMR to Zero; 
    TMR1 = 0x00;
    //Period = 0.0001 s; Frequency = 100000000 Hz; PR 9999; 
    PR1 = MAIN_EXEC_PER;
    
    // Reset interrupt and interrupt flag bit
    _T1IP = 0;  // Set interrupt priority to zero
    _T1IF = 0;  // Reset interrupt flag bit
    _T1IE = 0;  // Disable Timer1 interrupt
   
    return(retval);
}

volatile uint16_t sysOsTimer_Enable (volatile bool interrupt_enable, volatile uint8_t interrupt_priority)
{
    volatile uint16_t retval=1;

    // Enable Timer1
    _T1IP = interrupt_priority;  // Set interrupt priority to zero
    _T1IF = 0;  // Reset interrupt flag bit
    _T1IE = interrupt_enable;  // Enable/Disable Timer1 interrupt
    T1CONbits.TON = 1; // Turn on Timer1
    retval &= T1CONbits.TON; // Add timer enable bit to list of checked bits
    
    return(retval);
}