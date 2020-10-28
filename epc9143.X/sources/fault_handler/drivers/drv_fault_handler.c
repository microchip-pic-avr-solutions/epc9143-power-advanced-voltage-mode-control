/*
 * File:   fault_handler.c
 * Author: M91406
 *
 * Created on December 27, 2019, 12:21 PM
 */


#include <xc.h>
#include <stddef.h>
#include <stdlib.h>
#include "drv_fault_handler.h"

/*!fault_check()
 *****************************************************************************
 * Function:	 uint16_t fault_check(volatile FAULT_OBJECT_t* fltobj)
 * Arguments:	 FAULT_OBJECT_t* fltobj
 * Return Value: Unsigned Integer
 *
 * Summary:
 * Check current fault status of a user-defined fault object
 *
 * Description:
 * 
 * This routine compares the most recent value of a global variable or SFR
 * (SOURCE) against user-defined thresholds. If the value violates/exceeds
 * one or more of the user defined conditions, a fault counter is incremented. 
 * 
 * When this fault counter exceeds the user-defined maximum, a fault condition 
 * is tripped and the fault_status flag bit is set.
 * 
 * When a fault condition has been tripped and the fault status is set (=true), 
 * the fault check monitors for the source value triggering a recovery event. 
 * The recovery process works like the fault trip event by comparing the most 
 * recent source value against the user-defined RESET_LEVEL. Once the value
 * has been RSTCNT_MAX times below the RESET_LEVEL threshold, the fault 
 * will automatically be cleared.
 * 
 *      Please note:
 *      If the value is within normal operating conditions, the fault 
 *      counter will be cleared. Thus fault events must occur successively 
 *      incrementing the fault event counter high enough to eventually 
 *      trip a fault event. Thus the fault event counter can be used to 
 *      adjust the sensitivity of the fault response.
 * 
 * 
 * a) Comparison Types
 * 
 * The fault handler offers the following different comparison methods:
 * 
 *      - Greater Than:
 *          performs comparison SOURCE > TRIP_LEVEL
 * 
 *          TRIP_LEVEL is greater than RESET_LEVEL. The difference between 
 *          TRIP_LEVEL and RESET_LEVEL is the hysteresis of the defined
 *          threshold.
 * 
 *      - Less Than
 *          performs comparison SOURCE < TRIP_LEVEL
 * 
 *          TRIP_LEVEL is less than RESET_LEVEL. The difference between 
 *          TRIP_LEVEL and RESET_LEVEL is the hysteresis of the defined
 *          threshold.
 *
 *      - Is Equal
 *          performs comparison SOURCE == TRIP_LEVEL
 *
 *          RESET_LEVEL is ignored.
 *
 *      - Is Not Equal
 *          performs comparison SOURCE != TRIP_LEVEL
 *
 *          RESET_LEVEL is ignored.
 *
 *      - Between
 *          performs comparison RESET_LEVEL < SOURCE < TRIP_LEVEL
 *
 *          min/max of the FAULT range is defined by the range between
 *          RESET_LEVEL (min) and TRIP_LEVEL (max)
 *
 *      - Outside
 *          performs comparison (SOURCE < RESET_LEVEL) or (TRIP_LEVEL < SOURCE)
 *
 *          min/max of the allowed operating range is defined by the range 
 *          between RESET_LEVEL (min) and TRIP_LEVEL (max)
 * 
 * b) Value Filtering
 * 
 *    A bit-mask filter can be used to monitor individual register bits or filter
 *    on specific bits within a 16-bit wide value. The bit-mask is always applied 
 *    the source value. If no bit-mask is required, set bitmask = 0xFFFF; 
 * 
 * c) Comparison of two dynamic values
 * 
 *    When dynamic values of two variables need to be compared, the fault object
 *    offers a second pointer to a so-called reference object "ref_obj". When this
 *    pointer is != NULL, the absolute value of the difference between SOURCE and 
 *    REFERNCE is compared against the user-defined TRIP and RESET thresholds.
 *    When no second  value is used, set ref_obj = NULL (NULL-pointer). This 
 *    will force the fault check to ignore this value.
 * 
 * d) User defined responses
 *    
 *    Function pointers "trip_response" and "reset_response" can be used 
 *    to assign user-defined functions which should be called when a fault
 *    condition has been tripped or reset.
 *    I no user-defined function should be called, these pointers can be 
 *    set = NULL (NULL-pointer)
 * 
 * References:
 * -
 *
 * See also:
 * -
 *****************************************************************************/


