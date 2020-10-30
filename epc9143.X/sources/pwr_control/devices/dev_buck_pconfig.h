/**
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms, you may use Microchip software
 *  and any derivatives exclusively with Microchip products. You're responsible
 *  for complying with 3rd party license terms applicable to your use of 3rd
 *  party software (including open source software) that may accompany Microchip
 *  software.
 *
 *  SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 *  APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 *  MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
 *  HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
 *  THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 *  CLAIMS RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY,
 *  YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 *  @file    dev_buck_pconfig.h
 *  @brief   This file contains APIs to for the power control
 *
 *  @note
 *  Microchip Technology Inc. has followed development methods required by
 *  IEC-60730 and performed extensive validation and static testing to ensure
 *  that the code operates as intended. Any modification to the code can
 *  invalidate the results of Microchip's validation and testing.
 *
 */

/* 
 * File:   dev_buck_pconfig.h
 * Author: M91406
 * Comments: Peripheral configuration template header file for generic buck converter driver
 * Revision history: 
 * 1.0  initial release
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BUCK_CONVERTER_PERIPHERAL_CONFIGURAITON_H
#define	BUCK_CONVERTER_PERIPHERAL_CONFIGURAITON_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "dev_buck_typedef.h"
#include "xc16_pral.h"

/* ********************************************************************************
 * *******************************************************************************/

extern volatile uint16_t buckGPIO_Initialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t buckGPIO_Set(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance);
extern volatile uint16_t buckGPIO_Clear(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance);
extern volatile bool     buckGPIO_GetPinState(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance);

/* ********************************************************************************
 * PWM GENERATOR CONFIGURATION
 * *******************************************************************************/
/* PCLKCON: PWM CLOCK CONTROL REGISTER

                           ________________ BIT 15: HRRDY: High-Resolution Ready bit
                          | _______________ BIT 14: HRERR: High-Resolution Error bit
                          || ______________ BIT 13: (unimplemented) 
                          ||| _____________ BIT 12: (unimplemented) 
                          |||| ____________ BIT 11: (unimplemented) 
                          ||||| ___________ BIT 10: (unimplemented)
                          |||||| __________ BIT  9: (unimplemented)
                          ||||||| _________ BIT  8: LOCK: Lock bit
                          |||||||| ________ BIT  7: (unimplemented)
                          ||||||||| _______ BIT  6: (unimplemented)
                          |||||||||| ______ BIT  5: DIVSEL[1:0]: PWM Clock Divider Selection bits
                          ||||||||||| _____ BIT  4: 
                          |||||||||||| ____ BIT  3: (unimplemented)
                          ||||||||||||| ___ BIT  2: (unimplemented)
                          |||||||||||||| __ BIT  1: MCLKSEL[1:0]: PWM Master Clock Selection bits
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PCLKCON     0b0000000000000011

// PWM module default configuration
volatile struct P33C_PWM_MODULE_s buckPwmModuleConfig = 
{
        .vPCLKCON.value = REG_PCLKCON,  // PCLKCON: PWM CLOCK CONTROL REGISTER
        .vFSCL.value = 0,               // FSCL: FREQUENCY SCALE REGISTER
        .vFSMINPER.value = 0,           // FSMINPER: FREQUENCY SCALING MINIMUM PERIOD REGISTER
        .vMPHASE.value = 0,             // MPHASE: MASTER PHASE REGISTER
        .vMDC.value = 0,                // MDC: MASTER DUTY CYCLE REGISTER
        .vMPER.value = 0,               // MPER: MASTER PERIOD REGISTER
        .vLFSR.value = 0,               // LFSR: LINEAR FEEDBACK SHIFT REGISTER
        .vCMBTRIGL.value = 0,           // CMBTRIGL: COMBINATIONAL TRIGGER REGISTER LOW
        .vCMBTRIGH.value = 0,           // CMBTRIGH: COMBINATIONAL TRIGGER REGISTER HIGH
        .LOGCON_A.value = 0,            // LOGCONA: COMBINATORIAL PWM LOGIC CONTROL REGISTER A
        .LOGCON_B.value = 0,            // LOGCONB: COMBINATORIAL PWM LOGIC CONTROL REGISTER B
        .LOGCON_C.value = 0,            // LOGCONC: COMBINATORIAL PWM LOGIC CONTROL REGISTER C
        .LOGCON_D.value = 0,            // LOGCOND: COMBINATORIAL PWM LOGIC CONTROL REGISTER D
        .LOGCON_E.value = 0,            // LOGCONE: COMBINATORIAL PWM LOGIC CONTROL REGISTER E
        .LOGCON_F.value = 0,            // LOGCONF: COMBINATORIAL PWM LOGIC CONTROL REGISTER F
        .PWMEVT_A.value = 0,            // PWMEVTA: PWM EVENT OUTPUT CONTROL REGISTER A
        .PWMEVT_B.value = 0,            // PWMEVTB: PWM EVENT OUTPUT CONTROL REGISTER B
        .PWMEVT_C.value = 0,            // PWMEVTC: PWM EVENT OUTPUT CONTROL REGISTER C
        .PWMEVT_D.value = 0,            // PWMEVTD: PWM EVENT OUTPUT CONTROL REGISTER D
        .PWMEVT_E.value = 0,            // PWMEVTE: PWM EVENT OUTPUT CONTROL REGISTER E
        .PWMEVT_F.value = 0             // PWMEVTF: PWM EVENT OUTPUT CONTROL REGISTER F
    };


/* ********************************************************************************
 * PWM GENERATOR CONFIGURATION
 * *******************************************************************************/
    
