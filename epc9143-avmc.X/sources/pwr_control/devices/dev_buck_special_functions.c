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
#include "dev_buck_typedef.h" // include buck converter type definitions
#include "dev_buck_special_functions.h" // include buck converter special function defiition

/***********************************************************************************
 * @ingroup lib-layer-buck-specialfn-properties-private-data-types
 * @struct CS_CALIBRATION_s
 * @brief  Current sense calibration data structure
 **********************************************************************************/
typedef struct CS_CALIBRATION_s 
{
    bool start;
    bool stop;
    volatile uint16_t counter;
    volatile uint32_t buffer;
} CS_CALIBRATION_t;

/*********************************************************************************
 * @ingroup lib-layer-buck-specialfn-properties-private-variables
 * @var struct CS_CALIBRATION_s calib_cs[BUCK_MPHASE_COUNT]
 * @brief  Array of current sense calibration data objects of type CS_CALIBRATION_t
 * @details
 *  The current sense feedback offset calibration requires a data space to 
 *  accumulate and average the static feedback offset value. The final result
 *  is written to the feedback channel configuration of the buck converter data
 *  object, hence, the CS_CALIBRATION_s data structure used for the current 
 *  sense feedback offset calibration is kept private and inaccessible from
 *  external firmware modules. This variable is declared as array reserving
 *  a data set for each current sense feedback channel.
 **********************************************************************************/
    
volatile struct CS_CALIBRATION_s calib_cs[BUCK_MPHASE_COUNT];

/*********************************************************************************
 * @ingroup lib-layer-buck-specialfn-properties-private-defines
 * @def CS_CALIB_STEPS
 * @brief  Number of signal oversampling steps used to determine the calibration value
 *  
 **********************************************************************************/
// Current Sense
#define CS_CALIB_STEPS  8


// Private function prototypes of sub-state function calls

volatile uint16_t CurrentSenseOffsetCalibration(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);

/*******************************************************************************
 * @ingroup lib-layer-buck-specialfn-properties-private-variables
 * @var *BuckConverterRampUpSubStateMachine[](volatile struct BUCK_POWER_CONTROLLER_s *buckInstance)
 * @brief Function pointer list of all special function sub-state functions
 * @details
 * The function pointer list BuckConverterSpecialFunctions[] is providing public
 * access to a list of functions serving special purposes supporting specific 
 * power converter configuration options. Each function mapped into this array 
 * as function pointer is a self-contained, independent sub-state, which can be 
 * called from any level of the main state machine being treated like a common 
 * sub-state. 
 * 
 * Each function needs to be called by handing over a parameter of type
 * 
 * - struct BUCK_POWER_CONTROLLER_s 
 * 
 * Each function returns of type unsigned integer:
 * 
 * - 0 = BUCK_OPSRET_ERROR
 * - 1 = BUCK_OPSRET_COMPLETE
 * - 2 = BUCK_OPSRET_REPEAT
 * 
 * <b>Recently available Spacial Functions<b><br>
 * 
 *  - Current Sense Feedback Offset Calibration
 * 
 *********************************************************************************/

volatile uint16_t (*BuckConverterSpecialFunctions[])(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) = 
{
    CurrentSenseOffsetCalibration ///< Function #0: Mutli-Cycle current sense feedbak offset calibration function 
};


/*********************************************************************************
 * @ingroup lib-layer-buck-specialfn-functions-public
 * @fn drv_BuckConverter_SpecialFunctionExecute
 * @brief  This is the public function call access point to call dedicated special sub-functions
 * @param  struct BUCK_POWER_CONTROLLER_s * buckInstance
 * @param  enum BUCK_SPECIAL_FUNCTIONS_e function
 * @return DATA_TYPE SHORT_VALUE_DESCRIPTION
 * @details
 *  ADD_DESCRIPTION_HERE
 *
 * <p><b>Example:</b></p>
 * @code{.c}
 *  ADD_CODE_EXAMPLE_HERE
 * @endcode
 *
 * @note
 *  ADD_REMARKS_HERE
 *
 **********************************************************************************/
	
