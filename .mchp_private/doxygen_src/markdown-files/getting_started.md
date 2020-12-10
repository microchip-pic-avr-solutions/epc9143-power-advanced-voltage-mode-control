
## Getting Started
### Introduction to the Microchip SMPS Firmware Framework Architecture

This power converter firmware is based on a set of standardized software modules, which are initialized and executed by a central, two priority level, cooperative task scheduler. The standardized building blocks (modules) are providing a framework of function building blocks (tasks) encapsulated in open-source libraries (device driver modules). These device driver modules are tailored to application-specific requirements by configuring their respective data objects (properties) and provide additional function calls (methods) for high-level control from external user code.

#### a) Task Functions: 
Each task provides the following set of standard functions:

- 



### 1. Device Startup

<p>
  <center>
    Device Startup <br>
    <img src="dot_dev-startup.svg" alt="Device Startup" width="300">
  </center>
</p>

_________________________________________________
(c) 2020, Microchip Technology Inc.

