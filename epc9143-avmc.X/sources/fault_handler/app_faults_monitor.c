/*
 * File:   faults.c
 * Author: M91406
 *
 * Created on March 12, 2020, 11:38 AM
 */

#include <stddef.h>

#include "config/hal.h"
#include "drivers/drv_fault_handler.h"
#include "pwr_control/app_power_control.h"


// Define fault objects
volatile struct FAULT_OBJECT_s fltobj_BuckUVLO;
volatile struct FAULT_OBJECT_s fltobj_BuckOVLO;
volatile struct FAULT_OBJECT_s fltobj_BuckOCP;
volatile struct FAULT_OBJECT_s fltobj_BuckRegErr;

// Declare private function prototypes 
volatile uint16_t __attribute__((always_inline)) uvlo_FaultInitialize(void);
volatile uint16_t __attribute__((always_inline)) ovlo_FaultInitialize(void);
volatile uint16_t __attribute__((always_inline)) ocp_FaultInitialize(void);
volatile uint16_t __attribute__((always_inline)) regerr_FaultInitialize(void);

/**
 * @addtogroup fault_handler
 * @addtogroup fault_handler_function
 * @{ 
 */

/*********************************************************************************
 * @fn volatile uint16_t appFaultMonitor_Initialize(void)
 * @brief  Initialization of user-defined fault objects
 * @param (none)
 * @return unsigned integer   (0=failure, 1=success)
 * 
 * <b>Description</b>
 * 
 *********************************************************************************/

volatile uint16_t appFaultMonitor_Initialize(void) 
{
    volatile uint16_t retval=1;
    
    // Initialize user fault objects
    retval &= uvlo_FaultInitialize();
    retval &= ovlo_FaultInitialize();
    retval &= ocp_FaultInitialize();
    retval &= regerr_FaultInitialize();
    
    return(retval);
}


/*********************************************************************************
 * @fn volatile uint16_t appFaultMonitor_Dispose(void) 
 * @brief Function clearing all fault object settings
 * @param (none)
 * @return unsigned integer   (0=failure, 1=success)
 * 
 * <b>Description</b>
 *   This function is used to clear all fault objects settings. Once cleared,
 *   the fault objects are detached from memory addresses and cannot be used
 *   for fault monitoring anymore until they have been re-initialized.
 * 
 *********************************************************************************/

volatile uint16_t appFaultMonitor_Dispose(void) 
{
    fltobj_BuckUVLO = fltobjClear; // Delete Under Voltage Lock Out object
    fltobj_BuckOVLO = fltobjClear; // Delete Over Voltage Lock Out object
    fltobj_BuckRegErr = fltobjClear; // Delete Regulation Error object
    fltobj_BuckOCP = fltobjClear; // Delete Over Current Protection object
    
    return(1);
}

/*********************************************************************************
 * @fn volatile uint16_t appFaultMonitor_Execute(void)  
 * @brief Application wide fault object monitoring routine
 * @param (none)
 * @return unsigned integer   (0=failure, 1=success)
 * 
 * <b>Description</b>
 *   In this function all user-defined fault objects are monitored for 
 *   threshold violations. While fault responses are triggered by each 
 *   fault object individually, system recovery from a fault condition is 
 *   only allowed when all fault conditions have been cleared. Hence, 
 *   individual fault status bits are combined into a common fault bit, 
 *   which needs to be cleared to allow the power supply to start-up again.
 * 
 *********************************************************************************/

volatile uint16_t appFaultMonitor_Execute(void) 
{
    volatile uint16_t retval=1;
    static bool pre_fault_active=false;
    
    // Call fault handler
    retval &= drv_FaultCheck(&fltobj_BuckUVLO);
    retval &= drv_FaultCheck(&fltobj_BuckOVLO);
    retval &= drv_FaultCheck(&fltobj_BuckRegErr);
    retval &= drv_FaultCheck(&fltobj_BuckOCP);

    // Combine individual fault bits to a common fault indicator
    buck.status.bits.fault_active = (bool) (
        fltobj_BuckUVLO.Status.bits.FaultStatus | 
        fltobj_BuckOVLO.Status.bits.FaultStatus |
        fltobj_BuckRegErr.Status.bits.FaultStatus |
        fltobj_BuckOCP.Status.bits.FaultStatus 
        );
    
    // If system has recovered from a global fault condition, 
    // trigger fault recovery function
    if ((pre_fault_active) && (!buck.status.bits.fault_active))
        { retval = appPowerSupply_Resume(); }
    
    // Track global fault bit transitions
    pre_fault_active = buck.status.bits.fault_active;
    
    
    return (retval);
}


/* *********************************************************************************
 * PRIVATE FUNCTIONS
 * ********************************************************************************/


/*********************************************************************************
 * @fn volatile uint16_t uvlo_FaultInitialize(void)
 * @brief 
 * @param (none)
 * @return unsigned integer   (0=failure, 1=success)
 * 
 * <b>Description</b>
 * 
 *********************************************************************************/

