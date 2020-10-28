/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BUCK_CONVERTER_PERIPHERAL_CONFIGURAITON_H
#define	BUCK_CONVERTER_PERIPHERAL_CONFIGURAITON_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

// Digital-To-Analog Converter and High Speed Comparator Special Function Register Set 
#define ADC_POWRUP_TIMEOUT  5000
    
// GENERIC GPIO INSTANCE SPECIAL FUNCTION REGISTER SET
// DO NOT REORDER ELEMENTS AS THEY MAP ONTO DEVICE REGISTER MEMORY !!!
#ifndef P33C_GPIO_INSTANCE_s
    typedef struct P33C_GPIO_INSTANCE_s {
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }ANSELx; // ANSELx: ANALOG SELECT FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }TRISx; // TRISx: OUTPUT ENABLE FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }PORTx; // PORTx: INPUT DATA FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }LATx; // LATx: OUTPUT DATA FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }ODCx; // ODCx: OPEN-DRAIN ENABLE FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNPUx; // CNPUx: CHANGE NOTIFICATION PULL-UP ENABLE FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNPDx; // CNPDx: CHANGE NOTIFICATION PULL-DOWN ENABLE FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNCONx; // CNCONx: CHANGE NOTIFICATION CONTROL FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNEN0x; // CNEN0x: CHANGE NOTIFICATION INTERRUPT ENABLE FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNSTATx; // CNSTATx: CHANGE NOTIFICATION STATUS FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNEN1x; // CNEN1x: CHANGE NOTIFICATION EDGE SELECT FOR PORTx REGISTER
        union {   
            volatile struct tagLATABITS bits; // Register bit-field
            volatile uint16_t value; // 16-bit wide register value
        }CNFx; // CNFx: CHANGE NOTIFICATION INTERRUPT FLAG FOR PORTx REGISTER
    } __attribute__((packed)) obj_P33C_GPIO_INSTANCE_t; // GPIO REGISTER SET
    #define P33C_GPIO_SFR_OFFSET  ((volatile uint16_t)&ANSELB - (volatile uint16_t)&ANSELA)
#endif


// GENERIC PDM DAC MODULE SPECIAL FUNCTION REGISTER SET
#ifndef P33C_DAC_MODULE_s
    typedef struct P33C_DAC_MODULE_s{
        volatile uint16_t DACCTRL1L;    // DAC CONTROL 1 REGISTER LOW
        volatile unsigned : 16;         // (reserved)
        volatile uint16_t DACCTRL2L;    // DACCTRL2L: DAC CONTROL 2 REGISTER LOW
        volatile uint16_t DACCTRL2H;    // DACCTRL2H: DAC CONTROL 2 REGISTER HIGH
    } __attribute__((packed)) obj_P33C_DAC_MODULE_t; // PDM DAC MODULE REGISTER SET
#endif

// GENERIC PDM DAC INSTANCE SPECIAL FUNCTION REGISTER SET
#ifndef P33C_DAC_INSTANCE_s    
    typedef struct P33C_DAC_INSTANCE_s{
        volatile uint16_t DACxCONL; // DACxCONL: DACx CONTROL LOW REGISTER
        volatile uint16_t DACxCONH; // DACxCONH: DACx CONTROL HIGH REGISTER
        volatile uint16_t DACxDATL; // DACxDATL: DACx DATA LOW REGISTER
        volatile uint16_t DACxDATH; // DACxDATH: DACx DATA HIGH REGISTER
        volatile uint16_t SLPxCONL; // SLPxCONL: DACx SLOPE CONTROL LOW REGISTER
        volatile uint16_t SLPxCONH; // SLPxCONH: DACx SLOPE CONTROL HIGH REGISTER
        volatile uint16_t SLPxDAT;  // SLPxDAT:  DACx SLOPE DATA REGISTER
    } __attribute__((packed)) obj_P33C_DAC_INSTANCE_t; // PDM DAC INSTANCE REGISTER SET
    #define P33C_DAC_SFR_OFFSET  ((volatile uint16_t)&DAC2CONL - (volatile uint16_t)&DAC1CONL)
#endif
    
#define P33C_PGxCONL_PWM_ON     0x8000  // control bit in PGxCONL enabling/disabling the PWM generator
#define P33C_PGxCONL_HRES_EN    0x0080  // control bit in PGxCONL enabling/disabling High Resolution Mode
#define P33C_PGxIOCONL_OVREN    0x3000  // control bits in PGxIOCONL enabling/disabling the PWM output override
#define P33C_PGxIOCONH_PEN      0x000C  // control bits in PGxIOCONH enabling/disabling the PWM outputs
#define P33C_PGxSTAT_UPDREQ     0x0008  // Control bit in PGxSTAT setting the Update Request bit
#define P33C_PGxCONH_MPERSEL    0x4000  // Control bit in PGxCONH seting the PERIOD register source
    
