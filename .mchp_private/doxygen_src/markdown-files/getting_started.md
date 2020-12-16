
## Getting Started

### Power Converter Control Firmware

Establishing a digital control system of a power supply using a programmable microcontroller requires some specific considerations to allow the high-speed real-time control loop run freely and uninterrupted despite background activity of additional functions such as communication, fault monitoring and power supply runtime supervision. 

### Introduction to the Microchip SMPS Firmware Framework Architecture

This power converter firmware is based on a set of standardized software modules, which are initialized and executed by a central, two priority level, cooperative task scheduler. The standardized building blocks (modules) are providing a framework of function building blocks (tasks) encapsulated in open-source libraries (device driver modules). These device driver modules are tailored to application-specific requirements by configuring their respective data objects (properties) and provide additional function calls (methods) for high-level control from external user code.

#### 1) Tasks: 
Each task is organized in three levels:

- Application Layer (proprietary user code)
  - User configuration of task properties
  - Interface between task device driver functions and main scheduler
  - Application specific runtime implementation of device driver functions
<br>


- Device Driver Layer
  - Generic functions and properties 
<br>
- Sub-Modules Driver Layer


#### 2) Device Startup

<p>
  <center>
    Device Startup <br>
    <img src="dot_dev-startup.svg" alt="Device Startup" width="300">
  </center>
</p>

_________________________________________________
(c) 2020, Microchip Technology Inc.

