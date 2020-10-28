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
 * File:   dev_buck_converter.h
 * Author: M91406
 * Comments: power controller functions for buck converter
 * Revision history: 
 * 1.0  initial version
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BUCK_CONVERTER_STATE_MACHINE_H
#define	BUCK_CONVERTER_STATE_MACHINE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types


// ==============================================================================================
// BUCK converter public function prototypes
// ==============================================================================================

// POWER CONVERTER FUNCTION API

//extern volatile uint16_t drv_BuckConverter_Initialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t drv_BuckConverter_Execute(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t drv_BuckConverter_Start(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t drv_BuckConverter_Stop(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t drv_BuckConverter_Suspend(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t drv_BuckConverter_Resume(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);

// POWER CONVERTER PERIPHERAL CONFIGURATION ROUTINES
    
extern volatile uint16_t buckPWM_ModuleInitialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);

extern volatile uint16_t buckPWM_VMC_Initialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t buckPWM_Start(volatile uint16_t pwmInstance);
extern volatile uint16_t buckPWM_Stop(volatile uint16_t pwmInstance);
extern volatile uint16_t buckPWM_Suspend(volatile uint16_t pwmInstance);
extern volatile uint16_t buckPWM_Resume(volatile uint16_t pwmInstance);

extern volatile uint16_t buckADC_ModuleInitialize(void);
extern volatile uint16_t buckADC_Channel_Initialize(volatile struct BUCK_ADC_INPUT_SETTINGS_s* adcInstance);
extern volatile uint16_t buckADC_Start(void);
    
extern volatile uint16_t buckGPIO_Initialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance);
extern volatile uint16_t buckGPIO_Set(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance);
extern volatile uint16_t buckGPIO_Clear(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance);
extern volatile bool buckGPIO_GetPinState(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* BUCK_CONVERTER_STATE_MACHINE_H */