volatile uint16_t uvlo_FaultInitialize(void)
{
    volatile uint16_t retval=1;
    
    // Initialize UVLO fault object
    fltobj_BuckUVLO = fltobjClear;  // Pre-initialize fault object
    
    fltobj_BuckUVLO.SourceObject.ptrObject = &buck.data.v_in;   // Set pointer to variable to monitor
    fltobj_BuckUVLO.SourceObject.bitMask = 0xFFFF;      // Compare all bits of SOURCE (no bit filter)
    fltobj_BuckUVLO.ReferenceObject.ptrObject = NULL;   // Clear pointer to "compare against" variable 
    fltobj_BuckUVLO.ReferenceObject.bitMask = 0xFFFF;   // Clear pointer to "compare against" variable 

    fltobj_BuckUVLO.Status.bits.CompareType = FLTCMP_LESS_THAN; // Select Compare-Type

    fltobj_BuckUVLO.TripResponse.compareThreshold = BUCK_VIN_UVLO_TRIP;    // Set fault trip level
    fltobj_BuckUVLO.TripResponse.eventThreshold = BUCK_UVLO_TDLY;    // Set counter level at which a FAULT condition will be tripped
    fltobj_BuckUVLO.TripResponse.ptrResponseFunction = &appPowerSupply_Suspend; // Set pointer to user-function which should be called when a FAULT is tripped

    fltobj_BuckUVLO.RecoveryResponse.compareThreshold = BUCK_VIN_UVLO_RELEASE;   // Set fault recovery level
    fltobj_BuckUVLO.RecoveryResponse.eventThreshold = BUCK_UVLO_RDLY;     // Set counter level at which a FAULT condition will be cleared
    fltobj_BuckUVLO.RecoveryResponse.ptrResponseFunction = NULL; // Clear recovery function pointer
    
    fltobj_BuckUVLO.Counter = 0; // Clear fault event counter
    fltobj_BuckUVLO.Status.bits.FaultActive = true; // Set fault condition flag (must be cleared by fault check)
    fltobj_BuckUVLO.Status.bits.FaultStatus = true; // Set fault flag (must be cleared by fault check)
    fltobj_BuckUVLO.Status.bits.Enabled = true; // Enable fault checks
    
    return(retval);
    
}

/*********************************************************************************
 * @fn volatile uint16_t ovlo_FaultInitialize(void)
 * @brief 
 * @param (none)
 * @return unsigned integer   (0=failure, 1=success)
 * 
 * <b>Description</b>
 * 
 *********************************************************************************/

volatile uint16_t ovlo_FaultInitialize(void)
{
    volatile uint16_t retval=1;

    // Initialize OVLO fault object
    fltobj_BuckOVLO = fltobjClear;  // Pre-initialize fault object

    fltobj_BuckOVLO.SourceObject.ptrObject = &buck.data.v_in;   // Set pointer to variable to monitor
    fltobj_BuckOVLO.SourceObject.bitMask = 0xFFFF;    // Compare all bits of SOURCE (no bit filter)
    fltobj_BuckOVLO.ReferenceObject.ptrObject = NULL; // Clear pointer to "compare against" variable 
    fltobj_BuckOVLO.ReferenceObject.bitMask = 0xFFFF; // Compare all bits of SOURCE (no bit filter)
    fltobj_BuckOVLO.Status.bits.CompareType = FLTCMP_GREATER_THAN; // Select Compare-Type

    fltobj_BuckOVLO.TripResponse.compareThreshold = BUCK_VIN_OVLO_TRIP;    // Set fault trip level
    fltobj_BuckOVLO.TripResponse.eventThreshold = BUCK_OVLO_TDLY;    // Set counter level at which a FAULT condition will be tripped
    fltobj_BuckOVLO.TripResponse.ptrResponseFunction = &appPowerSupply_Suspend; // Set pointer to user-function which should be called when a FAULT is tripped

    fltobj_BuckOVLO.RecoveryResponse.compareThreshold = BUCK_VIN_OVLO_RELEASE;   // Set fault recovery level
    fltobj_BuckOVLO.RecoveryResponse.eventThreshold = BUCK_OVLO_RDLY; // Set counter level at which a FAULT condition will be cleared
    fltobj_BuckOVLO.RecoveryResponse.ptrResponseFunction = NULL; // Clear recovery function pointer
    
    fltobj_BuckOVLO.Counter = 0;        // Clear fault event counter
    fltobj_BuckOVLO.Status.bits.FaultActive = true; // Set fault condition flag (must be cleared by fault check)
    fltobj_BuckOVLO.Status.bits.FaultStatus = true; // Set fault flag (must be cleared by fault check)
    fltobj_BuckOVLO.Status.bits.Enabled = true; // Enable fault checks
            
    return(retval);
    
}
    
