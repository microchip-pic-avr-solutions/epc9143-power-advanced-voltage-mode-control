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

/** 
 * @file dev_buck_opstates.c
 * @brief Functions of the buck converter state machine operating states
 * @defgroup buck_state_machine Buck Converter State Machine 
 * @dot
 * digraph State_Machine{ 
 *      node [fontname = "Consolas, 'Courier New', Courier, Sans-Serif"];
 *      node [fontsize = 10];
 *      node [shape = box]; State_Initialize; State_Reset; State_Standby; State_RampUp; State_Online;    
 *      node [shape = box]; yes1; no1; yes2; no2;
 *      node [shape = diamond]; e_f; c_r;
 *      yes1 [label = "YES"];
 *      no1 [label = "NO"];
 *      yes2 [label = "YES"];
 *      no2 [label = "NO"];
 *      
 *      State_Initialize [label="State Initialize" URL="@ref State_Initialize"];
 *      State_Reset [label="State Reset" URL="@ref State_Reset"];
 *      State_Standby [label="State Standby" URL="@ref State_Standby"]; 
 *      State_RampUp [label="State Ramp Up" URL="@ref State_RampUp"]; 
 *      State_Online [label="State Online" URL="@ref State_Online"];
 * 
 *      e_f [label = "Enabled and Fault cleared?"];
 *      c_r [label = "Converter Running?"];
 *      e_f -> no1 -> c_r -> no2 -> State_Initialize;
 *      c_r -> yes2 -> State_Reset;
 *      e_f -> yes1 -> State_Initialize;
 *      State_Initialize->State_Reset->State_Standby->State_RampUp->State_Online;
 * }
 * @enddot
 * 
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

// END OF FILE
