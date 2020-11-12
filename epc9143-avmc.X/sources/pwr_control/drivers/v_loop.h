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
 * Date/Time:           11/11/2020 13:58:58
 * ********************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef __SPECIAL_FUNCTION_LAYER_V_LOOP_H__
#define __SPECIAL_FUNCTION_LAYER_V_LOOP_H__

#include <xc.h>                                   // include processor files - each processor file is guarded
#include <dsp.h>                                  // include DSP data types (e.g. fractional)
#include <stdint.h>                               // include standard integer number data types
#include <stdbool.h>                              // include standard boolean data types (true/false)

#include "./pwr_control/drivers/npnz16b.h"        // include NPNZ library header file

/* *******************************************************************************
 * Data Arrays:
 * The NPNZ16b_t data structure contains pointers to coefficient, control and error
 * history arrays. The pointer target objects (variables and arrays) are defined
 * in controller source file v_loop.c
 *
 * Type definitions for A- and B- coefficient arrays as well as error- and control
 * history arrays are aligned in memory using the 'packed' attribute for optimized
 * addressing during DSP computations. These aligned data structures need to be
 * placed in specific memory locations to allow direct X/Y-access from the DSP.
 * This X/Y-memory placement is covered by the declarations used in controller
 * source file v_loop.c
 * ******************************************************************************/

typedef struct V_LOOP_CONTROL_LOOP_COEFFICIENTS_s
{
    volatile int32_t ACoefficients[4];            // A-Coefficients
    volatile int32_t BCoefficients[5];            // B-Coefficients
} __attribute__((packed)) V_LOOP_CONTROL_LOOP_COEFFICIENTS_t; // Data structure packing A- and B- coefficient arrays in a linear memory space for optimized DSP code execution

typedef struct V_LOOP_CONTROL_LOOP_HISTORIES_s
{
    volatile fractional ControlHistory[4];        // Control History Array
    volatile fractional ErrorHistory[5];          // Error History Array
} __attribute__((packed)) V_LOOP_CONTROL_LOOP_HISTORIES_t; // Data structure packing control and error histories arrays in a linear memory space for optimized DSP code execution

// P-Term Coefficient for Plant Measurements
extern volatile int16_t v_loop_pterm_factor;      // Q15 fractional of the Pterm factor
extern volatile int16_t v_loop_pterm_scaler;      // Bit-shift scaler of the Pterm factor

//Adaptive Gain Control Coefficient
extern volatile int16_t v_loop_agc_factor_default; // Q15 fractional of the AGC factor
extern volatile int16_t v_loop_agc_scaler_default; // Bit-shift scaler of the Pterm factor


// User-defined NPNZ16b_s controller data object
extern volatile struct NPNZ16b_s v_loop;          // user-controller data object


/* *******************************************************************************
 * Function call prototypes for initialization routines and control loops
 * ******************************************************************************/

// Initialization of v_loop controller object
extern volatile uint16_t v_loop_Initialize(       // v_loop initialization function call
        volatile struct NPNZ16b_s* controller     // Pointer to NPNZ16b data type object
    );

// Clears the 4P4Z controller output and error histories
extern void v_loop_Reset(                         // v_loop reset function call (Assembly)
        volatile struct NPNZ16b_s* controller     // Pointer to NPNZ16b data type object
    );

// Loads user-defined values into 4P4Z controller output and error histories
extern void v_loop_Precharge(                     // v_loop history pre-charge function call (Assembly)
        volatile struct NPNZ16b_s* controller,    // Pointer to NPNZ16b data type object
        volatile fractional ctrl_input,           // user-defined, constant error history value
        volatile fractional ctrl_output           // user-defined, constant control output history value
    );

// Calls the v_loop control loop
extern void v_loop_Update(                        // Calls the 4P4Z controller (Assembly)
        volatile struct NPNZ16b_s* controller     // Pointer to NPNZ16b data type object
    );

// Calls the v_loop P-Term controller during measurements of plant transfer functions
// THIS CONTROLLER IS USED FOR MEASUREMENTS OF THE PLANT TRANSFER FUNCTION ONLY.
// THIS LOOP IS BY DEFAULT UNSTABLE AND ONLY WORKS UNDER STABLE TEST CONDITIONS
// DO NOT USE THIS CONTROLLER TYPE FOR NORMAL OPERATION
extern void v_loop_PTermUpdate(                   // Calls the P-Term controller (Assembly)
        volatile struct NPNZ16b_s* controller     // Pointer to NPNZ16b data type object
    );

#endif                                            // end of __SPECIAL_FUNCTION_LAYER_V_LOOP_H__


//**********************************************************************************
// Download latest version of this tool here: https://areiter128.github.io/DCLD
//**********************************************************************************