volatile uint16_t drv_BuckConverter_SpecialFunctionExecute(
        volatile struct BUCK_POWER_CONTROLLER_s * buckInstance, 
        volatile enum BUCK_SPECIAL_FUNCTIONS_e specialFunction
        ) 
{
    volatile uint16_t retval=0;
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* NULL POINTER PROTECTION                                                            */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    // If no buck instance has been declared, leave here
    if(buckInstance == NULL)
        return(0);

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* CALL SPECIAL FUNCTION                                                              */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    retval = BuckConverterSpecialFunctions[specialFunction](buckInstance);
    
	return(retval);

}

/*******************************************************************************
 * PRIVATE FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 * @ingroup lib-layer-buck-specialfn-functions-private
 * @fn	volatile uint16_t CurrentSenseOffsetCalibration(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) 
 * @brief Performs an offset calibration of the current sense feedback signal(s)
 * @param  volatile struct BUCK_POWER_CONTROLLER_s *buckInstance
 * @return unsigned integer (0=failure, 1=success)
 *  
 * @details
 * This function performs a current sense feedback channel zero-offset 
 * calibration. The calibration is executed when the reference voltage is 
 * applied to the current sense shunt amplifiers but the power supply is still
 * turned off. The offset value is determined by a 4x oversampling of each of
 * the feedback signals to eliminate high-frequency noise. 
 * Once the calibration is complete, the 'cs_calib_complete' status bit in 
 * the buck converter power controller object status word is set, allowing 
 * the state machine to run.
 *********************************************************************************/

volatile uint16_t CurrentSenseOffsetCalibration(volatile struct BUCK_POWER_CONTROLLER_s *buckInstance) 
{
    volatile uint16_t _i=0;
    volatile bool _complete=true;
    volatile enum BUCK_OPSTATE_RETURNS_e retval = BUCK_OPSRET_ERROR;

    // if current sense calibration is disabled, return COMPLETE and leave
    if(!buckInstance->status.bits.cs_calib_enable)
    {
        return((uint16_t)BUCK_OPSRET_COMPLETE); // Set return value to COMPLETE and leave function
    }

    // Protect against floored Current Calibration Procedure
    if ((!buckInstance->status.bits.adc_active) ||
        (!buckInstance->status.bits.pwm_active)
       )
    { return((uint16_t)BUCK_OPSRET_REPEAT); } // Return REPEAT
        
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Perform Calibration Step
    
    for(_i = 0; _i<buckInstance->set_values.no_of_phases; _i++)
    {
        // Reset Calibration Data Buffers if Calibration is rerun
        if ((calib_cs[_i].start && calib_cs[_i].stop))
        {
            // Clear calibration data buffer
            calib_cs[_i].buffer = 0; // Clear buffer
            calib_cs[_i].counter = 0; // Clear counter
            calib_cs[_i].start = false; // Clear START flag bit
            calib_cs[_i].stop = false; // Clear STOP flag bit
        }

        // Collect data samples
        if (++calib_cs[_i].counter < CS_CALIB_STEPS)
        {
            calib_cs[_i].start = true; // Clear START flag bit
            calib_cs[_i].stop = false; // Clear STOP flag bit
            calib_cs[_i].buffer += buckInstance->data.i_sns[_i]; // Read ADC offset value
        }
        // Collection of data samples is complete
        else
        {
            calib_cs[_i].buffer >>= 3; // Divide accumulated ADC samples (calculate average)
            calib_cs[_i].stop = true;  // Set STOP flag bit

            // Write calibration data to buck converter data structure
            buckInstance->i_loop[_i].feedback_offset = calib_cs[_i].buffer;

        }
        
        _complete &= calib_cs[_i].stop; // track STOP flag bits
    }

    // Return REPEAT until calibration is complete
    if (_complete)
    { 
        retval = (uint16_t)BUCK_OPSRET_COMPLETE;  // Return COMPLETE
    }
    else
    { retval = (uint16_t)BUCK_OPSRET_REPEAT; } // Return REPEAT
    
    return(retval);
    
}  

// end of file
