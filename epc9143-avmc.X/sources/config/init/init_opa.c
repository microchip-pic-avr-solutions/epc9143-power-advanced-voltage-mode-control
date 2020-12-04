/*
 * File:   init_opa.c
 * Author: M91406
 *
 * Created on May 19, 2020, 1:19 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "init_opa.h"

/**
 * @ingroup op-amp-initialization
 * @{
 */
/***********************************************************************************
 * @fn uint16_t sysOpAmp_Initialize
 * @brief  Initializes the on-chip operational amplifier module
 * @param  (none)
 * @return unsigned integer
 * @return 0=failure
 * @return 1=success
 * 
 * @details
 * The EPC9143 300W 16th brick power module reference designs uses one of the on-chip 
 * operational amplifiers as buffer op-amp for the current reference signal applied
 * to external high-side current sense shunt amplifier devices. This operational
 * amplifier is initialized here.
 * 
 **********************************************************************************/

volatile uint16_t sysOpAmp_Initialize(volatile uint16_t opaInstance, volatile bool disable_n_channel) 
{
    volatile uint16_t retval=1;
    volatile uint16_t idum=0;
    volatile struct P33C_OPA_MODULE_s* opa = p33c_OpaModule_GetHandle();

    // Disable and reset op-amp module
    *opa = opaModuleDefault;
    opa->AmpCon1L.value = 0; // Disable and reset Op-Amp module

    // Enable op-amp instance
    idum = (0x0001 << (opaInstance - 1));
    opa->AmpCon1L.value |= idum;
    
     // Disables Op Amp #1 N channel input stage
    idum = (((uint16_t)disable_n_channel) << (opaInstance - 1));
    opa->AmpCon1H.value |= idum;
        
    return (retval);
}

/***********************************************************************************
 * @fn uint16_t sysOpAmp_ModuleEnable
 * @brief  Enables the on-chip operational amplifier module
 * @param  (none)
 * @return unsigned integer
 * @return 0=failure
 * @return 1=success
 * 
 * @details
 * The on-chip operational amplifier module allows the configuration of multiple 
 * operational amplifier instances. The module itself provides an additional 
 * master enable bit to turn on/off the entire module.
 * 
 **********************************************************************************/

volatile uint16_t sysOpAmp_ModuleEnable(void)
{
    volatile struct P33C_OPA_MODULE_s* opa = p33c_OpaModule_GetHandle();
    opa->AmpCon1L.bits.AMPON = true; // Enable Op-Amp module
    return (opa->AmpCon1L.bits.AMPON);
}

/** @}*/ // end of group op-amp-initialization

// end of file
