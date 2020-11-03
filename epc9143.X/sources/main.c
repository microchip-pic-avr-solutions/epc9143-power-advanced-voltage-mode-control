/*
 * File:   main.c
 * Author: M91406
 *
 * Created on July 8, 2019, 1:52 PM
 */

/**
 * @mainpage EPC9143KIT : 300 W 1/16 th Brick Evaluation Module
 * @section overview Overview
 * Brick DC-DC converters are widely used in data center, telecommunication and
 *  automotive applications, converting a nominal 48 V to different output nominal
 *  voltages such as 5 V, 9 V or 12 V. The standard dimension of the 1/16th brick 
 * converter is 33 x 22.9 mm (1.3 x 0.9 inch). The EPC9143 1/16th brick power module
 *  reference design, developed in collaboration with Efficient Power Conversion Corp.
 *  EPC, is designed for 48 V to 12 V DC/DC applications. It features the EPC2053 
 * enhancement mode (eGaN) field effect transistors (FETs), as well as a Microchip 
 * dsPIC33CK32MP102 16-bit digital signal controller (DSC). The height limit for this 
 * design is set to 10 mm (0.4 inch)
 * 
 * The reference design firmware includes two modes of operation:
 * 
 *  - <b> Conventional Average Current Mode Control (ACMC):</b> Multiloop controller with 
 * one outer voltage loop providing the same current reference IREF to two independent
 *  inner current loops for each phase, supporting control bandwidths of 2 kHz
 * 
 *  - <b>Advanced Type IV Voltage Loop Control (AVMC) with Enforced Cycle-By-Cycle PWM 
 * Steering, Gain Modulation and Current Balancing:</b> A single, high-speed type IV 
 * voltage mode controller with enforced PWM steering is used to automatically create 
 * balanced phase currents in both phases of this interleaved converter. An underlying 
 * current balancing scheme compensates component tolerances and deviations over 
 * temperature. A built-in adaptive gain control algorithm stabilizes gain variations 
 * of the voltage loop controller during input- and output voltage transients, 
 * stabilizing cross-over frequency and output impedance, supporting control bandwidths 
 * of 25 kHz, for improved transient response, helping to minimize power distribution 
 * network (PDN) decoupling capacity
 * 
 * For more information on hardware related documentation, design files and purchasing 
 * information, please visit EPC?s product website: https://epc-co.com/epc/Products/DemoBoards/EPC9143.aspx
 * 
 * @section feature Product Feature
 * - Input Voltage: 18 to 61 V DC
 * - Output Voltage: 12 V DC
 * - Output Current: 25 A (max.)
 * - Operating Temperature: -40 to 110 C (Measured on FET package, airflow 800 LFM)
 * - High efficiency: 95.8% @ 12V/25A output
 * - Dimension: 33mm x 22.9 mm x 9 mm (1.30 in. x 0.90 in. x 0.35 in.)
 * - Industry standard footprint and pinout
 * - Positive logic Enable
 * - Power Good output
 * - Constant switching frequency: 500 kHz
 * - Remote Sense
 * - Re-programmable output voltage and protection thresholds
 * - Output voltage trimming
 * - Fault protection:
 *      - Input under voltage lock out (UVLO)
 *      - Input over voltage lock out (OVLO)
 *      - Output over current limit (OCL) (ACMC only)
 *      - Output over current protection (OCP) (AVMC only)
 *      - Regulation error (REGERR)
 * 
 * For evaluation purposes the 16th brick power module is mounted on the EPC9531 
 * test fixture, including the recommended 47uF of input capacitance and 220 uF of 
 * output capacitance, easy access to voltage sense test points as well as power 
 * and data connectors. The Microchip dsPIC33CK controller can be programmed using 
 * the in-circuit serial programming port (ICSP) available on the RJ-11 programming 
 * interface as well as the 5-pin header provided by the EPC9531 test fixture. These 
 * interfaces support all of Microchip?s in-circuit programmers/debuggers, such as 
 * MPLAB ICD4, MPLAB REAL ICE or MPLAB PICkit4 and previous derivatives.
 * 
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


