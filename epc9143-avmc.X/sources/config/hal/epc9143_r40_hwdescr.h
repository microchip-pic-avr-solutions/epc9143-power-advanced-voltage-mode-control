/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * @file   epc9143_R40_hwdescr.h
 * Author: M91406
 * @brief EPC9143 16th Brick Reference Design Hardware Descriptor header file
 * Revision history: 
 */



// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef EPC9143_R40_HARDWARE_DESCRIPTOR_H
#define	EPC9143_R40_HARDWARE_DESCRIPTOR_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types
#include <math.h> // include standard math functoins library

/**************************************************************************************************
 * @ingroup hardware-id-macro
 * @{
 * @brief Global macro identifying the hardware version supported by 
 * 
 * @details
 * This global macro is used to identify the hardware version supported by this hardware 
 * abstraction layer header file. 
 * 
 **************************************************************************************************/

#ifndef __EPC9143_R40__
  #define __EPC9143_R40__
#endif

/** @} */ // end of group hardware-id-macro

/**************************************************************************************************
 * @ingroup special-options
 * @{
 * @brief Global defines used to enable/disable special firmware options
 * 
 * @details
 * This section is used to enable/disable special options of the firmware. 
 * 
 **************************************************************************************************/

/* CUSTOM RUNTIME OPTIONS */
#define PLANT_MEASUREMENT   false ///< If enabled, replaces the common voltage control loop by a simple P-control loop to perform measurements of the plant transfer function.

#define DBGPIN1_ENABLE      false ///< Enables debug pin indicating control loop execution timing
#define DBGPIN2_ENABLE      true ///< Enables debug pin indicating task scheduler execution timing

/** @} */ // end of group special-options

/*********************************************************************************
 * @ingroup special-options
 * @def BUCK_ISNS_OFFSET_CALIBRATION_ENABLE
 * @brief  Enables/Disables Current Sense Offset Calibration
 * @details
 * Flag indicating if the signal offset of the current sense feedback needs to be calibrated.
 * The calibration procedure is available as Special Function of the power controller and will be 
 * called automatically when the option BUCK_ISNS_NEED_CALIBRATION is set to 'true' 
 * @note
 * Standby current sense feedback offset calibration is not supported by the MCP6C02 shunt amplifier
 * device used in EPC9143 due to its limited common mode range, which starts above 2.5 V DC. However,
 * the common reference voltage of both devices, auto-zero self tuning and high sensing precision
 * makes calibration negligible.
 **********************************************************************************/

#define BUCK_ISNS_OFFSET_CALIBRATION_ENABLE  false ///< Current Sense Offset Calibration is disabled (see notes)

/**************************************************************************************************
 * @ingroup device-abstraction-settings
 * @{ 
 * @brief Fundamental microcontroller device settings
 * 
 * @details
 * This section is used to define device specific parameters like ADC reference and
 * resolution, main execution clock frequency and peripheral time base settings. 
 * All parameters are defined using physical quantities. 
 * 
 **************************************************************************************************/
#define CPU_FREQUENCY       (float)100000000.0  ///< CPU frequency in [Hz]

// ADC(DAC Reference and Resolution Settings    
#define ADC_REFERENCE       (float)3.300 ///< ADC reference voltage in V
#define ADC_RESOLUTION      (float)12.0  ///< ADC resolution in [bit]

// PWM/ADC Clock Settings    
#define PWM_CLOCK_FREQUENCY (float)4.0e+9   ///< PWM Clock Frequency in [Hz]


/** @} */ // end of group device-abstraction-settings

/**
 * @ingroup device-abstraction-macros
 * @{ 
 * @brief Conversion macros of fundamental microcontroller device settings
 * 
 * @details
 * This section is used to convert device specific parameters like ADC reference and
 * resolution, main execution clock frequency and peripheral time base settings, declared 
 * in physical quantities, into binary (integer) numbers to be written to variables and SFRs.
 */

#define CPU_TCY             (float)(1.0/CPU_FREQUENCY) ///< Instruction period
#define ADC_GRANULARITY     (float)(ADC_REFERENCE / pow(2.0, ADC_RESOLUTION)) ///< ADC granularity in [V/tick]
#define ADC_VALUE_MAX       (uint16_t) (pow(2.0, ADC_RESOLUTION) - 1.0) // DO NOT CHANGE
#define PWM_CLOCK_PERIOD    (float)(1.0/PWM_CLOCK_FREQUENCY) ///< PWM Clock Period in [sec]

/** @} */ // end of group device-abstraction-macros

/**************************************************************************************************
 * @ingroup state-machine-settings
 * @{
 * @brief Global state-machine user-settings
 * 
 * @details
 * This section is used to set, modify, enable or disable common state machine parameters
 * and features. 
 * 
 * (Please see individual settings description for detail) 
 * 
 **************************************************************************************************/

#define MAIN_EXECUTION_PERIOD   (float)100.0e-6 ///< main state machine function call period in [sec]

/** @} */ // end of group state-machine-settings ~~~~~~~~~~

/**
 * @ingroup state-machine-macros
 * @{
 * @brief Global state-machine user-settings conversion macros
 * 
 * @details
 * Conversion macros are used to convert user settings defined in physical quantities into 
 * binary (integer) numbers, which will be written to registers and variables and/or used in 
 * calculations throughout the firmware.
 */

#define MAIN_EXEC_PER           (uint16_t)((CPU_FREQUENCY * MAIN_EXECUTION_PERIOD)-1) // DO NOT CHANGE

/** @} */ // end of group state-machine-macros ~~~~~~~~~~

/**
 * @ingroup state-machine-mcal
 * @{
 * @brief Global state-machine peripheral assignments
 * 
 * @details
 * The main task scheduler time base required a timer interrupt to separate high-priority
 * from low-priority tasks. The high priority task timer interrupt is configured here.
 */

#define _OsTimerInterrupt      _T1Interrupt ///< Interrupt serivce routine label 
#define _OSTIMER_IP            _T1IP ///< interrupt priority register
#define _OSTIMER_IE            _T1IE ///< interrupt enable bit
#define _OSTIMER_IF            _T1IF ///< interrupt flag bit
#define _OSTIMER_PRIORITY       2    ///< interrupt priority (1 ... 7, default = 2)

/** @} */ // end of group state-machine-mcal ~~~~~~~~~~

/***************************************************************************************************
 * @ingroup circuit-gpio-mcal
 * @{
 * @brief Global abstraction labels of special circuit signal device pin assignments
 * 
 * <b>Description:</b>
 * This section is used to define labels of hardware specific signals, which are directly 
 * assigned to specific device pins. These labels will be used throughout the code and remain
 * unchanged even if this firmware is migrated to another device or pin-out changes between
 * hardware revisions.
 * 
 **************************************************************************************************/