#define P33C_PGxCONL_PWM_ON     0x8000  // control bit in PGxCONL enabling/disabling the PWM generator
#define P33C_PGxCONL_HRES_EN    0x0080  // control bit in PGxCONL enabling/disabling High Resolution Mode
#define P33C_PGxIOCONL_OVREN    0x3000  // control bits in PGxIOCONL enabling/disabling the PWM output override
#define P33C_PGxIOCONH_PEN      0x000C  // control bits in PGxIOCONH enabling/disabling the PWM outputs
#define P33C_PGxSTAT_UPDREQ     0x0008  // Control bit in PGxSTAT setting the Update Request bit
#define P33C_PGxCONH_MPERSEL    0x4000  // Control bit in PGxCONH seting the PERIOD register source
    
#define P33C_PGxCONH_UPDMOD_MSTR 0b001  // Master Immediate Update
#define P33C_PGxCONH_UPDMOD_SLV  0b011  // Slaved immediate Update

// ==============================================================================================
// BUCK converter Peripheral Configuration for Voltage and Average Current Mode Control
// ==============================================================================================

/* PGxCONL: PWM GENERATOR x CONTROL REGISTER LOW

                           ________________ BIT 15: ON: Enable: PWM Generator Enable
                          | _______________ BIT 14: (reserved) 
                          || ______________ BIT 13: (unimplemented) 
                          ||| _____________ BIT 12: (unimplemented) 
                          |||| ____________ BIT 11: (unimplemented) 
                          ||||| ___________ BIT 10: TRGCNT[2:0]: Trigger Count Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: HREN: PWM Generator x High-Resolution Enable
                          ||||||||| _______ BIT  6: (unimplemented)
                          |||||||||| ______ BIT  5: (unimplemented)
                          ||||||||||| _____ BIT  4: CLKSEL[1:0]: Clock Selection
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: MODSEL[2:0]: Mode Selection
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxCONL     0b0000000010001000
    
/* PGxCONH: PWM GENERATOR x CONTROL REGISTER HIGH

                           ________________ BIT 15: MDCSEL: Master Duty Cycle Register Selection: 0 = PWM Generator uses PGxDC register
                          | _______________ BIT 14: MPERSEL: Master Period Register Selection: 1 = PWM Generator uses MPER register
                          || ______________ BIT 13: MPHSEL: Master Phase Register Selection: 0 = PWM Generator uses PGxPHASE register
                          ||| _____________ BIT 12: (unimplemented) 
                          |||| ____________ BIT 11: MSTEN: Master Update Enable: 0 = PWM Generator does not broadcast the UPDREQ status bit state or EOC signal
                          ||||| ___________ BIT 10: UPDMOD[2:0]: PWM Buffer Update Mode Selection: 001 = Immediate update
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: (reserved)
                          ||||||||| _______ BIT  6: TRGMOD: PWM Generator Trigger Mode Selection: PWM Generator operates in Retriggerable mode
                          |||||||||| ______ BIT  5: (unimplemented)
                          ||||||||||| _____ BIT  4: (unimplemented)
                          |||||||||||| ____ BIT  3: SOCS[3:0]: Start-of-Cycle Selection: Local EOC ? PWM Generator is self-triggered
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxCONH     0b0000000100000000


/* PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER LOW

                           ________________ BIT 15: CLMOD: Current-Limit Mode Selection
                          | _______________ BIT 14: SWAP: Swap PWM Signals to PWMxH and PWMxL Device Pins
                          || ______________ BIT 13: OVRENH: User Override Enable for PWMxH Pin
                          ||| _____________ BIT 12: OVRENL: User Override Enable for PWMxL Pin
                          |||| ____________ BIT 11: OVRDAT[1:0]: Data for PWMxH/PWMxL Pins if Override is Enabled
                          ||||| ___________ BIT 10: 
                          |||||| __________ BIT  9: OSYNC[1:0]: User Output Override Synchronization Control
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: FLTDAT[1:0]: Data for PWMxH/PWMxL Pins if Fault Event is Active
                          ||||||||| _______ BIT  6: 
                          |||||||||| ______ BIT  5: CLDAT[1:0]: Data for PWMxH/PWMxL Pins if Current-Limit Event is Active
                          ||||||||||| _____ BIT  4: 
                          |||||||||||| ____ BIT  3: FFDAT[1:0]: Data for PWMxH/PWMxL Pins if Feed-Forward Event is Active
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: DBDAT[1:0]: Data for PWMxH/PWMxL Pins if Debug Mode is Active
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxIOCONL   0b0011000000000000

   
/* PGxIOCONH: PWM GENERATOR x I/O CONTROL REGISTER HIGH

                           ________________ BIT 15: (unimplemented)
                          | _______________ BIT 14: CAPSRC[2:0]: Time Base Capture Source Selection
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: (unimplemented)
                          ||||| ___________ BIT 10: (unimplemented)
                          |||||| __________ BIT  9: (unimplemented)
                          ||||||| _________ BIT  8: DTCMPSEL: Dead-Time Compensation Select
                          |||||||| ________ BIT  7: (unimplemented)
                          ||||||||| _______ BIT  6: (unimplemented)
                          |||||||||| ______ BIT  5: PMOD[1:0]: PWM Generator Output Mode Selection
                          ||||||||||| _____ BIT  4: 
                          |||||||||||| ____ BIT  3: PENH: PWMxH Output Port Enable
                          ||||||||||||| ___ BIT  2: PENL: PWMxL Output Port Enable
                          |||||||||||||| __ BIT  1: POLH: PWMxH Output Polarity
                          ||||||||||||||| _ BIT  0: POLL: PWMxL Output Polarity
                          ||||||||||||||||  */
