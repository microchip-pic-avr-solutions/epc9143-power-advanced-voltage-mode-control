# epc9143-power-advanced-voltage-mode-control, release v2.2.0

### Features Added\Updated
In this release the buck converter device driver was upgraded supporting the following new features:

- Average Current Mode Control Startup Current LImit
- Improved integration of Dynamic Over Current Protection Management
- Support for Synchronous and Asynchronous operation

The changes introduced by the buck converter device driver upgrade do not affect this firmware. The modified and extended features have been upgraded to support users who want to migrate/change the control loop of this firmware to average current mode control.

### Bugfixes

- Current Sense Calibration
the averaging procedure of the current sense feedback offset compensation averaged over a data array which was one step too short. Hence the produced result was slightly lower than the real signal offset value resulting in a less effective offset compensation.
- Operational Amplifier Configuration 
this bug caused previously configured op-amp instances to be reset when a new instant was initialized. This bug did not affect the previous version of this firmware but may corrupt firmware where users may want to configure a second instance.

### Documentation Update
The online documentation provided with this firmware was updated to account for the changes mentioned above. In addition, in this version also introduced additional chapters about the controller implementation and more detailed documentation of the NPNZ controller object classes used as feedback loop controllers.


# epc9143-power-advanced-voltage-mode-control, release v2.1.0

### Release Highlights
This release version is based on the original Advanced Voltage Mode Control scheme for the EPC9143 16th brick DC/DC converter power module reference design, hardware revision 4.0. With version 2.0 the state machine has been optimized and extended. Especially the converter startup has been made more robust and fault handling has been enhanced. With version 2.1 online documentation of the firmware has been added, which is now available as Github Pages:

[EPC9143 Online Firmware Documentation](https://microchip-pic-avr-examples.github.io/epc9143-power-advanced-voltage-mode-control)

### Features Added\Updated
A single, high-speed type IV (4P4Z) voltage mode controller with enforced PWM steering is used to automatically create balanced phase currents in both phases of this interleaved converter. An underlying high-speed current balancing scheme compensates component tolerances and deviations over temperature. 
A built-in adaptive gain control algorithm stabilizes gain variations of the voltage loop controller during input- and output voltage transients, stabilizing cross-over frequency, phase & gain margin and output impedance, supporting control bandwidths of >25 kHz, for improved transient response, helping to minimize power distribution network (PDN) decoupling capacity and increasing system robustness.

### Please Note
This is the first release version published on Github. Previous firmware versions 1.0.0 through 1.3.x as well as version 2.0.x were only available as ZIP archive on the EPC9143 product website on [microchip.com](https://www.microchip.com/epc9143) and are not covered by this repository.