#if (DBGPIN1_ENABLE == true)
#define DBGPIN1_PORT        1   ///< GPIO port declaration where 0=Port RA, 0=Port RB, 0=Port RC, etc.
#define DBGPIN1_PIN         14  ///< GPIO port pin declaration where 0=Rx0, 1=Rx1, 2=Rx3, etc.
#define DBGPIN1_Set()	    { _LATB14 = 1; } ///< Macro instruction to set a pin state to logic HIGH
#define DBGPIN1_Clear()	    { _LATB14 = 0; } ///< Macro instruction to set a pin state to logic LOW
#define DBGPIN1_Toggle()    { _LATB14 ^= 1; } ///< Macro instruction to toggle most recent pin state
#define DBGPIN1_Init()	    { _LATB14 = 0; _TRISB14 = 0; } ///< Macro instruction initializing the specified GPIO as input or output
#endif

// Device Pin #2 on EPC9143 (not routed)
#if (DBGPIN2_ENABLE == true)
#define DBGPIN2_PORT        1   ///< GPIO port declaration where 0=Port RA, 0=Port RB, 0=Port RC, etc.
#define DBGPIN2_PIN         15  ///< GPIO port pin declaration where 0=Rx0, 1=Rx1, 2=Rx3, etc.
#define DBGPIN2_Set()       { _LATB15 = 1; } ///< Macro instruction to set a pin state to logic HIGH
#define DBGPIN2_Clear()     { _LATB15 = 0; } ///< Macro instruction to set a pin state to logic LOW
#define DBGPIN2_Toggle()    { _LATB15 ^= 1; } ///< Macro instruction to toggle most recent pin state
#define DBGPIN2_Init()      { _LATB15 = 0; _TRISB15 = 0; } ///< Macro instruction initializing the specified GPIO as input or output
#endif

// Device Pin #14 on EPC9243
#define PWRGOOD_PORT        1   ///< GPIO port declaration where 0=Port RA, 0=Port RB, 0=Port RC, etc.
#define PWRGOOD_PIN         1   ///< GPIO port pin declaration where 0=Rx0, 1=Rx1, 2=Rx3, etc.
#define PWRGOOD_Set()       { _LATB1 = 1; } ///< Macro instruction to set a pin state to logic HIGH
#define PWRGOOD_Clear()	    { _LATB1 = 0; } ///< Macro instruction to set a pin state to logic LOW
#define PWRGOOD_Toggle()    { _LATB1 ^= 1; } ///< Macro instruction to toggle most recent pin state
#define PWRGOOD_Init()      { _ANSELB1 = 0; _LATB1 = 0; _TRISB1 = 0; } ///< Macro instruction initializing the specified GPIO as input or output
    
/** @} */ // end of group circuit-gpio-mcal

/**************************************************************************************************
 * @ingroup circuit-peripheral-mcal
 * @{
 * @brief User-declaration of global defines for PWM signal generator settings
 * 
 * @details
 * This section defines fundamental PWM settings required for the interleaved buck converter
 * of the EPC9143 300W 16th brick power module reference design. These settings are determined 
 * by hardware and defined using physical quantities. Pre-compiler macros are used to convert 
 * physical values into binary (integer) numbers to be written to Special Function Registers (SFR).
 * 
 **************************************************************************************************/

#define ISENSE_REF_DAC_INSTANCE         1U ///< Digital-To-Analog Converter instance used to generate current semse amplifier reference voltage
#define ISENSE_REF_BUFFER_OPA_INSTANCE  2U ///< Operational amplifier instance used to generate current semse amplifier reference voltage

/** @} */ // end of group circuit-peripheral-mcal

/**************************************************************************************************
 * @ingroup pwm-settings
 * @{
 * @brief User-declaration of global defines for PWM signal generator settings
 * 
 * @details
 * This section defines fundamental PWM settings required for the interleaved buck converter
 * of the EPC9143 300W 16th brick power module reference design. These settings are determined 
 * by hardware and defined using physical quantities. Pre-compiler macros are used to convert 
 * physical values into binary (integer) numbers to be written to Special Function Registers (SFR).
 * 
 **************************************************************************************************/

#define BUCK_NO_OF_PHASES              2U     ///< Number of power converter phases of this design
    
#define BUCK_SWITCHING_FREQUENCY       (float)500.0e+3 ///< Fixed Switching frequency in [Hz]
#define BUCK_PWM_DUTY_CYCLE_MIN        (float)0.010 ///< Minimum on/off-time ratio (duty ratio) in [%]
#define BUCK_PWM_DUTY_CYCLE_MAX        (float)0.850 ///< Maximum on/off-time ratio (duty ratio) in [%]
#define BUCK_LEADING_EDGE_BLANKING     (float)100.0e-9 ///< Leading Edge Blanking period in [sec]
#define BUCK_DEAD_TIME_LEADING_EDGE    (float)10.0e-9 ///< Leading Edge Dead Time delay in [sec]
#define BUCK_DEAD_TIME_FALLING_EDGE    (float)10.0e-9 ///< Falling Edge Dead Time delay in [sec]

/** @} */ // end of group pwm-settings ~~~~~~~~~~~~~~~~~~~~

/** 
 * @ingroup pwm-mcal-phase1
 * @{ 
 * @brief PWM peripheral output pins, control signals and register assignments of converter phase #1
 * 
 * @details
 * Converter phase #1 uses a simple half-bridge to commutate the switch node. The signal source
 * therefore only requires a single PWM generator instance to be configured in fixed frequency 
 * complementary mode with dead times. Additional PWM peripheral features are used by the firmware
 * to respond to interrupts, trigger ADC conversions, control device output pins during startup 
 * and fault responses and to change timing settings on the fly. 
 * 
 * Please review the device data sheet for details about register names and settings.
 */
#define BUCK_PWM1_CHANNEL              2U ///< PWM Instance Index (e.g. 1=PWM1, 2=PWM2, etc.)
#define BUCK_PWM1_GPIO_INSTANCE        1U ///< Number indicating device port, where 0=Port RA, 0=Port RB, 0=Port RC, etc.
#define BUCK_PWM1_GPIO_PORT_PINH       12U ///< Port Pin Number
#define BUCK_PWM1_GPIO_PORT_PINL       13U ///< Port Pin Number
    