#define REG_PGxIOCONH   0b0000000000000000

/* PGxEVTL: PWM GENERATOR x EVENT REGISTER LOW

                           ________________ BIT 15: ADTR1PS[4:0]: ADC Trigger 1 Postscaler Selection
                          | _______________ BIT 14: 
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: 
                          ||||| ___________ BIT 10: ADTR1EN3: ADC Trigger 1 Source is PGxTRIGC Compare Event Enable
                          |||||| __________ BIT  9: ADTR1EN2: ADC Trigger 1 Source is PGxTRIGB Compare Event Enable
                          ||||||| _________ BIT  8: ADTR1EN1: ADC Trigger 1 Source is PGxTRIGA Compare Event Enable
                          |||||||| ________ BIT  7: (unimplemented)
                          ||||||||| _______ BIT  6: (unimplemented)
                          |||||||||| ______ BIT  5: (unimplemented)
                          ||||||||||| _____ BIT  4: UPDTRG[1:0]: Update Trigger Selection
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: PGTRGSEL[2:0]: PWM Generator Trigger Output Selection
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxEVTL     0b0000000100011001


/* PGxEVTH: PWM GENERATOR x EVENT REGISTER HIGH

                           ________________ BIT 15: FLTIEN: PCI Fault Interrupt Enable
                          | _______________ BIT 14: CLIEN: PCI Current-Limit Interrupt Enable
                          || ______________ BIT 13: FFIEN: PCI Feed-Forward Interrupt Enable
                          ||| _____________ BIT 12: SIEN: PCI Sync Interrupt Enable
                          |||| ____________ BIT 11: (unimplemented)
                          ||||| ___________ BIT 10: (unimplemented)
                          |||||| __________ BIT  9: IEVTSEL[1:0]: Interrupt Event Selection = Interrupts CPU at TRIGA compare event
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: ADTR2EN3: ADC Trigger 2 Source is PGxTRIGC Compare Event Enable
                          ||||||||| _______ BIT  6: ADTR2EN2: ADC Trigger 2 Source is PGxTRIGB Compare Event Enable
                          |||||||||| ______ BIT  5: ADTR2EN1: ADC Trigger 2 Source is PGxTRIGA Compare Event Enable
                          ||||||||||| _____ BIT  4: ADTR1OFS[4:0]: ADC Trigger 1 Offset Selection
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxEVTH     0b0000000101000000


/* PGxCLPCIL: PWM GENERATOR CURRENT LIMIT PCI REGISTER LOW

                           ________________ BIT 15: TSYNCDIS: Termination Synchronization Disable
                          | _______________ BIT 14: TERM[2:0]: Termination Event Selection
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: AQPS: Acceptance Qualifier Polarity Selection
                          ||||| ___________ BIT 10: AQSS[2:0]: Acceptance Qualifier Source Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: SWTERM: PCI Software Termination
                          ||||||||| _______ BIT  6: PSYNC: PCI Synchronization Control
                          |||||||||| ______ BIT  5: PPS: PCI Polarity Selection
                          ||||||||||| _____ BIT  4: PSS[4:0]: PCI Source Selection
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0:                
                          ||||||||||||||||  */
