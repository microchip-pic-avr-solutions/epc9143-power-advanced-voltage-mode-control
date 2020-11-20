/*
 * File:   init_opa.c
 * Author: M91406
 *
 * Created on May 19, 2020, 1:19 PM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer types header file
#include <stdbool.h> // include standard boolean types header file

#include "config/hal.h"
#include "init_dac.h"
#include "pwr_control/devices/dev_buck_typedef.h"

volatile uint16_t dac_mask = 0;
volatile bool _dacout_used=false;

/* Default configuration of DAC module running from 500 MHz input clock */
volatile struct P33C_DAC_MODULE_s dacModuleDefault = {
    .DacModuleCtrl1L.value = 0x0080, ///< DAC Module disabled, DAC Stop In Idle Mode=0, DAC Clock Source=AFPLLO, DAC Clock Divider=1:1, Filter Clock Divider=1:1
    .DacModuleCtrl2H.bits.SSTIME = 0x008A, ///< Steady-state setting time is set to default of 0x8A
    .DacModuleCtrl2L.bits.TMODTIME = 0x0055 ///< Transition mode duration is set to default of 0x55
};


volatile uint16_t init_dac_module(void) {
    
    volatile uint16_t retval=1;
    volatile struct P33C_DAC_MODULE_s* dac;

    dac = p33c_DacModule_GetHandle();
    retval &= p33c_DacModule_Dispose();
    retval &= p33c_DacModule_ConfigWrite(dacModuleDefault);

    return (retval);
    
}

volatile uint16_t init_dac_channel(volatile uint16_t dacInstance) {
    
    volatile uint16_t retval=1;
    volatile struct P33C_DAC_INSTANCE_s* dac;
    
    dac = p33c_DacInstance_GetHandle(dacInstance);
    retval &= p33c_DacInstance_Dispose(dacInstance);
    
    if(!_dacout_used)
        dac->DACxCONL.bits.DACOEN = 1; // Enable DAC output pin

    dac->DACxCONH.bits.TMCB  = BUCK_LEB_PERIOD;
    dac->DACxDATH.value = 0x07FF; // Set board current reference to VDD/2 (~1.650 V)

    dac_mask = (1 << (dacInstance-1));
    _dacout_used |= (bool)(dac->DACxCONL.bits.DACOEN);
    
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
