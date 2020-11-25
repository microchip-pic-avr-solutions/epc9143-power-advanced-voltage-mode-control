/**
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms, you may use Microchip software
 *  and any derivatives exclusively with Microchip products. You're responsible
 *  for complying with 3rd party license terms applicable to your use of 3rd
 *  party software (including open source software) that may accompany Microchip
 *  software.
 *
 *  SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 *  APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 *  MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
 *  HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
 *  THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
 *  CLAIMS RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY,
 *  YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 *  @file    dev_buck_typedef.h
 *  @brief   This file contains APIs to for the power control
 *
 *  @note
 *  Microchip Technology Inc. has followed development methods required by
 *  IEC-60730 and performed extensive validation and static testing to ensure
 *  that the code operates as intended. Any modification to the code can
 *  invalidate the results of Microchip's validation and testing.
 *
 */

/* 
 * File:   dev_buck_typedef.h
 * Author: M91406
 * Comments: Type definitions for the multiphase BUCK converter data object
 * Revision history: 
 * 1.0  initial release
 * 1.1  restructured phase arrays in data object to optimize code execution and stay with unified API
 *      with regards to other power converter object libraries
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BUCK_CONVERTER_TYPE_DEF_H
#define	BUCK_CONVERTER_TYPE_DEF_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer number data types
#include <stdbool.h> // include standard boolean data types (true/false)
#include <stddef.h> // include standard definition data types

#include "pwr_control/drivers/npnz16b.h"
#include "config/hal.h"


/**
 * @addtogroup power-handler-variable
 * @{
 */
#define BUCK_MPHASE_COUNT                BUCK_NO_OF_PHASES

// Controller Status Bits
#define BUCK_STAT_READY                  0b0000000000000001
#define BUCK_STAT_ADC_ACTIVE             0b0000000000000010
#define BUCK_STAT_PWM_ACTIVE             0b0000000000000100
#define BUCK_STAT_POWERSOURCE_DETECTED   0b0000000000001000
#define BUCK_STAT_CS_SENSE_READY         0b0000000000010000
    
#define BUCK_STAT_FORCED_SHUT_DOWN       0b0000000010000000
#define BUCK_STAT_BUSY                   0b0000000100000000

// Controller Control Bits
#define BUCK_STAT_GO                     0b0010000000000000
#define BUCK_STAT_AUTORUN                0b0100000000000000
#define BUCK_STAT_NO_AUTORUN             0b0000000000000000

#define BUCK_STAT_ENABLED                0b1000000000000000
#define BUCK_STAT_DISABLED               0b0000000000000000
/**@}*/

/**
 * @addtogroup power-handler-enum
 * @{  
 */

/****************************************************************************************************
 * @enum BUCK_OPSTATES_e
 * @brief  Enumeration of state machine operating states 
 **************************************************************************************************** */
typedef enum BUCK_OPSTATES_e {  // Enumeration of state machine operating states 
    
    BUCK_OPSTATE_ERROR          = 0x00,  ///< power converter control state #0: in case of an error, state machine will reset to RESET
    BUCK_OPSTATE_INITIALIZE     = 0x01,  ///< power converter control state #1: initialize variables and hijack controller reference
    BUCK_OPSTATE_RESET          = 0x02,  ///< power converter control state #2: Initializing variable but bypassing delays
    BUCK_OPSTATE_STANDBY        = 0x03,  ///< power converter control state #3: power converter control state #2 standing by, ready to launch, waiting for GO (no action)
    BUCK_OPSTATE_RAMPUP         = 0x04,  ///< power converter control state #4: Startup handler sub-state machine
    BUCK_OPSTATE_ONLINE         = 0x05   ///< power converter control state #5: Output in regulation and power is OK (normal continuous operation)
        
} BUCK_OPSTATE_t; // Enumeration of state machine operating states 


/****************************************************************************************************
 * @enum BUCK_SUBSTATES_e
 * @brief Enumeration of state machine operating sub-states 
 **************************************************************************************************** */