//#define REG_PGxCLPCIL   0b0001101000011011    // Peak Current Mode Configuration
#define REG_PGxCLPCIL   0b0000000000000000    
    
/* PGxCLPCIH: PWM GENERATOR CURRENT LIMIT PCI REGISTER HIGH

                           ________________ BIT 15: BPEN: PCI Bypass Enable
                          | _______________ BIT 14: BPSEL[2:0]: PCI Bypass Source Selection
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: (unimplemented)
                          ||||| ___________ BIT 10: ACP[2:0]: PCI Acceptance Criteria Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: SWPCI: Software PCI Control
                          ||||||||| _______ BIT  6: SWPCIM[1:0]: Software PCI Control Mode
                          |||||||||| ______ BIT  5: 
                          ||||||||||| _____ BIT  4: LATMOD: PCI SR Latch Mode
                          |||||||||||| ____ BIT  3: TQPS: Termination Qualifier Polarity Selection
                          ||||||||||||| ___ BIT  2: TQSS[2:0]: Termination Qualifier Source Selection
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
//#define REG_PGxCLPCIH   0b0000011000000000  // Peak Current Mode Configuration
#define REG_PGxCLPCIH   0b0000000000000000  

/* PGxFPCIL: PWM GENERATOR FAULT PCI REGISTER LOW

                           ________________ BIT 15: TSYNCDIS: Termination Synchronization Disable
                          | _______________ BIT 14: TERM[2:0]: Termination Event Selection
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: AQPS: Acceptance Qualifier Polarity Selection
                          ||||| ___________ BIT 10: AQSS[2:0]: Acceptance Qualifier Source Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: SWTERM: PCI Software Termination
                          ||||||||| _______ BIT  6: PSYNC: PCI Synchronization Control
                          |||||||||| ______ BIT  5: PPS: PCI Polarity Selection
                          ||||||||||| _____ BIT  4: PSS[4:0]: PCI Source Selection
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxFPCIL    0b0000000000000000
    
/* PGxFPCIH: PWM GENERATOR FAULT PCI REGISTER HIGH

                           ________________ BIT 15: BPEN: PCI Bypass Enable
                          | _______________ BIT 14: BPSEL[2:0]: PCI Bypass Source Selection
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: (unimplemented)
                          ||||| ___________ BIT 10: ACP[2:0]: PCI Acceptance Criteria Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: SWPCI: Software PCI Control
                          ||||||||| _______ BIT  6: SWPCIM[1:0]: Software PCI Control Mode
                          |||||||||| ______ BIT  5: 
                          ||||||||||| _____ BIT  4: LATMOD: PCI SR Latch Mode
                          |||||||||||| ____ BIT  3: TQPS: Termination Qualifier Polarity Selection
                          ||||||||||||| ___ BIT  2: TQSS[2:0]: Termination Qualifier Source Selection
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0:               
                          ||||||||||||||||  */
