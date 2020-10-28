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
 * File:   fault_handler.h
 * Author: M91406
 * Comments: Global, generic fault handler header file
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef FAULT_HANDLER_H
#define	FAULT_HANDLER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer types 
#include <stdbool.h> // include standard boolean types  
#include <stddef.h> // include standard definitions  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum {
	FLTCMP_NONE				= 0, // No comparison type has been defined (fault object will be ignored)
	FLTCMP_GREATER_THAN		= 1, // Check for condition: SOURCE > trip level
	FLTCMP_LESS_THAN		= 2, // Check for condition: SOURCE < trip level
	FLTCMP_IS_EQUAL			= 3, // Check for condition: SOURCE = trip level
	FLTCMP_IS_NOT_EQUAL		= 4, // Check for condition: SOURCE != trip level
	FLTCMP_BETWEEN			= 5, // Check for condition: (reset_level < SOURCE) && (SOURCE < trip_level)
	FLTCMP_OUTSIDE			= 6  // Check for condition: (SOURCE < reset_level) || (trip_level < SOURCE)
} FLT_COMPARE_TYPE_e;

typedef union{

	struct {
		volatile bool fault_status : 1;         // Bit 0: Flag bit indicating if FAULT has been tripped
		volatile bool fault_active : 1;         // Bit 1: Flag bit indicating if fault condition has benn detected but FAULT has not been tripped yet
		volatile unsigned : 6;					// Bit <7:2>: (reserved)
		volatile FLT_COMPARE_TYPE_e type: 3;	// Bit <10:8>: Fault check comparison type control bits
		volatile unsigned : 4;					// Bit 14: (reserved)
		volatile bool enabled : 1;              // Bit 15: Control bit enabling/disabling monitoring of the fault object
	} __attribute__((packed)) bits; // Fault object status bit field for signle bit access  

	volatile uint16_t value;		// Fault object status word  

} FLT_OBJECT_STATUS_t;	// Fault object status

typedef struct {
	volatile FLT_OBJECT_STATUS_t status; // Status word of this fault object
	volatile uint16_t* source_obj;	// Pointer to variable or SFR to be monitored 
	volatile uint16_t* ref_obj;     // Pointer to variable or SFR defining the threshold
    volatile uint16_t (*trip_response)(void); // pointer to a user function called when a defined fault condition is detected
    volatile uint16_t (*reset_response)(void); // pointer to a user function called when a defined fault condition is cleared
	volatile uint16_t bit_mask;		// Bit mask will be &-ed with source as value (use 0xFFFF for full value comparison)
	volatile uint16_t counter;		// Fault event counter (controlled by FAULT HANDLER)
	volatile uint16_t trip_level;	// Signal level at which the fault condition will be detected
	volatile uint16_t tripcnt_max;	// Counter value at/above which the fault condition will be triggered 
	volatile uint16_t reset_level;	// Signal level at which the fault condition will be cleared
	volatile uint16_t rstcnt_max;	// Counter value at/above which the fault condition will be triggered 
} FAULT_OBJECT_t;


// Public Function Prototypes
extern volatile uint16_t fault_check(volatile FAULT_OBJECT_t* fltobj);
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* FAULT_HANDLER_H */

