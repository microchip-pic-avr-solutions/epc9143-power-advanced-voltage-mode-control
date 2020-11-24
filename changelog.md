# epc9143-power-advanced-voltage-mode-control, release v1.2.0

### Release Highlights
This is the initial release version of the advanced voltage mode control scheme for the EPC9143 16th brick DC/DC converter module reference design, hardware revision 4.0.

### Features Added\Updated
A single, high-speed type IV (4P4Z) voltage mode controller with enforced PWM steering is used to automatically create balanced phase currents in both phases of this interleaved converter. An underlying high-speed current balancing scheme compensates component tolerances and deviations over temperature. 
A built-in adaptive gain control algorithm stabilizes gain variations of the voltage loop controller during input- and output voltage transients, stabilizing cross-over frequency, phase & gain margin and output impedance, supporting control bandwidths of >25 kHz, for improved transient response, helping to minimize power distribution network (PDN) decoupling capacity and increasing system robustness.


