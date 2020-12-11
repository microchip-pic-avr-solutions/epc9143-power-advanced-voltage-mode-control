# epc9143-power-advanced-voltage-mode-control, release v2.1.0

### Release Highlights
Version 2.1 is based on the original Advanced Voltage Mode Control scheme for the EPC9143 16th brick DC/DC converter power module reference design, hardware revision 4.0. With version 2.0 the state machine has been optimized and extended. Especially the converter startup has been made more robust and fault handling has been enhanced. With version 2.1 online documentation of the firmware has been added, which is now available as Github Pages:

[EPC9143 Online Firmware Documentation](https://microchip-pic-avr-examples.github.io/epc9143-power-advanced-voltage-mode-control)

### Features Added\Updated
A single, high-speed type IV (4P4Z) voltage mode controller with enforced PWM steering is used to automatically create balanced phase currents in both phases of this interleaved converter. An underlying high-speed current balancing scheme compensates component tolerances and deviations over temperature. 
A built-in adaptive gain control algorithm stabilizes gain variations of the voltage loop controller during input- and output voltage transients, stabilizing cross-over frequency, phase & gain margin and output impedance, supporting control bandwidths of >25 kHz, for improved transient response, helping to minimize power distribution network (PDN) decoupling capacity and increasing system robustness.

### Please Note
This is the first release version published on Github. Previous firmware versions 1.0 through 1.3 as well as version 2.0 were only available as ZIP archive on the EPC9143 product website on [microchip.com](https://www.microchip.com/epc9143) and are not covered by this repository.

Please contact [Microchip Technology Digital Power Support](mailto:mcu16support@microchip.com) if you are looking for previous firmware versions for this design.


