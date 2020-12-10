/* *********************************************************************************
 * z-Domain Control Loop Designer, Version 0.9.12.642
 * *********************************************************************************
 * 4p4z controller function declarations and compensation filter coefficients
 * derived for following operating conditions:
 * *********************************************************************************
 *
 *  Controller Type:    4P4Z - Advanced High-Q Compensator
 *  Sampling Frequency: 500000 Hz
 *  Fixed Point Format: Q15
 *  Scaling Mode:       3 - Dual Bit-Shift Scaling
 *  Input Gain:         0.208791
 *
 * *********************************************************************************
 * CGS Version:         3.0.0
 * CGS Date:            09/07/2020
 * *********************************************************************************
 * User:                M91406
 * Date/Time:           12/06/2020 15:02:37
 * ********************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef __SPECIAL_FUNCTION_LAYER_V_LOOP_AGC_H__
#define __SPECIAL_FUNCTION_LAYER_V_LOOP_AGC_H__

#include <xc.h>                                   // include processor files - each processor file is guarded
#include <dsp.h>                                  // include DSP data types (e.g. fractional)
#include <stdint.h>                               // include standard integer number data types
#include <stdbool.h>                              // include standard boolean data types (true/false)

#include "./pwr_control/drivers/npnz16b.h"        // include NPNZ library header file


// ADVANCED CONTROL FUNCTION DECLARATIONS

extern void v_loop_AGCFactorUpdate(volatile NPNZ16b_t* controller); ///< Pointer to nPnZ data type object
                                                // Calls the AGC Factor Modulation Function (Assembly)


#endif	/* __SPECIAL_FUNCTION_LAYER_V_LOOP_AGC_H__ */