#define BUCK_PWM1_PDC                   PG2DC    ///< PWM Instance Duty Cycle Register
#define BUCK_PWM1H_TRIS                 _TRISB12 ///< Device Port TRIS register
#define BUCK_PWM1H_WR                   _LATB12  ///< Device Pin WRITE
#define BUCK_PWM1H_RD                   _RB12    ///< Device Pin READ
#define BUCK_PWM1H_RPx                  (uint8_t)44 ///< Device Pin output remappable pin number (RPx)
#define BUCK_PWM1L_TRIS                 _TRISB13 ///< Device Port TRIS register
#define BUCK_PWM1L_WR                   _LATB13  ///< Device Pin WRITE
#define BUCK_PWM1L_RD                   _RB13    ///< Device Pin READ
#define BUCK_PWM1L_RPx                  (uint8_t)45 ///< Device Pin output remappable pin number (RPx)

#define _BUCK_PWM1_Interrupt            _PWM2Interrupt ///< PWM Interrupt Service Routine label
#define BUCK_PWM1_IF                    _PWM2IF  ///< PWM Interrupt Flag Bit
#define BUCK_PWM1_IE                    _PWM2IE  ///< PWM Interrupt Enable Bit
#define BUCK_PWM1_IP                    _PWM2IP  ///< PWM Interrupt Priority
#define BUCK_PWM1_TRGSRC_TRG1           0b00110  ///< PWM Trigger #1 Trigger Source of this channel
#define BUCK_PWM1_TRGSRC_TRG2           0b00111  ///< PWM Trigger #2 Trigger Source of this channel
#define BUCK_PWM1_PGxTRIGA              PG2TRIGA ///< PWM trigger register A
#define BUCK_PWM1_PGxTRIGB              PG2TRIGB ///< PWM trigger register B
#define BUCK_PWM1_PGxTRIGC              PG2TRIGC ///< PWM trigger register C
    
#define BUCK_PWM1_ADTR1OFS              0U ///< ADC Trigger 1 Offset:  0...31
#define BUCK_PWM1_ADTR1PS               0U ///< ADC Trigger 1 Postscaler: 0...31

#define BUCK_PWM1_UPDREQ                PG1STATbits.UPDREQ

/** @} */ // end of group pwm-mcal-phase1 ~~~~~~~~~~~~~~~~~

/** 
 * @ingroup pwm-mcal-phase2
 * @{ 
 * @brief PWM peripheral output pins, control signals and register assignments of converter phase #2
 * 
 * @details
 * Converter phase #2 uses a simple half-bridge to commutate the switch node. The signal source
 * therefore only requires a single PWM generator instance to be configured in fixed frequency 
 * complementary mode with dead times. Additional PWM peripheral features are used by the firmware
 * to respond to interrupts, trigger ADC conversions, control device output pins during startup 
 * and fault responses and to change timing settings on the fly. 
 * 
 * Please review the device data sheet for details about register names and settings.
 */

// PWM Phase #2 Configuration
#define BUCK_PWM2_CHANNEL               4U ///< PWM Instance Index (e.g. 1=PWM1, 2=PWM2, etc.)
#define BUCK_PWM2_GPIO_INSTANCE         1U ///< Number indicating device port, where 0=Port RA, 0=Port RB, 0=Port RC, etc.
#define BUCK_PWM2_GPIO_PORT_PINH        9U ///< Port Pin Number
#define BUCK_PWM2_GPIO_PORT_PINL        8U ///< Port Pin Number

#define BUCK_PWM2_PDC                   PG4DC    ///< PWM Instance Duty Cycle Register

#define BUCK_PWM2H_TRIS                 _TRISB9  ///< Device Port TRIS register
#define BUCK_PWM2H_WR                   _LATB9   ///< Device Pin WRITE
#define BUCK_PWM2H_RD                   _RB9     ///< Device Pin READ
#define BUCK_PWM2H_RPx                  (uint8_t)41 ///< Device Pin output remappable pin number (RPx)
#define BUCK_PWM2H_INIT                 { _LATB9 = 0; _TRISB9 = 0; }

#define BUCK_PWM2L_TRIS                 _TRISB8  ///< Device Port TRIS register
#define BUCK_PWM2L_WR                   _LATB8   ///< Device Pin WRITE
#define BUCK_PWM2L_RD                   _RB8     ///< Device Pin READ
#define BUCK_PWM2L_RPx                  (uint8_t)40 ///< Device Pin output remappable pin number (RPx)
#define BUCK_PWM2L_INIT                 { _LATB8 = 0; _TRISB8 = 0; }

#define _BUCK_PWM2_Interrupt            _PWM4Interrupt ///< PWM Interrupt Serivice Routine label
#define BUCK_PWM2_IF                    _PWM4IF  ///< PWM Interrupt Flag Bit
#define BUCK_PWM2_IE                    _PWM4IE  ///< PWM Interrupt Enable Bit
#define BUCK_PWM2_IP                    _PWM4IP  ///< PWM Interrupt Priority
#define BUCK_PWM2_TRGSRC_TRG1           0b01010  ///< PWM2 Trigger #1 Trigger Source of this channel
#define BUCK_PWM2_TRGSRC_TRG2           0b01011  ///< PWM2 Trigger #2 Trigger Source of this channel
#define BUCK_PWM2_PGxTRIGA              PG4TRIGA ///< PWM2 trigger register A
#define BUCK_PWM2_PGxTRIGB              PG4TRIGB ///< PWM2 trigger register B
#define BUCK_PWM2_PGxTRIGC              PG4TRIGC ///< PWM2 trigger register C

#define BUCK_PWM2_ADTR1OFS              0 ///< ADC Trigger 1 Offset:  0...31
#define BUCK_PWM2_ADTR1PS               0 ///< ADC Trigger 1 Postscaler: 0...31
    
#define BUCK_PWM2_UPDREQ                PG1STATbits.UPDREQ