#define REG_PGxFPCIH    0b0000000000000000

/* PGxFFPCIL: PWM GENERATOR FEED FORWARD PCI REGISTER LOW

                           ________________ BIT 15: TSYNCDIS: Termination Synchronization Disable
                          | _______________ BIT 14: TERM[2:0]: Termination Event Selection
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: AQPS: Acceptance Qualifier Polarity Selection
                          ||||| ___________ BIT 10: AQSS[2:0]: Acceptance Qualifier Source Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: SWTERM: PCI Software Termination
                          ||||||||| _______ BIT  6: PSYNC: PCI Synchronization Control
                          |||||||||| ______ BIT  5: PPS: PCI Polarity Selection
                          ||||||||||| _____ BIT  4: PSS[4:0]: PCI Source Selection
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxFFPCIL   0b0000000000000000
    
/* PGxFFPCIH: PWM GENERATOR FEED FORWARD PCI REGISTER HIGH

                           ________________ BIT 15: BPEN: PCI Bypass Enable
                          | _______________ BIT 14: BPSEL[2:0]: PCI Bypass Source Selection
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: (unimplemented)
                          ||||| ___________ BIT 10: ACP[2:0]: PCI Acceptance Criteria Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: SWPCI: Software PCI Control
                          ||||||||| _______ BIT  6: SWPCIM[1:0]: Software PCI Control Mode
                          |||||||||| ______ BIT  5: 
                          ||||||||||| _____ BIT  4: LATMOD: PCI SR Latch Mode
                          |||||||||||| ____ BIT  3: TQPS: Termination Qualifier Polarity Selection
                          ||||||||||||| ___ BIT  2: TQSS[2:0]: Termination Qualifier Source Selection
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0:               
                          ||||||||||||||||  */
#define REG_PGxFFPCIH   0b0000000000000000
    
/* PGxSPCIL: PWM GENERATOR SOFTWARE PCI REGISTER LOW

                           ________________ BIT 15: TSYNCDIS: Termination Synchronization Disable
                          | _______________ BIT 14: TERM[2:0]: Termination Event Selection
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: AQPS: Acceptance Qualifier Polarity Selection
                          ||||| ___________ BIT 10: AQSS[2:0]: Acceptance Qualifier Source Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: SWTERM: PCI Software Termination
                          ||||||||| _______ BIT  6: PSYNC: PCI Synchronization Control
                          |||||||||| ______ BIT  5: PPS: PCI Polarity Selection
                          ||||||||||| _____ BIT  4: PSS[4:0]: PCI Source Selection
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxSPCIL    0b0000000000000000
    
/* PGxSPCIH: PWM GENERATOR SOFTWARE PCI REGISTER HIGH

                           ________________ BIT 15: BPEN: PCI Bypass Enable
                          | _______________ BIT 14: BPSEL[2:0]: PCI Bypass Source Selection
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: (unimplemented)
                          ||||| ___________ BIT 10: ACP[2:0]: PCI Acceptance Criteria Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: SWPCI: Software PCI Control
                          ||||||||| _______ BIT  6: SWPCIM[1:0]: Software PCI Control Mode
                          |||||||||| ______ BIT  5: 
                          ||||||||||| _____ BIT  4: LATMOD: PCI SR Latch Mode
                          |||||||||||| ____ BIT  3: TQPS: Termination Qualifier Polarity Selection
                          ||||||||||||| ___ BIT  2: TQSS[2:0]: Termination Qualifier Source Selection
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0:               
                          ||||||||||||||||  */
