/*
 * File:   init_opa.c
 * Author: M91406
 *
 * Created on May 19, 2020, 1:19 PM
 */


#include <xc.h>
#include "config/epc9143_r40_hwdescr.h"
#include "init_dac.h"

volatile uint16_t dac_mask = 0;

volatile uint16_t init_dac_module(void) {
    
    volatile uint16_t retval=1;

    DACCTRL1Lbits.DACON = 0; // Disable DAC module
    
    DACCTRL1Lbits.DACSIDL = 0; // Continues module operation in Idle mode
    DACCTRL1Lbits.CLKSEL = 0b10; // Clock selection = AFPLLO
    DACCTRL1Lbits.CLKDIV = 0b01; // Clock Divider selection = 1:2
    DACCTRL1Lbits.FCLKDIV = 0b00; // Comparator Filter Clock Divider = 1:1

    DACCTRL2Lbits.TMODTIME = 1; // set Transition Mode Duration
    DACCTRL2Hbits.SSTIME = 1; // set Steady-State delay time

    return (retval);
    
}

volatile uint16_t init_dac_channel(volatile uint16_t dacInstance) {
    
    volatile uint16_t retval=1;
    volatile P33C_DAC_INSTANCE_t* dac;
    
    dac = (volatile P33C_DAC_INSTANCE_t*)(
                (volatile uint8_t*) &DAC1CONL + ((dacInstance - 1) * 
                ((volatile uint16_t)&DAC2CONL - (volatile uint16_t)&DAC1CONL))
        );
    
    dac->DACxCONL.bits.DACEN = 0; // Disable DAC module #1

    dac->DACxCONH.bits.TMCB  = BUCK_LEB_PERIOD;
    
    dac->DACxCONL.bits.IRQM = 0b00; // disable generation of interrupts
    dac->DACxCONL.bits.CBE = 0; // no comparator blanking bit 
    dac->DACxCONL.bits.FLTREN = 0; // Disable digital filter
    dac->DACxCONL.bits.CMPPOL = 0; // Comparator output not inverted
    dac->DACxCONL.bits.INSEL = 0b000; // Enable Comparator input A
    dac->DACxCONL.bits.HYSPOL = 0; // Hysteresis is applied to rising edge of comparator output
    dac->DACxCONL.bits.HYSSEL = 0b00; // no hysteresis selected
    dac->DACxCONL.bits.DACOEN = 1; // Disable DAC output pin
    
    dac->DACxDATH.value = 0x07FF;
    
    dac_mask = (1 << (dacInstance-1));
    
    return (retval);
}

volatile uint16_t init_dac_enable(void) {
    
    volatile uint16_t retval=1;

    DAC1CONLbits.DACEN = (bool)(dac_mask & 0x01);
    DAC2CONLbits.DACEN = (bool)(dac_mask & 0x02);
    DAC3CONLbits.DACEN = (bool)(dac_mask & 0x04);

    DACCTRL1Lbits.DACON = 1; // Disable DAC module
    
    return (retval);
}