volatile uint16_t fault_check(volatile FAULT_OBJECT_t* fltobj) {

    volatile uint16_t fres=1;
    volatile uint16_t source=0;
    
    // If the fault object is not initialized, exit here with error
    if (fltobj == NULL)
        return(0);

    // If FAULT CHECK is disabled, exit here
    if (!fltobj->status.bits.enabled) {
        fltobj->counter = 0;                        // Clear Counter
        fltobj->status.bits.fault_active = false;   // Clear immediate fault flag
        fltobj->status.bits.fault_status = false;   // Clear fault status flag
        return(1);  // Return success
    }
    
    // If the source object is not initialized, exit here with error
    if (fltobj->source_obj == NULL)
        return(0);
    
    // Read most recent fault object value with bit-mask
    source = (*fltobj->source_obj & fltobj->bit_mask);
    
    if(fltobj->ref_obj != NULL) {  // If a reference object has been defined...
        source = (volatile uint16_t)abs((volatile int32_t)*fltobj->source_obj - 
                    (volatile int32_t)*fltobj->ref_obj); // Load most recent value
    }

    // Check fault condition

    switch(fltobj->status.bits.type) {

        case FLTCMP_GREATER_THAN:  // Check if SOURCE > TRIP_LEVEL
            
            if (source > fltobj->trip_level)
                fltobj->status.bits.fault_active = true; // Set FAULT_ACTIVE status flag bit
            else if (source < fltobj->reset_level)
                fltobj->status.bits.fault_active = false;   // Clear FAULT_ACTIVE status flag bit
            break;

        case FLTCMP_LESS_THAN:
            if(source < fltobj->trip_level)  // Check if SOURCE < TRIP_LEVEL
                fltobj->status.bits.fault_active = true; // Set FAULT_ACTIVE status flag bit
            else if(source > fltobj->reset_level)  // Check if SOURCE > RESET_LEVEL
                fltobj->status.bits.fault_active = false;   // Clear FAULT_ACTIVE status flag bit
            break;

        case FLTCMP_IS_EQUAL:
            if(source == fltobj->trip_level)  // Check if SOURCE == TRIP_LEVEL
                fltobj->status.bits.fault_active = true; // Set FAULT_ACTIVE status flag bit
            else if(source != fltobj->trip_level)  // Check if SOURCE != TRIP_LEVEL
                fltobj->status.bits.fault_active = false;   // Clear FAULT_ACTIVE status flag bit
            break;

        case FLTCMP_IS_NOT_EQUAL:
            if(source != fltobj->trip_level)  // Check if SOURCE != TRIP_LEVEL
                fltobj->status.bits.fault_active = true; // Set FAULT_ACTIVE status flag bit
            else if(source == fltobj->trip_level)  // Check if SOURCE == TRIP_LEVEL
                fltobj->status.bits.fault_active = false;   // Clear FAULT_ACTIVE status flag bit
            break;

        case FLTCMP_BETWEEN:
            if((fltobj->reset_level < source) && (source < fltobj->trip_level))  // Check if SOURCE is between "RESET_LEVEL ti TRIP_LEVEL"
                fltobj->status.bits.fault_active = true; // Set FAULT_ACTIVE status flag bit
            else 
                fltobj->status.bits.fault_active = false;   // Clear FAULT_ACTIVE status flag bit
            break;

        case FLTCMP_OUTSIDE:
            if((source < fltobj->reset_level) || (fltobj->trip_level < source))  // Check if SOURCE is outside "RESET_LEVEL to TRIP_LEVEL"
                fltobj->status.bits.fault_active = true; // Set FAULT_ACTIVE status flag bit
            else 
                fltobj->status.bits.fault_active = false;   // Clear FAULT_ACTIVE status flag bit
            break;

        default:
            return(0);  // Return=>Error (Ignore fault check if compare type is not defined)
            break;
    
    }
            
    // If a fault condition has been detected while no FAULT has been tripped....
    if ((fltobj->status.bits.fault_active) && (!fltobj->status.bits.fault_status)) {
    
        fltobj->counter++;  // Increment fault event counter
        
        // Trigger on FAULT conditions
        if (fltobj->counter >= fltobj->tripcnt_max)
        {
            fltobj->status.bits.fault_status = true;    // Set FAULT STATUS FLAG BIT
            fltobj->counter = fltobj->tripcnt_max;      // Set fault event counter to threshold level
            if (fltobj->trip_response != NULL)    // If a user function has been defined,
                fres = fltobj->trip_response();   // => call this function and capture return value
        }

    }
    // If a FAULT has been tripped but no fault condition has been detected anymore....
    else if ((fltobj->status.bits.fault_status) && (!fltobj->status.bits.fault_active)) {
    
        fltobj->counter++;  // Increment fault event counter

        // Trigger on RESET conditions
        if (fltobj->counter >= fltobj->rstcnt_max)
        {
            fltobj->status.bits.fault_status = false;   // Clear FAULT STATUS FLAG BIT
            fltobj->counter = fltobj->rstcnt_max;       // Set fault event counter to threshold level
            if (fltobj->reset_response != NULL)   // If a user function has been defined,
                fres = fltobj->reset_response();  // => call this function and capture return value
        }
    
    }
    // If everything is OK
    else
    {
        fltobj->counter = 0;  // clear fault event counter
    }

    
    return (fres); // Fault handler executed successfully
}