#define REG_PGxSPCIH    0b0000000000000000

/* PGxLEBH: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER HIGH

                           ________________ BIT 15: (unimplemented)
                          | _______________ BIT 14: (unimplemented)
                          || ______________ BIT 13: (unimplemented)
                          ||| _____________ BIT 12: (unimplemented)
                          |||| ____________ BIT 11: (unimplemented)
                          ||||| ___________ BIT 10: PWMPCI[2:0]: PWM Source for PCI Selection
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: (unimplemented)
                          ||||||||| _______ BIT  6: (unimplemented)
                          |||||||||| ______ BIT  5: (unimplemented)
                          ||||||||||| _____ BIT  4: (unimplemented)
                          |||||||||||| ____ BIT  3: PHR: PWMxH Rising Edge Trigger Enable
                          ||||||||||||| ___ BIT  2: PHF: PWMxH Falling Edge Trigger Enable
                          |||||||||||||| __ BIT  1: PLR: PWMxL Rising Edge Trigger Enable
                          ||||||||||||||| _ BIT  0: PLF: PWMxL Falling Edge Trigger Enable
                          ||||||||||||||||  */
#define REG_PGxLEBH     0b0000000000001000

/* PGxLEBL: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER LOW

                           ________________ BIT 15: LEB[15:0]: Leading-Edge Blanking Period bits
                          | _______________ BIT 14: 
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: 
                          ||||| ___________ BIT 10: 
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: 
                          ||||||||| _______ BIT  6: 
                          |||||||||| ______ BIT  5: 
                          ||||||||||| _____ BIT  4: 
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxLEBL     0b0000000000000000
    
/* PGxDCA: PWM GENERATOR x DUTY CYCLE ADJUSTMENT REGISTER

                           ________________ BIT 15: PGxDCA[15:0]: PWM Generator x Duty Cycle Adjustment Register
                          | _______________ BIT 14: 
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: 
                          ||||| ___________ BIT 10: 
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: 
                          ||||||||| _______ BIT  6: 
                          |||||||||| ______ BIT  5: 
                          ||||||||||| _____ BIT  4: 
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
#define REG_PGxDCA      0b0000000000000000

// PWM generator default configuration
volatile struct P33C_PWM_GENERATOR_s buckPwmGeneratorConfig = 
{
        .PGxCONL.value = REG_PGxCONL,       // PGxCONL: PWM GENERATOR x CONTROL REGISTER LOW
        .PGxCONH.value = REG_PGxCONH,       // PGxCONH: PWM GENERATOR x CONTROL REGISTER HIGH
        .PGxSTAT.value = 0x0000,            // PGxSTAT: Clear status bits 
        .PGxIOCONL.value = REG_PGxIOCONL,   // PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER LOW
        .PGxIOCONH.value = REG_PGxIOCONH,   // PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER HIGH
        .PGxEVTL.value = REG_PGxEVTL,       // PGxEVTL: PWM GENERATOR x EVENT REGISTER LOW
        .PGxEVTH.value = REG_PGxEVTH,       // PGxEVTH: PWM GENERATOR x EVENT REGISTER HIGH
        .PGxCLPCIL.value = REG_PGxCLPCIL,   // PGxLCPCIL: PWM GENERATOR x CURRENT LIMIT PCI REGISTER LOW
        .PGxCLPCIH.value = REG_PGxCLPCIH,   // PGxLCPCIL: PWM GENERATOR x CURRENT LIMIT PCI REGISTER HIGH
        .PGxFPCIL.value = REG_PGxFPCIL,     // PGxFPCIL: PWM GENERATOR x FAULT PCI REGISTER LOW
        .PGxFPCIH.value = REG_PGxFPCIH,     // PGxFPCIL: PWM GENERATOR x FAULT PCI REGISTER HIGH
        .PGxFFPCIL.value = REG_PGxFFPCIL,   // PGxFFPCIL: PWM GENERATOR x FEED FORWARD PCI REGISTER LOW
        .PGxFFPCIH.value = REG_PGxFFPCIH,   // PGxFFPCIL: PWM GENERATOR x FEED FORWARD PCI REGISTER HIGH
        .PGxSPCIL.value = REG_PGxSPCIL,     // PGxSPCIL: PWM GENERATOR x SOFTWARE PCI REGISTER LOW
        .PGxSPCIH.value = REG_PGxSPCIH,     // PGxSPCIL: PWM GENERATOR x SOFTWARE PCI REGISTER HIGH
        .PGxLEBL.value = REG_PGxLEBL,       // PGxLEBL: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER LOW
        .PGxLEBH.value = REG_PGxLEBH,       // PGxLEBL: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER HIGH
        .PGxPHASE.value = 0x0000,           // PGxPHASE: PWM GENERATOR x PHASE REGISTER
        .PGxDC.value = 0x0000,              // PGxDC: PWM GENERATOR x DUTY CYCLE REGISTER
        .PGxDCA.value = 0x0000,             // PGxDCA: PWM GENERATOR x DUTY CYCLE ADJUSTMENT REGISTER
        .PGxPER.value = 0x0000,             // PGxPER: PWM GENERATOR x PERIOD REGISTER
        .PGxTRIGA.value = 0x0000,           // PGxTRIGA: PWM GENERATOR x TRIGGER A REGISTER
        .PGxTRIGB.value = 0x0000,           // PGxTRIGA: PWM GENERATOR x TRIGGER B REGISTER
        .PGxTRIGC.value = 0x0000,           // PGxTRIGA: PWM GENERATOR x TRIGGER C REGISTER
        .PGxDTL.value = 0x0000,             // PGxDTL: PWM GENERATOR x DEAD TIME REGISTER LOW
        .PGxDTH.value = 0x0000,             // PGxDTH: PWM GENERATOR x DEAD TIME REGISTER HIGH
        .PGxCAP.value = 0x0000              // PGxCAP: PWM GENERATOR x CAPTURE REGISTER
};

// POWER CONVERTER PERIPHERAL CONFIGURATION ROUTINES OF PWM DRIVER
    
extern volatile uint16_t buckPWM_ModuleInitialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t buckPWM_ChannelInitialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t buckPWM_Start(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t buckPWM_Stop(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t buckPWM_Suspend(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t buckPWM_Resume(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);

/* ********************************************************************************
 * *******************************************************************************/

