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
#ifndef INITIALIZE_DIGITAL_TO_ANALOG_CONVERTER_H
#define	INITIALIZE_DIGITAL_TO_ANALOG_CONVERTER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    
    union {   
        volatile DAC1CONLBITS bits; // Register bit-field
        volatile uint16_t value; // 16-bit wide register value
    }DACxCONL; // DACxCONL: DACx CONTROL LOW REGISTER
    union {   
        volatile DAC1CONHBITS bits; // Register bit-field
        volatile uint16_t value; // 16-bit wide register value
    }DACxCONH; // DACxCONH: DACx CONTROL HIGH REGISTER
    union {   
        volatile DAC1DATLBITS bits; // Register bit-field
        volatile uint16_t value; // 16-bit wide register value
    }DACxDATL; // DACxDATL: DACx DATA LOW REGISTER
    union {   
        volatile DAC1DATHBITS bits; // Register bit-field
        volatile uint16_t value; // 16-bit wide register value
    }DACxDATH; // DACxDATH: DACx DATA HIGH REGISTER
    union {   
        volatile SLP1CONLBITS bits; // Register bit-field
        volatile uint16_t value; // 16-bit wide register value
    }SLPxCONL; // DACx SLOPE CONTROL LOW REGISTER
    union {   
        volatile SLP1CONHBITS bits; // Register bit-field
        volatile uint16_t value; // 16-bit wide register value
    }SLPxCONH; // DACx SLOPE CONTROL LOW REGISTER
    
} __attribute__((packed)) P33C_DAC_INSTANCE_t; // DAC INSTANCE REGISTER SET

    
extern volatile uint16_t init_dac_module(void);
extern volatile uint16_t init_dac_channel(volatile uint16_t dacInstance);
extern volatile uint16_t init_dac_enable(void);

#endif	/* INITIALIZE_DIGITAL_TO_ANALOG_CONVERTER_H */