typedef enum BUCK_SUBSTATES_e {  // Enumeration of state machine operating sub-states

    BUCK_OPSTATE_POWER_ON_DELAY = 0x00,  ///< power converter control state #3: power on delay (no action)
    BUCK_OPSTATE_PREPARE_V_RAMP = 0x01,  ///< power converter control state #4: turn on PWM outputs and enable controller
    BUCK_OPSTATE_V_RAMP_UP      = 0x02,  ///< power converter control state #5: perform output voltage ramp up based on parameters and system response 
    BUCK_OPSTATE_I_RAMP_UP      = 0x03,  ///< power converter control state #6: perform output current ramp up based on parameters and system response (average current mode only)
    BUCK_OPSTATE_PWRGOOD_DELAY  = 0x04   ///< power converter control state #7: Output reached regulation point but waits until things have settled
    
} BUCK_OP_SUBSTATES_t; // Enumeration of state machine operating sub-states 

/****************************************************************************************************
 * @enum BUCK_OPSTATE_RETURNS_e
 * @brief Enumeration of state machine operating state return values
 **************************************************************************************************** */
typedef enum BUCK_OPSTATE_RETURNS_e {  // Enumeration of state machine operating state return values
    
    BUCK_OPSRET_ERROR           = 0x0000,  ///< power converter state return #0: internal error occurred
    BUCK_OPSRET_COMPLETE        = 0x0001,  ///< power converter state return #1: operation state has completed
    BUCK_OPSRET_REPEAT          = 0x0002   ///< power converter state return #2: operation state is in progress and needs to be recalled
        
} BUCK_OPSTATE_RETURNS_t; // Enumeration of state machine operating state return values

/****************************************************************************************************
 * @enum BUCK_CONTROL_MODE_e
 * @brief  Enumeration of the power supply mode control
 **************************************************************************************************** */
typedef enum {
    
    BUCK_CONTROL_MODE_VMC = 0,              ///< Voltage Mode Control
//    BUCK_CONTROL_MODE_PCMC = 1,           // Peak Current Mode Control (not supported yet)
    BUCK_CONTROL_MODE_ACMC = 2              ///< Average Current Mode Control
        
} BUCK_CONTROL_MODE_e;

/**@}*/
/**
 * @addtogroup power-handler-struct
 * @{
 */
/*****************************************************************************************************
 *  @struct BUCK_CONVERTER_STATUS_s
 *  @brief Generic power controller status word
 * 
 * <b>Description: </b><br>
 * The power controller status/control word contains status (low-byte) and control bits (high-byte). 
 * -# Status Bits:
 *      - ADC_ACTIVE: ADC is active and running (read only)
 *      - PWM_STARTED: PWM is active and running generating ADC triggers (read only)
 *      - POWERSOURCE_DETECTED: A valid power source has been detected allowing the converter to run (read only)
 *      - CS_READ: Current sense feedback ready (read only)
 *      - FORCED_SHUT_DOWN: Control(Status bit for external sowftware components forcing the converter to stay off
 *      - BUSY: Converter is currently going through an internal process (e.g. ramp up/down) (read only)
 *      
 * -# Control Bits
 *      - ENABLE: Enables/Disables the power converter
 *      - AUTORUN: When set, the power converter will automatically start up once all status bits are set accordingly
 *      - GO: Control bit to manually start the power converter if (AUTOSTART=0)
 *  
 **************************************************************************************************** */