// Digital-To-Analog Converter and High Speed Comparator Special Function Register Set 
#define ADC_POWERUP_TIMEOUT  5000
/* SLPxDAT: DACx SLOPE DATA REGISTER => Timing Register: User value will be set in code */

// ADC specific declarations
#define ADC_CORE_MASK           0b0000000010001111
#define ADC_CORE0_MASK_INDEX    0b0000000000000001
#define ADC_CORE1_MASK_INDEX    0b0000000000000010
#define ADC_CORE2_MASK_INDEX    0b0000000000000100
#define ADC_CORE3_MASK_INDEX    0b0000000000001000
#define ADC_SHRCORE_MASK_INDEX  0b0000000010000000


extern volatile uint16_t buckADC_ModuleInitialize(void);
extern volatile uint16_t buckADC_ChannelInitialize(volatile BUCK_ADC_INPUT_SETTINGS_t* adcInstance);
extern volatile uint16_t buckADC_Start(void);


/* ********************************************************************************
 * *******************************************************************************/


/* DACxCONL: DACx CONTROL REGISTER LOW

                           ________________ BIT 15: DACEN: Individual DACx Module Enable
                          | _______________ BIT 14: IRQM[1:0]: Interrupt Mode select
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: (unimplemented)
                          |||| ____________ BIT 11: (unimplemented)
                          ||||| ___________ BIT 10: CBE: Comparator Blank Enable
                          |||||| __________ BIT  9: DACOEN: DACx Output Buffer Enable
                          ||||||| _________ BIT  8: FLTREN: Comparator Digital Filter Enable
                          |||||||| ________ BIT  7: CMPSTAT: Comparator Status
                          ||||||||| _______ BIT  6: CMPPOL: Comparator Output Polarity Control
                          |||||||||| ______ BIT  5: INSEL[2:0]: Comparator Input Source Select
                          ||||||||||| _____ BIT  4: 
                          |||||||||||| ____ BIT  3: 
                          ||||||||||||| ___ BIT  2: HYSPOL: Comparator Hysteresis Polarity Select
                          |||||||||||||| __ BIT  1: HYSSEL[1:0]: Comparator Hysteresis Select
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
//#define REG_DACxCONL    0b0000010100000101  // Peak Current Mode Configuration
#define REG_DACxCONL    0b0000000000000000

/* DACxCONH: DACx CONTROL REGISTER HIGH => Timing Register: User value will be set in code */
/* DACxCONL: DACx CONTROL REGISTER LOW  => Timing Register: User value will be set in code */
  
