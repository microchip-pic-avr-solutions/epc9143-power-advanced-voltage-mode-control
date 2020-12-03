/*
 * File:   dev_buck_special_functions.c
 * Author: M91406
 *
 * Created on December 3, 2020, 10:14 AM
 */

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "xc16_pral.h" // include peripheral register abstraction layer drivers
#include "dev_buck_typedef.h"


/***********************************************************************************
 * @struct CS_CALIBRATION_s
 * @brief  Current sense calibration data structure
 * 
 **********************************************************************************/
typedef struct CS_CALIBRATION_s {
    
    volatile uint16_t cs_calib_cnt;
    volatile uint16_t cs_calib_offset;
    
} CS_CALIBRATION_t;


volatile struct CS_CALIBRATION_s calib_cs[BUCK_MPHASE_COUNT];

/* CURRENT SENSE CALIBRATION */
#define  CS_CALIB_STEPS         8


// Function pointer array defining the state machine execution sequence
/*******************************************************************************
 * @var	volatile uint16_t (*BuckConverterStateMachine[])(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
 * @brief 	
 *
 *********************************************************************************/

volatile uint16_t (*BuckConverterStateMachine[])(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) = {

    State_Error,        ///< State #0: That's the blank "undefined default state", causing the state machine to reset
    State_Initialize,   ///< State #1: Initialize state machine by resetting all runtime flags to default
    State_Reset,        ///< State #2: Reset key runtime flags when power converter was already turned on
    State_Standby,      ///< State #3: After successful initialization, power converter waits to be launched
    State_RampUp,       ///< State #4: Topology-specific startup sub-states are handled in Ramp-Up function
    State_Online        ///< State #5: During normal operation the converter responds to changes in reference

};

/***********************************************************************************
 * @fn volatile uint16_t CurrentSenseOffsetCalibration(void)
 * @brief  Performs an offset calibration of the current sense feedback signal(s)
 * @param  volatile struct BUCK_POWER_CONTROLLER_s *buckInstance
 * @return unsigned integer (0=Repeat
 * @details
 * ADD_DETAILED_DESCRIPTION_HERE
 *
 * @example
 * @code{.c}
 * ADD_CODE_EXAMPLE_HERE
 * @endcode
 *
 * @remarks
 * ADD_REMARKS_HERE
 *
 **********************************************************************************/

volatile enum BUCK_OPSTATE_RETURNS_e CurrentSenseOffsetCalibration(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) 
{
    volatile enum BUCK_OPSTATE_RETURNS_e retval = BUCK_OPSRET_ERROR;

    // if current sense calibration is disabled, return COMPLETE and leave
    if(!buckInstance->status.bits.cs_calib_enable)
    {
        buckInstance->status.bits.cs_calib_complete = true; // Set CS Calibration Flag to COMPLETE
        buckInstance->status.bits.busy = false; // Clear BUSY bit to indicate on-going activity
        retval = BUCK_OPSRET_COMPLETE; // Set return value to COMPLETE
        return(retval); // Leave function returning result
    }

    // Perform Calibration Step
    volatile uint16_t _i = 0;
    
    buckInstance->status.bits.cs_calib_complete = false; // Clear current sense calibration flag during calibration
    buckInstance->status.bits.busy = true; // Set BUSY bit to indicate on-going activity
    
    for (_i=0; _i<buckInstance->set_values.no_of_phases; _i++) 
    {
        
    }
    
    return(retval);
}
