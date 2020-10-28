# Fault Handler Function Driver
## Generic fault handler supporting comparison of static and dynamic data with automated fault trip and release function

**Description**
This generic fault handler driver declares a fault object data structure, which can be used in user code to create various different fault objects, which will get scanned and managed by the fault handler functions.
The main function of this fault handler is restricted to detecting fault conditions, differentiating between trip and release conditions. Fault conditions are defined in user code individually for each fault object.

**Fault Object Types:**

* One 16-bit wide SFR or user variable compared against 16-bit wide constant
* One 16-bit wide SFR or user variable against another 16-bit wide SFR or user variable 
* Each variable is/can be supported by bit masks

**Compare Functions:**

* Greater Than
* Less Than
* Equal
* Not Equal
* Between Thresholds
* Outside Thresholds

**Fault Indication/Fault Response:**

* Immediate indication of fault condition through status bit in fault object status word (set/cleared when change in fault condition is detected)
* Immediate indication of fault status through status bit in fault object status word (set/cleared when fault trips/resets)
* Automatic trigger of user-defined software function when a fault condition trips
* Automatic trigger of user-defined software function when a fault condition is released

**Integration Template and Test Container:**
* Function and code integration can be reviewed in [code example CE200](https://bitbucket.microchip.com/projects/MCU16ASMPSCE/repos/p33c_ce200/browse).

**History:**
* 03/13/2020 v1.0 Initial release by M91406

