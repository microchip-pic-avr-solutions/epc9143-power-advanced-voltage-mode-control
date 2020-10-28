![image](images/microchip.jpg) 

## EPC9143 300W 16th Brick Non-Isolated Step Down Converter Advanced Voltage Mode Control Firmware
**2-Phase Synchronous Buck Converter with Advanced Voltage Mode Control and Current Balancing**

<p>
  <center>
    <a href="https://www.microchip.com/EPC9143" rel="nofollow">
      <img src="images/9143_r4.png" alt="EPC9143 Top View" width="300">
	</a>
    <a href="https://www.microchip.com/EPC9143" rel="nofollow">
      <img src="images/9143_r4_back.png" alt="EPC9143 Top View" width="300">
	</a>
  </center>
</p>

## Summary
This code example demonstrates a closed loop voltage mode control implementation for dsPIC33CK. It has specifically been developed for the EPC9143 Rev4.0 1/16 brick converter.

The board starts up the buck converter automatically when power is applied to the board, providing a regulated output voltage of 12 V at the output of the converter. The startup procedure is controlled and executed by the power controller state machine (PWRLIB_BUCK) and includes an configurable startup procedure with power-on delay, ramp up period and power good delay before dropping into constant regulation mode.
An additional fault handler (FUNLIB_FAULT_HANDLER) shuts down the power supply if the input voltage is outside the defined range of 18V to 72.5V (UVLO/OVLO) or if the output voltage is more than 0.5V out of regulation for more than 10 milliseconds.

The control loop is based on a digital type IV compensator (4P4Z controller).

#### Product Features:
  - Input Voltage: 18 V to 61 V
  - Output Voltage: 5 V to 12.0 V (programmable)
  - Switching Frequency: 500 kHz
  - Control Frequency: 500 kHz
  - Cross-Over Frequency: ~20 kHz (depends on VIN and if AGC is on/off)
  - Phase Margin: ~ 50°

## Related Documentation
  - [EPC9143 300W 1/16th brick Power Module Reference Design Product Website](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/EPC9143)

## Software Used 
  - [MPLAB® X IDE v5.40](https://www.microchip.com/mplabx-ide-windows-installer)
  - [MPLAB® XC16 Compiler v1.60](https://www.microchip.com/mplabxc16windows)
  - [DCLD - Digital Control Library Designer v0.9.12.642](https://areiter128.github.io/DCLD/)

## Hardware Used
  - EPC9143: EPC9143 16th Brick Non-Isolated Step Down Converter, Revision 4.0
  - EPC9531: EPC9531 test fixture for EPC9143 16th brick reference design

  ![image](images/9531_test_fixture.png)

##Device Support:
  - [dsPIC33CK32MP102](https://www.microchip.com/dsPIC33CK32MP102)

## Setup


## Operation