typedef struct BUCK_CONVERTER_STATUS_s
{
    union {
    struct{
        volatile bool ready:1;                  ///< Bit #0: status bit, indicating buck converter is initialized and ready to run
        volatile bool adc_active:1;             ///< Bit #1: indicating that ADC has been started and samples are taken
        volatile bool pwm_active:1;             ///< Bit #2: indicating that PWM has been started and ADC triggers are generated
        volatile unsigned :1;                   ///< Bit #3: (reserved)
        volatile bool cs_calib_complete :1;     ///< Bit #4: indicating that current sensor calibration has completed
        volatile bool fault_active :1;          ///< Bit #5: Flag bit indicating system is in enforced shut down mode (usually due to a fault condition)
        volatile unsigned :1;                   ///< Bit #6: (reserved)
        volatile bool busy :1;                  ///< Bit #7:  Flag bit indicating that the state machine is executing a process (e.g. startup-ramp)

        volatile bool cs_calib_enable :1;       ///< Bit #8:  Flag bit indicating that current sensors need to calibrated
        volatile unsigned :1;                   ///< Bit #9:  (reserved)
        volatile unsigned :1;                   ///< Bit #10: (reserved)
        volatile unsigned :1;                   ///< Bit #11: (reserved)
        volatile bool suspend :1;               ///< Bit #12: Control bit to put the converter in suspend mode (turned off while ENABLE bit is still on)
        volatile bool GO :1;                    ///< Bit #13: When set, the GO-bit fires up the power supply
        volatile bool autorun :1;               ///< Bit #14: Control bit determining if charger is starting automatically or on command (using the GO bit)
        volatile bool enabled :1;               ///< Bit #15: Control bit enabling/disabling the charger port
    } __attribute__((packed)) bits;             ///< data structure for single bit addressing operations

	volatile uint16_t value; // buffer for 16-bit word read/write operations
    };
    
} BUCK_CONVERTER_STATUS_t;

/****************************************************************************************************
 * @struct BUCK_STATE_ID_s 
 * @brief data structure for the buck statement ID for sub-operating and operating states 
 **************************************************************************************************** */
typedef struct BUCK_STATE_ID_s 
{
    union {
    struct { 
        volatile enum BUCK_OPSTATES_e opstate_id;   ///< Most recent operating state of main state machine
        volatile enum BUCK_SUBSTATES_e substate_id; ///< Most recent operating state of active sub state machine
    } bits;
    volatile uint32_t value; // full state ID value access to main and sub-state machine state
    };
    
} BUCK_STATE_ID_t;

/****************************************************************************************************
 * @struct BUCK_STARTUP_SETTINGS_s
 * @brief Generic power controller startup settings
 * 
 * <b>Description:</b><br>
 * This data structure is used to set the startup settings such as power on delay, power good delay
 * and ramp up time. It further covers private values like startup counters and reference values
 * for voltage and current, which are used internally by the controller (read only) but are still
 * accessible for external code modules for monitoring, diagnostics and fault handling purposes.
 * 
 **************************************************************************************************** */
typedef struct BUCK_STARTUP_PERIOD_HANDLER_s {
    
    volatile uint16_t counter;      ///< Soft-Start Execution Counter (read only)
    volatile uint16_t period;       ///< Soft-Start Period (POD, RAMP PERIOD, PGD, etc.)
    volatile uint16_t reference;    ///< Internal dummy reference used to increment/decrement controller reference
    volatile uint16_t ref_inc_step; ///< Size/value of one reference increment/decrement or this period
    
} BUCK_STARTUP_PERIOD_HANDLER_t; // Power converter soft-start auxiliary variables


/****************************************************************************************************
 * @struct BUCK_CONVERTER_STARTUP_s
 * @brief 
 * *************************************************************************************************** */
 
typedef struct BUCK_CONVERTER_STARTUP_s {
    
    volatile struct BUCK_STARTUP_PERIOD_HANDLER_s power_on_delay;
    volatile struct BUCK_STARTUP_PERIOD_HANDLER_s power_good_delay;
    volatile struct BUCK_STARTUP_PERIOD_HANDLER_s i_ramp;
    volatile struct BUCK_STARTUP_PERIOD_HANDLER_s v_ramp;
    
} BUCK_CONVERTER_STARTUP_t; // Power converter start-up settings and variables

// ==============================================================================================
// BUCK converter runtime data object 
// ==============================================================================================


/****************************************************************************************************
 * @struct BUCK_CONVERTER_DATA_s
 * @brief 
 * 
 **************************************************************************************************** */
