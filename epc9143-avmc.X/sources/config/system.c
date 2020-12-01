/*
 * File:   system_initialize.c
 * Author: M91406
 *
 * Created on November 12, 2020, 10:33 AM
 */

#include "hal.h"
#include "system.h"

/**
 * @ingroup system-initialization 
 * @{
 */
/***********************************************************************************
 * @fn volatile uint16_t SYSTEM_Initialize(void) 
 * @brief  Initializes essential chip resources and application task
 * @param  (none)
 * @return unsigned integer (0=failure, 1=success)
 * 
 * <b>Description</b><br>
 * The SYSTEM_Initialize function covers the initialization of essential chip 
 * resources such as main oscillator, auxiliary oscillator, watchdog timer and
 * general purpose I/Os (GPIO).
 * 
 * <p><b>Remarks:</b></p>
 * ADD_REMARKS_HERE
 *
 **********************************************************************************/
volatile uint16_t SYSTEM_Initialize(void) 
{
    volatile uint16_t retval=1;
	
    retval &= sysFosc_Initialize(); ///< Set up system oscillator for 100 MIPS operation
    retval &= sysAclk_Initialize(); ///< Set up Auxiliary PLL for 500 MHz (source clock to PWM module)
    retval &= sysGpio_Initialize(); ///< Initialize common device GPIOs
    
	return(retval);

}

/***********************************************************************************
 * @fn uint16_t sysUserPeriperhals_Initialize
 * @brief  Initializes the user-defined tasks and chip resources
 * @param  (none)
 * @return unsigned integer (0=failure, 1=success)
 * 
 * <b>Description</b>
 * ADD_DESCRIPTION_HERE
 *
 * <p><b>Example:</b></p>
 *
 * <code>
 * ADD_CODE_EXAMPLE_HERE
 * </code>
 *
 * <p><b>Remarks:</b></p>
 * ADD_REMARKS_HERE
 *
 **********************************************************************************/
volatile uint16_t sysUserPeriperhals_Initialize(void) {

    volatile uint16_t retval=1;
	
    retval &= sysOpAmp_Initialize(); // Initialize op-amp #2 used to drive the reference voltage for current sense amplifiers
    
    retval &= sysDacModule_Initialize();  // Initialize DAC module
    retval &= sysDacOutput_Initialize(1); // Initialize DAC #1 used to generate the reference voltage for current sense amplifiers
    retval &= sysDacOutput_Enable(1); // Enable DAC providing reference to current sense amplifiers

	return(retval);

}

/***********************************************************************************
 * @fn uint16_t sysUserTasks_Initialize
 * @brief  Initializes the user-defined tasks and chip resources
 * @param  (none)
 * @return unsigned integer (0=failure, 1=success)
 * 
 * <b>Description</b>
 * ADD_DESCRIPTION_HERE
 *
 * <p><b>Example:</b></p>
 *
 * <code>
 * ADD_CODE_EXAMPLE_HERE
 * </code>
 *
 * <p><b>Remarks:</b></p>
 * ADD_REMARKS_HERE
 *
 **********************************************************************************/
volatile uint16_t sysUserTasks_Initialize(void) {

    volatile uint16_t retval=1;
	
    // Initialize task scheduler time base
    retval &= sysOsTimer_Initialize();     // Set up Timer1 as scheduler time base (see MAIN_EXECUTION_PERIOD for details)

    // Initialize software modules
    retval &= appPowerSupply_Initialize(); // Initialize BUCK converter object and state machine
    retval &= appFaultMonitor_Initialize(); // Initialize fault objects and fault handler task

	return(retval);

}

/**@}*/
// end of file
