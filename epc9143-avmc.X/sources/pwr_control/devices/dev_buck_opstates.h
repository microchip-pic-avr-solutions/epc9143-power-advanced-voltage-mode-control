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
 *  @file    dev_buck_opstates.h
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
 * File:   dev_buck_opstates.h
 * Author: M91406
 * Comments: Buck converter operation states header file
 * Revision history: 
 *   10/09/20   1.0  initial version
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BUCK_CONVERTER_OPERATION_STATES_H
#define	BUCK_CONVERTER_OPERATION_STATES_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types

// Buck converter state machine function pointer array
extern volatile uint16_t (*BuckConverterStateMachine[])
            (volatile struct BUCK_POWER_CONTROLLER_s *buckInstance);

// Buck converter state machine function pointer array size
extern volatile uint16_t BuckStateList_size;


#endif	/* BUCK_CONVERTER_OPERATION_STATES_H */


/** 
 * @file dev_buck_opstates.c
 * @brief Functions of the buck converter state machine operating states
 * @addtogroup buck-state-machine 
 * @dot
 * digraph State_Machine  
 * {
 *      node [fontname="Consolas, 'Courier New', Courier, Sans-Serif", fontsize=10];
 * 
 *      efs_clear [shape=invhouse, label="Enabled, Fault- and Suspend Flag cleared?"];
 *      conv_run  [shape=invhouse, label="Converter Running?"];
 *
 *      en_pin    [shape=diamond, label="Enable pin set? (optional)", URL="@ref BUCK_GPIO_SETTINGS_s"];
 *      en_set    [shape=diamond, label="Enable bit set?", URL="@ref BUCK_CONVERTER_STATUS_s"];
 *      flt_clear [shape=diamond, label="Fault Flag cleared?", URL="@ref BUCK_CONVERTER_STATUS_s"];
 *      sf_clear  [shape=diamond, label="Suspend Flag cleared?", URL="@ref BUCK_CONVERTER_STATUS_s"];
 *
 *      yes1 [shape=invtriangle, label="YES"];
 *      no1  [shape=invtriangle, label="NO"];
 *      yes2 [shape=invtriangle, label="YES"];
 *      no2  [shape=invtriangle, label="NO"];
 *      exit [shape=cds, label="Exit"];
 *
 *      PreState_Initialize [shape=box, label="State Initialize", URL="@ref State_Initialize"];
 *      PreState_Reset      [shape=box, label="State Reset", URL="@ref State_Reset"];
 * 
 *      State_Reset   [shape=box, label="State Reset",  URL="@ref State_Reset"];
 *      State_Standby [shape=box, label="State Standby", URL="@ref State_Standby"]; 
 *      State_RampUp  [shape=box, label="State Ramp Up", URL="@ref State_RampUp"]; 
 *      State_Online  [shape=box, label="State Online", URL="@ref State_Online"];
 *
 *      SubState_PowerOnDelay   [shape=ellipse, label="Power On Delay", URL="@ref SubState_PowerOnDelay"];
 *      SubState_PrepareVRampUp [shape=ellipse, label="Prepare Voltage Ramp Up", URL="@ref SubState_PrepareVRampUp"];
 *      SubState_VRampUp        [shape=ellipse, label="Voltage Ramp Up", URL="@ref SubState_VRampUp"]; 
 *      SubState_IRampUp        [shape=ellipse, label="Current Ramp Up", URL="@ref SubState_IRampUp"]; 
 *      SubState_PowerGoodDelay [shape=ellipse, label="Power Good Delay", URL="@ref SubState_PowerGoodDelay"];
 *
 *      en_pin->en_set->efs_clear;
 *      flt_clear -> efs_clear;
 *      sf_clear -> efs_clear;
 *      efs_clear -> no1 -> conv_run -> no2 -> PreState_Initialize -> exit;
 *      conv_run -> yes2 -> PreState_Reset-> exit;
 *      efs_clear -> yes1 -> State_Reset;
 * 
 *      State_Reset -> State_Standby -> State_RampUp;
 *      State_RampUp -> SubState_PowerOnDelay -> SubState_PrepareVRampUp -> SubState_VRampUp ->
 *          SubState_IRampUp -> SubState_PowerGoodDelay -> State_Online;
 * 
 * }
 * @enddot
 */

// END OF FILE