// ==============================================================================================
// BUCK converter Peripheral Configuration for Voltage Mode Control (VMC)
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
#define REG_PGxCONH     0b0000000101000000


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
                          |||||| __________ BIT  9: IEVTSEL[1:0]: Interrupt Event Selection
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
#define REG_PGxEVTH     0b0000001001000000


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
#define REG_PGxCLPCIL   0b0001101000011011
    
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
#define REG_PGxCLPCIH   0b0000011000000000

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

 
/* @@pwmConfigDispose
 * ********************************************************************************
 * Summary:
 *   Default RESET configuration of one PWM generator channel SFRs
 * 
 * Data type:
 *   struct P33C_PG_SFRSET_s:
 *      PWM module base Special Function Register (SFR) set
 *
 * Description:
 *   Default configuration of the PWM generator SFRs with all its registers 
 *   being reset to their default state when the device comes out of RESET.
 *   Programmers can use this template to reset (dispose) a previously used
 *   PWM generator when it's not used anymore or to secure a known startup
 *   condition before writing individual configurations to its SFRs.
 * 
 * *******************************************************************************/

volatile struct P33C_PWM_GENERATOR_s pgConfigBuckPWM = {
        .PGxCONL.value = REG_PGxCONL, // PGxCONL: PWM GENERATOR x CONTROL REGISTER LOW
        .PGxCONH.value = REG_PGxCONH, // PGxCONH: PWM GENERATOR x CONTROL REGISTER HIGH
        .PGxSTAT.value = 0x0000, // PGxSTAT: PWM GENERATOR x STATUS REGISTER
        .PGxIOCONL.value = REG_PGxIOCONL, // PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER LOW
        .PGxIOCONH.value = REG_PGxIOCONH, // PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER HIGH
        .PGxEVTL.value = REG_PGxEVTL, // PGxEVTL: PWM GENERATOR x EVENT REGISTER LOW
        .PGxEVTH.value = REG_PGxEVTH, // PGxEVTH: PWM GENERATOR x EVENT REGISTER HIGH
        .PGxFPCIL.value = REG_PGxFPCIL, // PGxFPCIL: PWM GENERATOR x FAULT PCI REGISTER LOW
        .PGxFPCIH.value = REG_PGxFPCIH, // PGxFPCIL: PWM GENERATOR x FAULT PCI REGISTER HIGH
        .PGxCLPCIL.value = REG_PGxCLPCIL, // PGxLCPCIL: PWM GENERATOR x CURRENT LIMIT PCI REGISTER LOW
        .PGxCLPCIH.value = REG_PGxCLPCIH, // PGxLCPCIL: PWM GENERATOR x CURRENT LIMIT PCI REGISTER HIGH
        .PGxFFPCIL.value = REG_PGxFFPCIL, // PGxFFPCIL: PWM GENERATOR x FEED FORWARD PCI REGISTER LOW
        .PGxFFPCIH.value = REG_PGxFFPCIH, // PGxFFPCIL: PWM GENERATOR x FEED FORWARD PCI REGISTER HIGH
        .PGxSPCIL.value = REG_PGxSPCIL, // PGxSPCIL: PWM GENERATOR x SOFTWARE PCI REGISTER LOW
        .PGxSPCIH.value = REG_PGxSPCIH, // PGxSPCIL: PWM GENERATOR x SOFTWARE PCI REGISTER HIGH
        .PGxLEBL.value = REG_PGxLEBL, // PGxLEBL: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER LOW
        .PGxLEBH.value = REG_PGxLEBH, // PGxLEBL: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER HIGH
        .PGxPHASE.value = 0x0000, // PGxPHASE=0
        .PGxDC.value = 0x0000, // PGxDC=0
        .PGxDCA.value = 0x0000, // PGxDCA=0
        .PGxPER.value = 0x0000, // PGxPER=0
        .PGxTRIGA.value = 0x0000, // PGxTRIGA=0
        .PGxTRIGB.value = 0x0000, // PGxTRIGB=0
        .PGxTRIGC.value = 0x0000, // PGxTRIGC=0
        .PGxDTL.value = 0x0000, // DTL=0
        .PGxDTH.value = 0x0000, // DTH=0
        .PGxCAP.value = 0x0000 // CAP=0
    };


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
#define REG_DACxCONL    0b0000010100000101

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
#define REG_SLPxCONL    0b0000000100010001

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
#define REG_SLPxCONH    0b1000000000000000

                           
/* SLPxDAT: DACx SLOPE DATA REGISTER => Timing Register: User value will be set in code */

// ADC specific declarations
#define ADC_CORE_MASK           0b0000000010001111
#define ADC_CORE0_MASK_INDEX    0b0000000000000001
#define ADC_CORE1_MASK_INDEX    0b0000000000000010
#define ADC_CORE2_MASK_INDEX    0b0000000000000100
#define ADC_CORE3_MASK_INDEX    0b0000000000001000
#define ADC_SHRCORE_MASK_INDEX  0b0000000010000000

    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* BUCK_CONVERTER_PERIPHERAL_CONFIGURAITON_H */

