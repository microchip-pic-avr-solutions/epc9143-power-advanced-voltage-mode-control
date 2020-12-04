/*
 * File:   system_initialize.c
 * Author: M91406
 *
 * Created on November 12, 2020, 10:33 AM
 */

#include "hal.h"
#include "system.h"

/**
 * @ingroup system-initialization-mcu
 * @{
 */
/***********************************************************************************
 * @fn volatile uint16_t SYSTEM_Initialize(void) 
 * @brief  Initializes essential chip resources
 * @param  (none)
 * @return unsigned integer 
 * 0=failure
 * 1=success
 * 
 * @details
 * The SYSTEM_Initialize function covers the initialization of essential chip 
 * resources such as main oscillator, auxiliary oscillator, watchdog timer and
 * general purpose I/Os (GPIO). All other, design specific peripherals are 
 * initialized in the User Peripheral Initialization or by the respective 
 * User Task Device Drivers included in the firmware project
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

/** @}*/ // end of group system-initialization-mcu

/**
 * @ingroup system-initialization-user-peripherals
 * @{
 */
/***********************************************************************************
 * @fn uint16_t sysUserPeriperhals_Initialize
 * @brief  Initializes the user-defined chip resources
 * @param  (none)
 * @return unsigned integer (0=failure, 1=success)
 * 
 * @details
 * The EPC9143 16th brick power module reference design uses further on-chip 
 * resources to provide a programmable/tunable reference voltage to external 
 * current sense shunt amplifier devices. This reference voltage is provided
 * by one of the free on-chip Digital-To-Analog converter (DAC) instances. 
 **********************************************************************************/
volatile uint16_t sysUserPeriperhals_Initialize(void) {

    volatile uint16_t retval=1;
    
    retval &= sysOpAmp_Initialize(ISENSE_REF_BUFFER_OPA_INSTANCE, true); // Initialize op-amp #2 used to drive the reference voltage for current sense amplifiers
    
    retval &= sysDacModule_Initialize();  // Initialize DAC module
    retval &= sysDacOutput_Initialize(ISENSE_REF_DAC_INSTANCE); // Initialize DAC #1 used to generate the reference voltage for current sense amplifiers
    retval &= sysDacOutput_Enable(ISENSE_REF_DAC_INSTANCE); // Enable DAC providing reference to current sense amplifiers

    retval &= sysOpAmp_ModuleEnable(); // Enable the operational amplifier module
    
	return(retval);

}

/** @}*/ // end of group system-initialization-user-peripherals

/**
 * @ingroup system-initialization-user-tasks User Task Initialization
 * @{
 */
/***********************************************************************************
 * @fn uint16_t sysUserTasks_Initialize
 * @brief  Initializes the user-defined tasks
 * @param  (none)
 * @return unsigned integer (0=failure, 1=success)
 * 
 * @details
 * The EPC9143 16th brick power module reference design has a very simple GPIO 
 * user interface, signaling the state of the output regulation on a POWER GOOD
 * output pin. Hence, this firmware4 mainly consists of the power control state
 * machine and fault handler, protecting the hardware.
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

/** @}*/ // end of group system-initialization-user-tasks

// end of file