typedef struct BUCK_CONVERTER_DATA_s {
    
    volatile uint16_t i_sns[BUCK_MPHASE_COUNT];     ///< BUCK output current
    volatile uint16_t i_out;                        ///< BUCK common output current
    volatile uint16_t v_in;                         ///< BUCK input voltage
    volatile uint16_t v_out;                        ///< BUCK output voltage
    volatile uint16_t temp;                         ///< BUCK board temperature
    
    volatile uint16_t control_input;                ///< BUCK most recent control input value (raw input)
    volatile uint16_t control_error;                ///< BUCK most recent control error value
    volatile uint16_t control_output;               ///< BUCK most recent control output value
    
}BUCK_CONVERTER_DATA_t;         // BUCK runtime data

/****************************************************************************************************
 * @struct BUCK_CONVERTER_CONTROL_s
 * @brief Generic power controller control settings
 * 
 * <b>Description:</b><br>
 * This data structure is used to set the overall settings to allow external software instances 
 * to control the power control object, such as voltage and current references.
 *  
 **************************************************************************************************** */
typedef struct BUCK_CONVERTER_SETTINGS_s {
    
    volatile BUCK_CONTROL_MODE_e control_mode;  ///< Fundamental control mode 
    volatile uint16_t no_of_phases;             ///< number of converter phases
    volatile uint16_t v_ref;                    ///< User reference setting used to control the power converter controller
    volatile uint16_t i_ref;                    ///< User reference setting used to control the power converter controller
    
} BUCK_CONVERTER_SETTINGS_t;  ///> Buck converter main settings


/****************************************************************************************************
 * @struct BUCK_LOOP_SETTINGS_s
 * @brief Generic power control loop settings
 * 
 * <b>Description:</b><br>
 * This data structure is used to set the control loop settings such as pointers to controller 
 * objects and its function calls as well as basic user settings such as reference, feedback
 * signal offsets, trigger delays and minimum/maximum output clamping values.
 * 
 * *************************************************************************************************** */
typedef struct BUCK_LOOP_SETTINGS_s {
    
    // Properties (user settings)
    volatile uint16_t reference;            ///< Control loop reference variable
    volatile uint16_t feedback_offset;      ///< Feedback offset value for calibration or bi-direction feedback signals
    volatile uint16_t trigger_offset;       ///< ADC trigger offset value for trigger fine-tuning
    volatile int16_t  minimum;              ///< output clamping value (minimum)
    volatile uint16_t maximum;              ///< output clamping value (maximum)
    // Control Loop Object
    volatile struct NPNZ16b_s* controller;  ///< pointer to control loop object data structure
    // Function pointers
    volatile uint16_t (*ctrl_Initialize)(volatile struct NPNZ16b_s*); ///< Function pointer to INIT routine
    void (*ctrl_Reset)(volatile struct NPNZ16b_s*); ///< Function pointer to RESET routine
    void (*ctrl_Update)(volatile struct NPNZ16b_s*); ///< Function pointer to UPDATE routine
    void (*ctrl_Precharge)(volatile struct NPNZ16b_s*, volatile fractional, volatile fractional); ///< Function pointer to PRECHARGE routine
    
} BUCK_LOOP_SETTINGS_t; ///< User defined settings for control loops; 

/****************************************************************************************************
 * @struct BUCK_SWITCH_NODE_SETTINGS_s
 * @brief Generic power converter switch-node specifications
 * 
 * <b>Description: </b><br>
 * This data structure is used to set the converter switch-node specifications declaring which
 * PWM channel is used as well as its switching frequency, phase-shift, dead times and duty ratio
 * limits.
 * 
 * *************************************************************************************************** */
