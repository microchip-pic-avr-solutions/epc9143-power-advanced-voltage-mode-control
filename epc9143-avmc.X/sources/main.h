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
 * File:   main.h
 * Author: M91406
 * Comments: main header file of this application
 * Revision history: 
 * v1.0 initial version
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APPLICATION_MAIN_HEADER_H
#define	APPLICATION_MAIN_HEADER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer data types
#include <stdbool.h> // include standard boolean data types
#include <stddef.h> // include standard definition data types

 /** 
 * @defgroup Firmware_Flow Firmware Flowchart
 * @ingroup Firmware_Flow
 * @dot
 * digraph Firmware{ 
 *      node [fontname = "Consolas, 'Courier New', Courier, Sans-Serif"];
 *      node [fontsize = 10];
 *      node [shape = box]; Power_Control_SM; State_Initialize; State_Reset; State_Standby; State_RampUp; State_Online;State_Error;    
 *		node [shape = box]; call_PCSM; call_FH; Fault_Handler;
 *		node [shape = box]; init_Osc; init_Timer; init_PSAux; enable_TMR; config_procedure_check;
 *      node [shape = box]; yes1;yes2;no1;no2;
 *      node [shape = diamond]; Success; Reset; timer_expired;
 * 
 *      graph [rankdir="TB"] {
 *     Reset [label="Reset"];
 *     subgraph cluster0 {      
 *      rank=same;      
 *		init_Osc [label="Initialize Oscillator + PLL"];
 *		init_Timer [label="Initialize Main Timer and GPIOs"];
 *		init_PSAux [label="Initialize Power supply Auxiliary Peripherals"]; 
 *		enable_TMR [label="Enable main Timer"];
 * 		config_procedure_check [label="Configuration procedure check"];
 *		Success [label="Successful?"]
 *      yes1 [label = "YES"];
 *      no1 [label = "NO"];
  *     label="Device Start-Up";
 *     }
 *     subgraph cluster1 {    
 *      rank=same; 
 *		timer_expired [label="100usec Timer expired?"];
 *      yes2 [label = "YES"];
 *      no2 [label = "NO"]; 
 *		call_PCSM [label="Call Power Control State Machine"];
 *		call_FH [label="call Fault Handler"];
  *     label="Main Loop";
 *      }
*     subgraph cluster2 {    
 *      rank=same; 
 *		Power_Control_SM [label="Power Control State Machine"];
 *      State_Initialize [label="State Initialize" URL="@ref State_Initialize"];
 *      State_Reset [label="State Reset" URL="@ref State_Reset"];
 *      State_Standby [label="State Standby" URL="@ref State_Standby"]; 
 *      State_RampUp [label="State Ramp Up" URL="@ref State_RampUp"]; 
 *      State_Online [label="State Online" URL="@ref State_Online"];
 *		State_Error [label="State Error" URL="@ref State_Error"];
 *      Fault_Handler [label="Fault Handler"];
  *     label="Task Layer";
 *      }
 *		Reset -> init_Osc -> init_Timer -> init_PSAux -> enable_TMR -> config_procedure_check -> Success -> no1 -> Reset;
 *		Success -> yes1 -> timer_expired -> no2 -> timer_expired;
 *		timer_expired -> yes2 -> call_PCSM -> call_FH -> timer_expired;
 *		call_PCSM -> Power_Control_SM -> State_Initialize->State_Reset->State_Standby->State_RampUp->State_Online;
 *		State_Error -> State_Reset;
 *		call_FH -> Fault_Handler -> State_Error;
 *     }
 * }
 * @enddot
 */

// COMMON SOFTWARE MODULES
#include "config/hal.h"
#include "config/system_initialize.h"

// APPLICATION LAYER HEADER FILES
#include "fault_handler/app_faults_monitor.h"
#include "pwr_control/app_power_control.h"

#endif	/* APPLICATION_MAIN_HEADER_H */

