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
 *  @file    app_power_control.h
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
 * File:   app_power_control.h
 * Author: M91406
 * Comments: Power control application layer
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APPLICATION_LAYER_POWER_CONTROL_H
#define	APPLICATION_LAYER_POWER_CONTROL_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

#include "devices/dev_buck_typedef.h"    // include buck converter object declarations
#include "pwr_control/drivers/npnz16b.h" // include NPNZ control loop object declarations


/**************************************************************************************************
 * @var volatile struct BUCK_POWER_CONTROLLER_s buck
 * @brief Global data object for the BUCK CONVERTER 
 * 
 * <b>Description:</b><br>
 * the 'buck' data object holds all status, control and monitoring values of the BUCK power 
 * controller. The BUCK_POWER_CONTROLLER_t data structure is defined in drv_buck_typedef.h.
 * Please refer to the comments on top of this file for further information.
 *  
 * *************************************************************************************************/
extern volatile struct BUCK_POWER_CONTROLLER_s buck;

// PUBLIC FUNCTION PROTOTYPE DECLARATION
extern volatile uint16_t appPowerSupply_Initialize(void);
extern volatile uint16_t appPowerSupply_Dispose(void);
extern volatile uint16_t appPowerSupply_Execute(void);
extern volatile uint16_t appPowerSupply_Start(void);
extern volatile uint16_t appPowerSupply_Stop(void);
extern volatile uint16_t appPowerSupply_Suspend(void);
extern volatile uint16_t appPowerSupply_Resume(void);

#else
  #pragma message "app_power_control.h inclusion bypassed"
#endif	/* APPLICATION_LAYER_POWER_CONTROL_H */