typedef struct BUCK_SWITCH_NODE_SETTINGS_s {
    
    volatile uint16_t pwm_instance;         ///< number of the PWM channel used
    volatile uint16_t gpio_instance;        ///< GPIO instance of the selected PWM generator
    volatile uint16_t gpio_high;            ///< GPIO port pin-number of PWMxH of the selected PWM generator
    volatile uint16_t gpio_low;             ///< GPIO port pin-number of PWMxL of the selected PWM generator
    volatile bool     master_period_enable; ///< Selecting MASTER or Individual period register
    volatile bool     high_resolution_enable; ///< Selecting if PWM module should use high-resolution mode 
    volatile uint16_t period;               ///< Switching period
    volatile uint16_t phase;                ///< Switching signal phase-shift
    volatile uint16_t duty_ratio_init;      ///< Initial duty cycle when the PWM module is being turned on
    volatile uint16_t duty_ratio_min;       ///< Absolute duty cycle minimum during normal operation
    volatile uint16_t duty_ratio_max;       ///< Absolute duty cycle maximum during normal operation
    volatile uint16_t dead_time_rising;     ///< Dead time setting at rising edge of a half-bridge drive
    volatile uint16_t dead_time_falling;    ///< Dead time setting at falling edge of a half-bridge drive
    volatile uint16_t leb_period;           ///< Leading-Edge Blanking period
    volatile uint16_t trigger_scaler;       ///< PWM triggers for ADC will be generated every n-th cycle
    volatile uint16_t trigger_offset;       ///< PWM triggers for ADC will be offset by n cycles
    
} BUCK_SWITCH_NODE_SETTINGS_t; ///< Switching signal timing settings

/****************************************************************************************************
 * @struct BUCK_ADC_INPUT_SCALING_s 
 * @brief Generic power converter feedback specifications
 * 
 * <b>Description:</b><br>
 * This data structure is used to set the converter feedback specifications declaring which
 * ADC channels are used including the individual AD input configuration such as trigger mode,
 * input mode, result format and value normalization.
 * 
 * *************************************************************************************************** */

typedef struct BUCK_ADC_INPUT_SCALING_s {
    
    volatile int16_t factor; ///< Fractional scaling factor (range -1 ... 0.99969)
    volatile int16_t scaler; ///< Feedback number scaler used for number normalization
    volatile int16_t offset; ///< Signal offset as signed integer to be subtracted from ADC input

} BUCK_ADC_INPUT_SCALING_t; ///< ADC input signal scaling = (ADCBUF - <offset>) * <factor> >> 2^<scaler>

/****************************************************************************************************
 * @struct BUCK_ADC_INPUT_SETTINGS_s
 * @brief Generic power converter ADC input channel configuration
 * 
 * <b>Description:</b><br>
 * 
 * *************************************************************************************************** */
typedef struct BUCK_ADC_INPUT_SETTINGS_s {
    
    volatile bool enabled;                  ///< input channel enable bit
    volatile uint16_t* adc_buffer;          ///< pointer to ADC result buffer
    volatile uint16_t gpio_instance;        ///< GPIO instance of the selected PWM generator
    volatile uint8_t adc_input;             ///< number of the ADC input channel used
    volatile uint8_t adc_core;              ///< number of the ADC core connected to the selected channel
    volatile uint8_t trigger_source;        ///< input channel trigger source
    volatile bool interrupt_enable;         ///< input channel interrupt enable bit
    volatile bool early_interrupt_enable;   ///< input channel early interrupt enable bit
    volatile bool differential_input;       ///< input channel differential mode enable bit
    volatile bool signed_result;            ///< input channel singed result mode enable bit
    volatile bool level_trigger;            ///< input channel level trigger mode enable bit
    volatile struct BUCK_ADC_INPUT_SCALING_s scaling; ///< normalization scaling settings

} BUCK_ADC_INPUT_SETTINGS_t; ///< ADC input channel configuration


/****************************************************************************************************
 * @struct BUCK_FEEDBACK_SETTINGS_s
 * @brief 
 * 
 * <b>Description:</b><br>
 * 
 * *************************************************************************************************** */