/** @} */ // end of group pwm-mcal-phase2 ~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/** 
 * @ingroup pwm-macros
 * @{ 
 * @brief Conversion macros for user-declarations of PWM parameters
 * 
 * These conversion macros are used to convert user settings defined as physical 
 * quantities into binary (integer) numbers, which will be written to registers and
 * variables and used in calculations throughout the firmware.
 */

// Conversion Macros
#define BUCK_SWITCHING_PERIOD   (float)(1.0/BUCK_SWITCHING_FREQUENCY)   ///< Switching period in [sec]
#define BUCK_PWM_PERIOD         (uint16_t)(float)(BUCK_SWITCHING_PERIOD / PWM_CLOCK_PERIOD) ///< This sets the switching period of the converter
#define BUCK_PWM_PHASE_SHIFT    (uint16_t)((float)BUCK_PWM_PERIOD / (float)BUCK_NO_OF_PHASES) ///< This sets the phase shift between phase #1 and #2
#define BUCK_PWM_DC_MIN         (uint16_t)(BUCK_PWM_DUTY_CYCLE_MIN * (float)BUCK_PWM_PERIOD) ///< This sets the minimum duty cycle
#define BUCK_PWM_DC_MAX         (uint16_t)(BUCK_PWM_DUTY_CYCLE_MAX * (float)BUCK_PWM_PERIOD) ///< This sets the maximum duty cycle
#define BUCK_LEB_PERIOD         (uint16_t)(BUCK_LEADING_EDGE_BLANKING / (float)PWM_CLOCK_PERIOD) ///< Leading Edge Blanking = n x PWM resolution (here: 50 x 2ns = 100ns)
#define BUCK_PWM_DEAD_TIME_LE   (uint16_t)(BUCK_DEAD_TIME_LEADING_EDGE / (float)PWM_CLOCK_PERIOD) ///< Rising edge dead time [tick = 250ps]
#define BUCK_PWM_DEAD_TIME_FE   (uint16_t)(BUCK_DEAD_TIME_FALLING_EDGE / (float)PWM_CLOCK_PERIOD) ///< Falling edge dead time [tick = 250ps]

/** @} */ // end of group pwm-macros ~~~~~~~~~~~~~~~~~~~~~~

    
/**************************************************************************************************
 * @ingroup input-voltage-feedback-settings
 * @{
 * @brief Declaration of input voltage feedback properties
 * 
 * In this section the output voltage feedback signal scaling, gain, valid signal limits and nominal
 * operating point is specified. Physical quantities are used to define values. Macros are used to 
 * convert given physical values into binary (integer) number to be written into SFRs and variables.
 * *************************************************************************************************/

// Feedback Declarations
#define BUCK_VIN_MINIMUM            (float)18.000   ///< Minimum input voltage in [V]
#define BUCK_VIN_NOMINAL            (float)48.000   ///< Nominal input voltage in [V]
#define BUCK_VIN_MAXIMUM            (float)60.500   ///< Maximum input voltage in [V]

#define BUCK_VIN_UNDER_VOLTAGE      (float)17.50    ///< Under Voltage Lock Out Cut Off in [V]
#define BUCK_VIN_OVER_VOLTAGE       (float)61.00    ///< Over Voltage Lock Out Cut Off in [V]
#define BUCK_VIN_HYSTERESIS         (float)1.500    ///< UVLO/OVLO Hysteresis in [V]
    
#define BUCK_VIN_R1                 (float)(110.0)  ///< Upper voltage divider resistor in [kOhm]
#define BUCK_VIN_R2                 (float)(4.870)  ///< Lower voltage divider resistor in [kOhm]
    
#define BUCK_VIN_FEEDBACK_OFFSET    (float)(0.0) ///< Physical, static signal offset in [V]
#define BUCK_VIN_ADC_TRG_DELAY      (float)(120.0e-9) ///< ADC trigger delay in [sec]

/** @} */ // end of group input-voltage-feedback-settings ~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/** 
 * @ingroup input-voltage-feedback-mcal
 * @{ 
 * @brief ADC input assignments of input voltage feedback signals
 * 
 * In this section the ADC input channels, related ADC result buffers, trigger
 * sources and interrupt vectors are defined. These settings allow the fast 
 * re-assignments of feedback signals in case of hardware changes.
 */

// Peripheral Assignments
#define _BUCK_VIN_ADCInterrupt  _ADCAN9Interrupt ///< ADC interrupt service routine function call of the input voltage feedback channel
#define _BUCK_VIN_ADCISR_IF     _ADCAN9IF   ///< ADC interrupt flag bit of the input voltage feedback channel

#define BUCK_VIN_ANSEL          _ANSELA2    ///< GPIO analog function mode enable bit
#define BUCK_VIN_ADCCORE        8           ///< 0=Dedicated Core #0, 1=Dedicated Core #1, 8=Shared ADC Core
#define BUCK_VIN_ADCIN          9           ///< Analog input number (e.g. '5' for 'AN5')
#define BUCK_VIN_ADCBUF         ADCBUF9     ///< ADC input buffer of this ADC channel
#define BUCK_VIN_ADCTRIG        PG2TRIGA    ///< Register used for trigger placement
#define BUCK_VIN_TRGSRC         BUCK_PWM1_TRGSRC_TRG1 ///< PWM1 (=PG2) Trigger 2 via PGxTRIGB

/** @} */ // end of group input-voltage-feedback-mcal ~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/** 
 * @ingroup input-voltage-feedback-macros
 * @{ 
 * @brief Conversion macros of input voltage feedback parameters
 * 
 * These conversion macros are used to convert user settings defined as physical 
 * quantities into binary (integer) numbers, which will be written to registers and
 * variables and used in calculations throughout the firmware.
 */
    
#define BUCK_VIN_FEEDBACK_GAIN  (float)((BUCK_VIN_R2) / (BUCK_VIN_R1 + BUCK_VIN_R2)) // DO NOT CHANGE
#define BUCK_VIN_MIN            (uint16_t)(BUCK_VIN_MINIMUM * BUCK_VIN_FEEDBACK_GAIN / ADC_GRANULARITY)   ///< Minimum input voltage
#define BUCK_VIN_NOM            (uint16_t)(BUCK_VIN_NOMINAL * BUCK_VIN_FEEDBACK_GAIN / ADC_GRANULARITY)   ///< Nominal input voltage
#define BUCK_VIN_MAX            (uint16_t)(BUCK_VIN_MAXIMUM * BUCK_VIN_FEEDBACK_GAIN / ADC_GRANULARITY)   ///< Maximum input voltage
#define BUCK_VIN_HYST           (uint16_t)(BUCK_VIN_HYSTERESIS * BUCK_VIN_FEEDBACK_GAIN / ADC_GRANULARITY)  ///< Over Voltage LOck Out voltage    
#define BUCK_VIN_UVLO_TRIP      (uint16_t)(BUCK_VIN_UNDER_VOLTAGE * BUCK_VIN_FEEDBACK_GAIN / ADC_GRANULARITY) ///< Under Voltage LOck Out voltage
#define BUCK_VIN_UVLO_RELEASE   (uint16_t)((BUCK_VIN_UNDER_VOLTAGE + BUCK_VIN_HYSTERESIS) * BUCK_VIN_FEEDBACK_GAIN / ADC_GRANULARITY) ///< Under Voltage LOck Out voltage
#define BUCK_VIN_OVLO_TRIP      (uint16_t)(BUCK_VIN_OVER_VOLTAGE * BUCK_VIN_FEEDBACK_GAIN / ADC_GRANULARITY)  ///< Over Voltage LOck Out voltage
#define BUCK_VIN_OVLO_RELEASE   (uint16_t)((BUCK_VIN_OVER_VOLTAGE - BUCK_VIN_HYSTERESIS) * BUCK_VIN_FEEDBACK_GAIN / ADC_GRANULARITY)  ///< Over Voltage LOck Out voltage
#define BUCK_VIN_ADC_TRGDLY     (uint16_t)(BUCK_VIN_ADC_TRG_DELAY / PWM_CLOCK_PERIOD) ///< Input voltage ADC trigger delay
#define BUCK_VIN_OFFSET         (uint16_t)(BUCK_VIN_FEEDBACK_OFFSET / ADC_GRANULARITY) ///< Input voltage feedback offset

#define BUCK_VIN_NORM_INV_G     (float)(1.0/BUCK_VIN_FEEDBACK_GAIN) ///< Inverted feedback gain required for value normalization
#define BUCK_VIN_NORM_SCALER    (int16_t)(ceil(log(BUCK_VIN_NORM_INV_G)) + 1) ///< VIN normalization  
#define BUCK_VIN_NORM_FACTOR    (int16_t)((BUCK_VIN_NORM_INV_G / pow(2.0, BUCK_VIN_NORM_SCALER)) * (pow(2.0, 15)-1)) ///< VIN normalization factor scaled in Q15

#define BUCK_VIN_RANGE_MAX      (float)(ADC_REFERENCE * BUCK_VIN_NORM_INV_G)

/** @} */ // end of group input-voltage-feedback-macros ~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************************
 * @ingroup output-voltage-feedback-settings
 * @{
 * @brief Declaration of output voltage feedback properties
 * 
 * In this section the output voltage feedback signal scaling, gain, valid signal limits and nominal
 * operating point is specified. Physical quantities are used to define values. Macros are used to 
 * convert given physical values into binary (integer) number to be written into SFRs and variables.
 * *************************************************************************************************/

// Feedback Declarations
#define BUCK_VOUT_NOMINAL           (float)12.000  ///< Nominal output voltage
#define BUCK_VOUT_TOLERANCE_MAX     (float)0.500   ///< Output voltage tolerance [+/-]
#define BUCK_VOUT_TOLERANCE_MIN     (float)0.100   ///< Output voltage tolerance [+/-]
    
#define BUCK_VOUT_DIV_R1            (float)(18.00) ///< Upper voltage divider resistor in kOhm
#define BUCK_VOUT_DIV_R2            (float)(4.750) ///< Lower voltage divider resistor in kOhm
#define BUCK_VOUT_FEEDBACK_OFFSET   (float)(0.0)   ///< Physical, static signal offset in [V]
#define BUCK_VOUT_ADC_TRG_DELAY     (float)(0.0e-9) ///< Trigger delay in [sec]

/** @} */ // end of group output-voltage-feedback-settings ~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/** 
 * @ingroup output-voltage-feedback-mcal
 * @{ 
 * @brief ADC input assignments of output voltage feedback signals
 * 
 * In this section the ADC input channels, related ADC result buffers, trigger
 * sources and interrupt vectors are defined. These settings allow the fast 
 * re-assignments of feedback signals in case of hardware changes.
 */

// Peripheral Assignments
#define BUCK_VOUT_ANSEL             _ANSELA0    ///< GPIO analog function mode enable bit
#define BUCK_VOUT_ADCCORE           0           ///< 0=Dedicated Core #0, 1=Dedicated Core #1, 8=Shared ADC Core
#define BUCK_VOUT_ADCIN             0           ///< Analog input number (e.g. '5' for 'AN5')
#define BUCK_VOUT_ADCBUF            ADCBUF0     ///< ADC input buffer of this ADC channel
#define BUCK_VOUT_ADCTRIG           PG2TRIGA    ///< Register used for trigger placement
#define BUCK_VOUT_TRGSRC            BUCK_PWM1_TRGSRC_TRG1 ///< PWM1 (=PG2) Trigger 1 via PGxTRIGA

/** @} */ // end of group output-voltage-feedback-mcal ~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/** 
 * @ingroup output-voltage-feedback-macros
 * @{ 
 * @brief Conversion macros of output voltage feedback parameters
 * 
 * These conversion macros are used to convert user settings defined as physical 
 * quantities into binary (integer) numbers, which will be written to registers and
 * variables and used in calculations throughout the firmware.
 */

#define BUCK_VOUT_FEEDBACK_GAIN (float)((BUCK_VOUT_DIV_R2) / (BUCK_VOUT_DIV_R1 + BUCK_VOUT_DIV_R2)) ///< Macro calculating the integer number equivalent of the output voltage feedback gain

#define BUCK_VOUT_REF           (uint16_t)(BUCK_VOUT_NOMINAL * BUCK_VOUT_FEEDBACK_GAIN / ADC_GRANULARITY) ///< Macro calculating the integer number equivalent of the output voltage reference given above in [V]
#define BUCK_VOUT_NOM           BUCK_VOUT_REF ///< Alias macro of the integer number equivalent of the nominal output voltage given above in [V]
#define BUCK_VOUT_DEV_TRIP      (uint16_t)(BUCK_VOUT_TOLERANCE_MAX * BUCK_VOUT_FEEDBACK_GAIN / ADC_GRANULARITY) ///< Macro calculating the integer number equivalent of the maximum allowed output voltage deviation given above in [V], which will lead to a converter shut down when exceeded.
#define BUCK_VOUT_DEV_RELEASE   (uint16_t)(BUCK_VOUT_TOLERANCE_MIN * BUCK_VOUT_FEEDBACK_GAIN / ADC_GRANULARITY) ///< Macro calculating the integer number equivalent of the maximum allowed output voltage deviation given above in [V], which needs to be underrun before a shut-down converter can recover
#define BUCK_VOUT_OFFSET        (uint16_t)(BUCK_VOUT_FEEDBACK_OFFSET / ADC_GRANULARITY) ///< Macro calculating the integer number equivalent of the physical, static signal offset of this feedback channel
#define BUCK_VOUT_ADC_TRGDLY    (uint16_t)(BUCK_VOUT_ADC_TRG_DELAY / PWM_CLOCK_PERIOD) ///< Macro calculating the integer number equivalent of the signal chain time delay between internal PWM timebase and effective switching edge of the leading FET

#define BUCK_VOUT_NORM_INV_G    (float)(1.0/BUCK_VOUT_FEEDBACK_GAIN) ///< Inverted feedback gain required for value normalization
#define BUCK_VOUT_NORM_SCALER   (int16_t)(ceil(log(BUCK_VOUT_NORM_INV_G)) + 1) ///< VOUT normalization  
#define BUCK_VOUT_NORM_FACTOR   (int16_t)((BUCK_VOUT_NORM_INV_G / pow(2.0, BUCK_VOUT_NORM_SCALER)) * (pow(2.0, 15)-1)) ///< VOUT normalization factor scaled in Q15

#define BUCK_VOUT_RANGE_MAX     (float)(ADC_REFERENCE * BUCK_VOUT_NORM_INV_G) ///< Macro calculating the integer number equivalent of the total output voltage range defined by the settings given above in [V]]
    
/** @} */ // end of group output-voltage-feedback-macros ~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************************
 * @ingroup phase-current-feedback-settings
 * @{
 * @brief Declaration of phase-current feedback properties
 * 
 * <b>Description:</b>
 * In this section the phase-current feedback signal scaling, gain, valid signal limits and nominal
 * operating point is specified. Physical quantities are used to define parameter values to ease
 * the system configuration. 
 * 
 * Macros are used to convert given physical values into binary (integer) number to be written
 * into SFRs and variables and being used in runtime calculations.  
 * (see \ref phase-current-feedback-macros for details)
 * *************************************************************************************************/

// Feedback Declarations
#define BUCK_IOUT_MINIMUM           (float) 0.000       ///< absolute minimum output current (average)
#define BUCK_IOUT_MAXIMUM           (float) 26.50       ///< absolute maximum output current (average)
#define BUCK_IOUT_RELEASE           (float) 24.00       ///< current reset level after over current event

#define BUCK_ISNS_FEEDBACK_GAIN     (float) 0.050       ///< Phase Current Gain in V/A
#define BUCK_ISNS_MINIMUM           (float) 0.000       ///< absolute minimum phase current (average)
#define BUCK_ISNS_MAXIMUM           (float) 26.50       ///< absolute maximum phase current (average)
#define BUCK_ISNS_RELEASE           (float) 24.00       ///< current reset level after over current event
#define BUCK_ISNS_REFERENCE         (float) 1.000       ///< output current reference (average)
#define BUCK_ISNS_REFERENCE_STARTUP (float) 22.00       ///< maximum output current (average) at startup
#define BUCK_ISNS_ADC_TRG_DELAY     (float) 120.0e-9    ///< ADC trigger delay for current sense in [sec]

#define BUCK_ISNS1_FEEDBACK_OFFSET  (float) 1.650       ///< current sense #1 feedback offset (average)
#define BUCK_ISNS2_FEEDBACK_OFFSET  (float) 1.650       ///< current sense #2 feedback offset (average)

/** @} */ // end of group

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/** 
 * @ingroup phase-current-feedback-macros
 * @{ 
 * @brief Conversion macros of phase current feedback parameters
 * 
 * These conversion macros are used to convert user settings defined as physical 
 * quantities into binary (integer) numbers, which will be written to registers and
 * variables and used in calculations throughout the firmware.
 */

// Phase Current Feedback Settings Conversion Macros
#define BUCK_ISNS_REF           (uint16_t)((BUCK_ISNS_REFERENCE * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Output Current Reference
#define BUCK_ISNS_REF_STARTUP   (uint16_t)((BUCK_ISNS_REFERENCE_STARTUP * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Output Current Startup Reference

#define BUCK_IOUT_MIN           (uint16_t)(int16_t)((BUCK_IOUT_MINIMUM * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Over Current Limit
#define BUCK_IOUT_OCL           (uint16_t)((BUCK_IOUT_MAXIMUM * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Over Current Limit
#define BUCK_IOUT_OCL_RELEASE   (uint16_t)((BUCK_IOUT_RELEASE * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Over Current Release Level

#define BUCK_ISNS1_MIN          (uint16_t)(int16_t)(((BUCK_ISNS_MINIMUM-BUCK_ISNS1_FEEDBACK_OFFSET) * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Over Current Limit
#define BUCK_ISNS1_OCL          (uint16_t)(((BUCK_ISNS_MAXIMUM-BUCK_ISNS1_FEEDBACK_OFFSET) * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Over Current Limit
#define BUCK_ISNS1_OCL_RELEASE  (uint16_t)(((BUCK_ISNS_RELEASE-BUCK_ISNS1_FEEDBACK_OFFSET) * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Over Current Release Level
#define BUCK_ISNS1_OFFFSET      (uint16_t)(BUCK_ISNS1_FEEDBACK_OFFSET / ADC_GRANULARITY)

#define BUCK_ISNS2_MIN          (uint16_t)(int16_t)(((BUCK_ISNS_MINIMUM-BUCK_ISNS2_FEEDBACK_OFFSET) * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Over Current Limit
#define BUCK_ISNS2_OCL          (uint16_t)(((BUCK_ISNS_MAXIMUM-BUCK_ISNS2_FEEDBACK_OFFSET) * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Over Current Limit
#define BUCK_ISNS2_OCL_RELEASE  (uint16_t)(((BUCK_ISNS_RELEASE-BUCK_ISNS2_FEEDBACK_OFFSET) * BUCK_ISNS_FEEDBACK_GAIN) / ADC_GRANULARITY)  ///< Over Current Release Level
#define BUCK_ISNS2_OFFFSET      (uint16_t)(BUCK_ISNS2_FEEDBACK_OFFSET / ADC_GRANULARITY)
#define BUCK_ISNS_ADC_TRGDLY    (uint16_t)(BUCK_ISNS_ADC_TRG_DELAY / PWM_CLOCK_PERIOD)

#define BUCK_ISNS_NORM_INV_G    (float)(1.0/BUCK_ISNS_FEEDBACK_GAIN) ///< Inverted feedback gain required for value normalization
#define BUCK_ISNS_NORM_SCALER   (int16_t)(ceil(log(BUCK_ISNS_NORM_INV_G)) + 1) ///< ISNS normalization  
#define BUCK_ISNS_NORM_FACTOR   (int16_t)((BUCK_ISNS_NORM_INV_G / pow(2.0, BUCK_ISNS_NORM_SCALER)) * (pow(2.0, 15)-1)) ///< ISNS normalization factor scaled in Q15

/** @} */ // end of group phase-current-feedback-macros ~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/** 
 * @ingroup phase-current-feedback-mcal
 * @{ 
 * @brief ADC input assignments of phase current feedback signals
 * 
 * @details
 * In this section the ADC input channels, related ADC result buffers, trigger
 * sources and interrupt vectors are defined. These settings allow the fast 
 * re-assignments of feedback signals in case of hardware changes.
 */
 
// Peripheral Assignments
#define _BUCK_ISNS1_ADCInterrupt    _ADCAN1Interrupt   
#define _BUCK_ISNS1_ADCISR_IF       _ADCAN1IF

#define BUCK_ISNS1_ANSEL            _ANSELA1    ///< GPIO analog function mode enable bit
#define BUCK_ISNS1_ADCCORE          1           ///< 0=Dedicated Core #0, 1=Dedicated Core #1, 2=Shared ADC Core
#define BUCK_ISNS1_ADCIN            1           ///< Analog input number (e.g. '5' for 'AN5')
#define BUCK_ISNS1_ADCBUF           ADCBUF1     ///< ADC input buffer of this ADC channel
#define BUCK_ISNS1_ADCTRIG          PG2TRIGB    ///< Register used for trigger placement
#define BUCK_ISNS1_TRGSRC           BUCK_PWM1_TRGSRC_TRG2 ///< PWM1 (=PG2) Trigger 2 via PGxTRIGB

#define _BUCK_ISNS2_ADCInterrupt    _ADCAN4Interrupt   
#define _BUCK_ISNS2_ADCISR_IF       _ADCAN4IF

#define BUCK_ISNS2_ANSEL            _ANSELA4    ///< GPIO analog function mode enable bit
#define BUCK_ISNS2_ADCCORE          8           ///< 0=Dedicated Core #0, 1=Dedicated Core #1, 2=Shared ADC Core
#define BUCK_ISNS2_ADCIN            4           ///< Analog input number (e.g. '5' for 'AN5')
#define BUCK_ISNS2_ADCBUF           ADCBUF4     ///< ADC input buffer of this ADC channel
#define BUCK_ISNS2_ADCTRIG          PG4TRIGB    ///< Register used for trigger placement
#define BUCK_ISNS2_TRGSRC           BUCK_PWM2_TRGSRC_TRG2 ///< PWM2 (=PG4) Trigger 2 via PGxTRIGB

/** @} */ // end of group phase-current-feedback-mcal ~~~~~~~~~~~~~~~~~~~~~~~~~

    
 /**************************************************************************************************
 * @ingroup adaptive-control
 * @{
 * @brief Declaration of additional hardware-specific defines required for adaptive gain control
 * 
 * <b>Description:</b>
 * In this section additional macros are defined to calculate constant parameters for the
 * adaptive gain modulation algorithm using user defined settings declared in their respective
 * sections. Any change of these parameters will also result in a change of the values of the 
 * gain modulation parameters of this section.
 * *************************************************************************************************/
   
#define BUCK_VL_MINIMUM         (float)(BUCK_VIN_UNDER_VOLTAGE - BUCK_VOUT_RANGE_MAX) ///< Minimum input voltage - maximum output voltate
#define BUCK_VL_NOMINAL         (float)(BUCK_VIN_NOMINAL       - BUCK_VOUT_NOMINAL) ///< Nominal input voltage - nominal output voltate
#define BUCK_VL_MAXIMUM         (float)(BUCK_VIN_RANGE_MAX     - 0) ///< Maximum input voltage - 0

#define BUCK_AGC_FACTOR_MAX     (float)(BUCK_VL_NOMINAL / BUCK_VL_MINIMUM) ///< Floating point number of the maximumm limit of the adaptive gain modulation factor (float)

// To calculate the voltage across the inductor, input and output voltage ADC results need to be normalized. The normalization factor is determined here
// Each input voltage sample has to be multiplied with this scaling factor to allow the calculation of the instantaneous voltage across the inductor
#define BUCK_VIN_NORM_FCT       (float)(BUCK_VOUT_FEEDBACK_GAIN / BUCK_VIN_FEEDBACK_GAIN)   ///< VIN-2-VOUT Normalization Factor
#define BUCK_AGC_IO_NORM_SCALER (int16_t)(ceil(log(BUCK_VIN_NORM_FCT)) + 1) ///< Nominal VL Q15 scaler  
#define BUCK_AGC_IO_NORM_FACTOR (int16_t)((BUCK_VIN_NORM_FCT / pow(2.0, BUCK_AGC_IO_NORM_SCALER)) * (pow(2.0, 15)-1)) ///< Nominal VL Q15 factor 

// The AGC compare value is defined at nominal input voltage and output voltage 
#define BUCK_AGC_MEDIAN         (int16_t)(((float)BUCK_VIN_NOM * BUCK_VIN_NORM_FCT) - BUCK_VOUT_NOM) ///< Adaptive gain modulation factor at nominal operating point
#define BUCK_AGC_NOM_SCALER     (uint16_t)(ceil(log(BUCK_AGC_FACTOR_MAX)) + 1) ///< Bit-shift scaler of the floating point number of the maimum limit of the adaptive gain modulation factor
#define BUCK_AGC_NOM_FACTOR     (uint16_t)(0x7FFF >> BUCK_AGC_NOM_SCALER) ///< Fractional of the floating point number of the maimum limit of the adaptive gain modulation factor

/** @} */ // end of group

/**************************************************************************************************
 * @ingroup startup-timing-settings
 * @{
 * @brief Global defines for soft-start specific parameters
 * 
 * @details
 * This section is used to define power supply startup timing settings. The soft-start sequence 
 * is part of the power controller. It allows to program specific timings for 
 *   - Power On Delay
 *   - Ramp Period 
 *   - Power Good Delay
 * 
 * After the startup has passed these three timing periods, the power supply is ending up in 
 * "normal" operation, continuously regulating the output until a fault is detected or the 
 * operating state is changed for any other reason. When the output voltage reference is changed, 
 * the power control state machine will use the voltage ramp slope defined here to tune from the 
 * recent voltage reference to the new reference value. During this period the BUSY-bit of the 
 * power controller (status word, bit #7) will be set. This status bit will be cleared automatically
 * by the power controller state machine once the new reference value has been applied and the 
 * converter is back in constant regulation mode.
 * 
 * Pre-compiler macros are used to translate physical values into binary (integer) numbers to 
 * be written to SFRs and variables.  
 * (see \ref startup-timing-macros for details)
 * 
 * <b>Please Note:</b><br>
 * On EPC9143 Rev 4 it takes roughly 50 ms until the auxiliary power has been started
 * and the controller completes self-test and peripheral configuration. After this period
 * the controller starts to execute the power control state machine.
 *  
 * This additional startup delay of ~50 ms is not considered here and needs to be taken into 
 * account when adjusting startup timing.
 **************************************************************************************************/

#define BUCK_POWER_ON_DELAY          (float) 200e-3 ///< power on delay in [sec]
#define BUCK_VRAMP_PERIOD            (float) 100e-3 ///< voltage ramp-up period in [sec]
#define BUCK_IRAMP_PERIOD            (float) 100e-3 ///< output current ramp-up period in [sec]
#define BUCK_POWER_GOOD_DELAY        (float) 200e-3 ///< power good delay in [sec]

/** @} */ // end of group startup-timing-settings ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/** 
 * @ingroup startup-timing-macros
 * @{ 
 * @brief Conversion Macros of Startup Timing Settings
 * 
 * These conversion macros are used to convert user settings defined as physical 
 * quantities into binary (integer) numbers, which will be written to registers and
 * variables and used in calculations throughout the firmware.
 */

#define BUCK_POD       (uint16_t)(((float)BUCK_POWER_ON_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0)
#define BUCK_VRAMP_PER (uint16_t)(((float)BUCK_VRAMP_PERIOD / (float)MAIN_EXECUTION_PERIOD)-1.0)
#define BUCK_VREF_STEP (uint16_t)((float)BUCK_VOUT_REF / (float)(BUCK_VRAMP_PER + 1.0))
#define BUCK_IRAMP_PER (uint16_t)(((float)BUCK_IRAMP_PERIOD / (float)MAIN_EXECUTION_PERIOD)-1.0)
#define BUCK_IREF_STEP (uint16_t)((float)BUCK_ISNS_REF / (float)(BUCK_VRAMP_PER + 1.0))
#define BUCK_PGD       (uint16_t)(((float)BUCK_POWER_GOOD_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0)

/** @} */ // end of group startup-timing-macros ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**************************************************************************************************
 * @ingroup fault-response-settings
 * @{
 * @brief Global defines for fault-monitor related parameters
 * 
 * @details
 * This section is used to define power supply fault object timing settings. The fault monitor 
 * is continuously monitoring declared data objects at the high-priority task frequency defined by 
 * \ref MAIN_EXECUTION_PERIOD. Based on this known interval, filtering delays for fault trip and 
 * fault recovery events to allow users to adjust the fault detection sensitivity.
 * 
 * - Fault Trip Event Delay   
 * This setting defines for how long a fault condition has to be continuously active before the 
 * effective fault trip status/event will be triggered.
 * 
 * - Fault Recovery Event Delay   
 * This setting defines for how long a fault condition has to be continuously cleared before the 
 * effective fault recovery status/event will be triggered.
 * 
 *************************************************************************************************/

#define BUCK_UVLO_TRIP_DELAY         (float) 5e-3   ///< under voltage lock out trip delay in [sec]
#define BUCK_UVLO_RECOVERY_DELAY     (float) 500e-3 ///< under voltage lock out recovery delay in [sec]
#define BUCK_OVLO_TRIP_DELAY         (float) 5e-3   ///< over voltage lock out trip delay in [sec]
#define BUCK_OVLO_RECOVERY_DELAY     (float) 500e-3 ///< over voltage lock out recovery delay in [sec]
#define BUCK_REGERR_TRIP_DELAY       (float) 25e-3  ///< regulation error trip delay in [sec]
#define BUCK_REGERR_RECOVERY_DELAY   (float) 500e-3 ///< regulation error recovery delay in [sec]
#define BUCK_OCP_TRIP_DELAY          (float) 2e-3   ///< over current proection trip delay in [sec]
#define BUCK_OCP_RECOVERY_DELAY      (float) 500e-3 ///< over current proection recovery delay in [sec]

/** @} */ // end of group fault-response-settings ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/** 
 * @ingroup fault-response-macros
 * @{ 
 * @brief Conversion Macros of Fault Response Timing Settings
 * 
 * These conversion macros are used to convert user settings defined as physical 
 * quantities into binary (integer) numbers, which will be written to registers and
 * variables and used in calculations throughout the firmware.
 */

#define BUCK_UVLO_TDLY   (uint16_t)(((float)      BUCK_UVLO_TRIP_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0) ///< under voltage lock out trip delay conversion nacro
#define BUCK_UVLO_RDLY   (uint16_t)(((float)  BUCK_UVLO_RECOVERY_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0) ///< under voltage lock out recovery delay conversion nacro
#define BUCK_OVLO_TDLY   (uint16_t)(((float)      BUCK_OVLO_TRIP_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0) ///< over voltage lock out trip delay conversion nacro
#define BUCK_OVLO_RDLY   (uint16_t)(((float)  BUCK_OVLO_RECOVERY_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0) ///< over voltage lock out recovery delay conversion nacro
#define BUCK_REGERR_TDLY (uint16_t)(((float)    BUCK_REGERR_TRIP_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0) ///< regulation error trip delay conversion macro
#define BUCK_REGERR_RDLY (uint16_t)(((float)BUCK_REGERR_RECOVERY_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0) ///< regulation error recovery delay conversion macro
#define BUCK_OCP_TDLY    (uint16_t)(((float)       BUCK_OCP_TRIP_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0) ///< over current protection trip Delay conversion macro
#define BUCK_OCP_RDLY    (uint16_t)(((float)   BUCK_OCP_RECOVERY_DELAY / (float)MAIN_EXECUTION_PERIOD)-1.0) ///< over current protection recovery delay conversion nacro

/** @} */ // end of group fault-response-macros ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
/**************************************************************************************************
 * @ingroup control-interrupt-vector-declarations
 * @{
 * @brief Control loop Interrupt Vector Settings
 * 
 * <b>Description</b>
 * Control loops are called in dedicated interrupt service routines of PWM events, ADC events
 * or triggered by timers. This section allows users to set and modify the interrupt service 
 * routine triggers and their priority to set up and optimize the control system interrupt 
 * structure.
 * 
 * *************************************************************************************************/
    
// Hardware-dependent defines
#define BUCK_VOUT_TRIG_PWM  0   ///< Buck VOUT control loop is called in PWM interrupt
#define BUCK_VOUT_TRIG_ADC  1   ///< Buck VOUT control loop is called in ADC interrupt

#define BUCK_VOUT_TRIGGER_MODE  BUCK_VOUT_TRIG_PWM ///< Currently selected voltage loop interrupt vector
#define BUCK_VOUT_ISR_PRIORITY  5 ///< Voltage loop interrupt vector priority (valid settings between 0...6 with 6 being the highest priority)

#if (BUCK_VOUT_TRIGGER_MODE == BUCK_VOUT_TRIG_ADC)    
  #define _BUCK_VLOOP_Interrupt     _ADCAN0Interrupt ///< Interrupt vector function call label
  #define _BUCK_VLOOP_ISR_IP        _ADCAN0IP ///< Interupt vector priority register bits
  #define _BUCK_VLOOP_ISR_IF        _ADCAN0IF ///< Interupt vector flag bit register bit
  #define _BUCK_VLOOP_ISR_IE        _ADCAN0IE ///< Interupt vector enable bit register bit
#elif (BUCK_VOUT_TRIGGER_MODE == BUCK_VOUT_TRIG_PWM)
  #define _BUCK_VLOOP_Interrupt     _PWM2Interrupt ///< Interrupt vector function call label
  #define _BUCK_VLOOP_ISR_IP        _PWM2IP ///< Interupt vector priority register
  #define _BUCK_VLOOP_ISR_IF        _PWM2IF ///< Interupt vector flag bit register bit
  #define _BUCK_VLOOP_ISR_IE        _PWM2IE ///< Interupt vector enable bit register bit
#endif
/** @} */ // end of group

#endif	/* EPC9143_R40_HARDWARE_DESCRIPTOR_H */