/* SLPxCONL: DACx SLOPE CONTROL REGISTER LOW

                           ________________ BIT 15: HCFSEL[3:0]: Hysteretic Comparator Function Input Selection
                          | _______________ BIT 14: 
                          || ______________ BIT 13: 
                          ||| _____________ BIT 12: 
                          |||| ____________ BIT 11: SLPSTOPA[3:0]: Slope Stop A Signal Selection
                          ||||| ___________ BIT 10: 
                          |||||| __________ BIT  9: 
                          ||||||| _________ BIT  8: 
                          |||||||| ________ BIT  7: SLPSTOPB[3:0]: Slope Stop B Signal Selection
                          ||||||||| _______ BIT  6: 
                          |||||||||| ______ BIT  5: 
                          ||||||||||| _____ BIT  4: 
                          |||||||||||| ____ BIT  3: SLPSTRT[3:0]: Slope Start Signal Selection
                          ||||||||||||| ___ BIT  2: 
                          |||||||||||||| __ BIT  1: 
                          ||||||||||||||| _ BIT  0: 
                          ||||||||||||||||  */
//#define REG_SLPxCONL    0b0000000100010001  // Peak Current Mode Configuration
#define REG_SLPxCONL    0b0000000000000000

/* SLPxCONH: DACx SLOPE CONTROL REGISTER HIGH

                           ________________ BIT 15: SLOPEN: Slope Function Enable/On
                          | _______________ BIT 14: (unimplemented)
                          || ______________ BIT 13: (unimplemented)
                          ||| _____________ BIT 12: (unimplemented)
                          |||| ____________ BIT 11: HME: Hysteretic Mode Enable bit
                          ||||| ___________ BIT 10: TWME: Triangle Wave Mode Enable
                          |||||| __________ BIT  9: PSE: Positive Slope Mode Enable
                          ||||||| _________ BIT  8: (unimplemented)
                          |||||||| ________ BIT  7: (unimplemented)
                          ||||||||| _______ BIT  6: (unimplemented)
                          |||||||||| ______ BIT  5: (unimplemented)
                          ||||||||||| _____ BIT  4: (unimplemented)
                          |||||||||||| ____ BIT  3: (unimplemented)
                          ||||||||||||| ___ BIT  2: (unimplemented)
                          |||||||||||||| __ BIT  1: (unimplemented)
                          ||||||||||||||| _ BIT  0: (unimplemented)
                          ||||||||||||||||  */
//#define REG_SLPxCONH    0b1000000000000000  // Peak Current Mode Configuration
#define REG_SLPxCONH    0b0000000000000000
    




#endif	/* BUCK_CONVERTER_PERIPHERAL_CONFIGURAITON_H */