typedef struct BUCK_FEEDBACK_SETTINGS_s {
    
    volatile struct BUCK_ADC_INPUT_SETTINGS_s ad_vin;                       ///< ADC input sampling input voltage
    volatile struct BUCK_ADC_INPUT_SETTINGS_s ad_vout;                      ///< ADC input sampling output voltage
    volatile struct BUCK_ADC_INPUT_SETTINGS_s ad_isns[BUCK_MPHASE_COUNT];   ///< ADC input sampling phase current
    volatile struct BUCK_ADC_INPUT_SETTINGS_s ad_temp;                      ///< ADC input sampling temperature
    
} BUCK_FEEDBACK_SETTINGS_t; ///< Buck converter feedback declarations

/****************************************************************************************************
 * @struct BUCK_GPIO_SETTINGS_s
 * @brief Generic power converter GPIO specifications
 * 
 * <b>Description:</b><br>
 * This data structure is used to set the converter GPIO specifications declaring which
 * if and which additional GPIOs are used by the converter controller, such as POWER_GOOD.
 * 
 * *************************************************************************************************** */
typedef struct BUCK_GPIO_INSTANCE_s {
    
    volatile bool enabled;      ///< Specifies, if this IO is used or not
    volatile uint16_t port;     ///< GPIO port instance number (0=Port RA, 0=Port RB, 0=Port RC, etc.)
    volatile uint16_t pin;      ///< GPIO port pin number
    volatile uint16_t polarity; ///< Output polarity, where 0=ACTIVE HIGH, 1=ACTIVE_LOW
    volatile uint16_t io_type;  ///< Input/Output definition (0=output, 1=input)

} BUCK_GPIO_INSTANCE_t; ///< GPIO instance of the converter control GPIO

/****************************************************************************************************
 * @struct BUCK_GPIO_SETTINGS_s
 * @brief Generic power converter GPIO specifications
 * 
 * <b>Description:</b><br>
 * 
 * *************************************************************************************************** */
typedef struct BUCK_GPIO_SETTINGS_s {
    
    volatile struct BUCK_GPIO_INSTANCE_s EnableInput; ///< External ENABLE input
    volatile struct BUCK_GPIO_INSTANCE_s PowerGood; ///< Power Good Output

} BUCK_GPIO_SETTINGS_t; ///< GPIO instance of the converter control GPIO

// ==============================================================================================
// BUCK converter state machine data structure and defines

// ==============================================================================================

/****************************************************************************************************
 * @struct BUCK_POWER_CONTROLLER_s
 * @brief 
 * 
 * <b>Description:</b><br>
 * 
 *****************************************************************************************************/
typedef struct BUCK_POWER_CONTROLLER_s 
{
    volatile struct BUCK_CONVERTER_STATUS_s status;     ///< BUCK operation status bits 
    volatile struct BUCK_STATE_ID_s state_id;           ///< BUCK state machine operating state ID
    volatile struct BUCK_CONVERTER_STARTUP_s startup;   ///< BUCK startup timing settings 
    volatile struct BUCK_CONVERTER_SETTINGS_s set_values;///< Control field for global access to references
    volatile struct BUCK_CONVERTER_DATA_s data;         ///< BUCK runtime data
    volatile struct BUCK_FEEDBACK_SETTINGS_s feedback;  ///< BUCK converter feedback settings

    volatile struct BUCK_SWITCH_NODE_SETTINGS_s sw_node[BUCK_MPHASE_COUNT]; ///< BUCK converter switch node settings
    volatile struct BUCK_GPIO_SETTINGS_s gpio;          ///< BUCK converter additional GPIO specification
    
    volatile struct BUCK_LOOP_SETTINGS_s v_loop;        ///< BUCK voltage control loop object
    volatile struct BUCK_LOOP_SETTINGS_s i_loop[BUCK_MPHASE_COUNT]; ///< BUCK Current control loop objects
    
} BUCK_POWER_CONTROLLER_t; ///< BUCK control & monitoring data structure

/**@}*/
/**@}*/
//#else
//    #pragma message "Warning: dev_buck_typedef.h inclusion bypassed"
#endif	/* BUCK_CONVERTER_TYPE_DEF_H */