/*********************************************************************************
 * @fn volatile uint16_t regerr_FaultInitialize(void)
 * @brief 
 * @param (none)
 * @return unsigned integer   (0=failure, 1=success)
 * 
 * <b>Description</b>
 * 
 *********************************************************************************/
volatile uint16_t regerr_FaultInitialize(void)
{
    volatile uint16_t retval=1;

    // Initialize regulation error fault object
    fltobj_BuckRegErr = fltobjClear;  // Pre-initialize fault object

    fltobj_BuckRegErr.SourceObject.ptrObject = &buck.data.v_out; // Set pointer to variable to monitor
    fltobj_BuckRegErr.SourceObject.bitMask = 0xFFFF; // Compare all bits of SOURCE (no bit filter)
    fltobj_BuckRegErr.ReferenceObject.ptrObject = &buck.set_values.v_ref; // Set pointer to "compare against" variable 
    fltobj_BuckRegErr.ReferenceObject.bitMask = 0xFFFF; // Compare all bits of Reference (no bit filter)
    fltobj_BuckRegErr.Status.bits.CompareType = FLTCMP_GREATER_THAN; // Select Compare-Type

    fltobj_BuckRegErr.TripResponse.compareThreshold = BUCK_VOUT_DEV_TRIP;    // Set fault trip level
    fltobj_BuckRegErr.TripResponse.eventThreshold = BUCK_REGERR_TDLY; // Set counter level at which a FAULT condition will be tripped
    fltobj_BuckRegErr.TripResponse.ptrResponseFunction = &appPowerSupply_Suspend; // Set pointer to user-function which should be called when a FAULT is tripped

    fltobj_BuckRegErr.RecoveryResponse.compareThreshold = BUCK_VOUT_DEV_RELEASE;   // Set fault recovery level
    fltobj_BuckRegErr.RecoveryResponse.eventThreshold = BUCK_REGERR_RDLY; // Set counter level at which a FAULT condition will be cleared
    fltobj_BuckRegErr.RecoveryResponse.ptrResponseFunction = NULL; // Clear recovery function pointer
    
    fltobj_BuckRegErr.Counter = 0;        // Clear fault event counter
    fltobj_BuckRegErr.Status.bits.FaultActive = false; // Set fault condition flag (must be cleared by fault check)
    fltobj_BuckRegErr.Status.bits.FaultStatus = false; // Set fault flag (must be cleared by fault check)
    fltobj_BuckRegErr.Status.bits.Enabled = false; // Disable fault checks at startup
    
    return(retval);
    
}
    
/*********************************************************************************
 * @fn volatile uint16_t ocp_FaultInitialize(void)
 * @brief 
 * @param (none)
 * @return unsigned integer   (0=failure, 1=success)
 * 
 * <b>Description</b>
 * 
 *********************************************************************************/
volatile uint16_t ocp_FaultInitialize(void)
{
    volatile uint16_t retval=1;

    // Initialize OCP fault object
    fltobj_BuckOCP = fltobjClear;  // Pre-initialize fault object

    fltobj_BuckOCP.SourceObject.ptrObject = &buck.data.i_out;   // Set pointer to variable to monitor
    fltobj_BuckOCP.SourceObject.bitMask = 0xFFFF;  // Compare all bits of SOURCE (no bit filter)
    fltobj_BuckOCP.ReferenceObject.ptrObject = NULL;  // Clear pointer to "compare against" variable 
    fltobj_BuckOCP.ReferenceObject.bitMask = 0xFFFF;  // Compare all bits of SOURCE (no bit filter)
    fltobj_BuckOCP.Status.bits.CompareType = FLTCMP_GREATER_THAN; // Select Compare-Type

    fltobj_BuckOCP.TripResponse.compareThreshold = BUCK_ISNS_OCL;    // Set fault trip level
    fltobj_BuckOCP.TripResponse.eventThreshold = BUCK_OCP_TDLY;    // Set counter level at which a FAULT condition will be tripped
    fltobj_BuckOCP.TripResponse.ptrResponseFunction = &appPowerSupply_Suspend; // Set pointer to user-function which should be called when a FAULT is tripped

    fltobj_BuckOCP.RecoveryResponse.compareThreshold = BUCK_ISNS_OCL_RELEASE;   // Set fault recovery level
    fltobj_BuckOCP.RecoveryResponse.eventThreshold = BUCK_OCP_RDLY;     // Set counter level at which a FAULT condition will be cleared
    fltobj_BuckOCP.RecoveryResponse.ptrResponseFunction = NULL; // Clear recovery function pointer
    
    fltobj_BuckOCP.Counter = 0;        // Clear fault event counter
    fltobj_BuckOCP.Status.bits.FaultActive = true; // Set fault condition flag (must be cleared by fault check)
    fltobj_BuckOCP.Status.bits.FaultStatus = true; // Set fault flag (must be cleared by fault check)
    fltobj_BuckOCP.Status.bits.Enabled = true; // Enable fault checks    

    return(retval);
    
}
/**@}*/    
// END OF FILE
