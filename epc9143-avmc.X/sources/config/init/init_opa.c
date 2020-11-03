/*
 * File:   init_opa.c
 * Author: M91406
 *
 * Created on May 19, 2020, 1:19 PM
 */


#include <xc.h>
#include <p33CK32MP102.h>

volatile uint16_t init_opa(void) {
    
    volatile uint16_t retval=1;

    AMPCON1Lbits.AMPON = 0; // Disable Op-Amp module
    
    AMPCON1Lbits.AMPEN1 = 0; // Disable OPA1
    AMPCON1Lbits.AMPEN2 = 1; // Enable OPA2
    
    AMPCON1Hbits.NCHDIS1 = 1; // Disables Op Amp #1 N channel input stage
    AMPCON1Hbits.NCHDIS2 = 1; // Enable Op Amp #2 N channel input stage
    AMPCON1Hbits.NCHDIS3 = 1; // Disables Op Amp #3 N channel input stage
    
    AMPCON1Lbits.AMPON = 1; // Enable Op-Amp module

    return (retval);
}
