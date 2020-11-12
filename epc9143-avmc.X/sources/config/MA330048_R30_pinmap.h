/* ***********************************************************************************************
 * File:           ma330048_p33ck_r30_pinmap.h 
 * Author:         M91406                                                                     
 * Comments:       Hardware abstraction layer device pinout descriptor                            
 * Board ID:       DPPIM_P33CK                                                                  
 * Product-No:     MA330048                                                               
 * Device ID:      P33CK                                                                    
 * Board Revision: 30                                                                  
 * Date:           05/15/2020                                                                         
 * Build:          0058                                                                   
 * Build Tool:     1.3                                                                            
 *                                                                                                 
 * Description:                                                                                    
 * This is a header file template adding signal labels for the hardware abstraction layer          
 * In this example user defined signals are directly associated to specific device pins.           
 * These associations have been created using the MS Excel macro-based code generation tool        
 * MyBoard_RXX_pinout.xlsm located in the h/hal/config directory of the project.                   
 *                                                                                                 
 * Note:                                                                                           
 * This file is the junction point between hardware and microcontroller abstraction layer.         
 * To better separate them from each other (e.g. for supporting CPU cards in hardware platforms),  
 * generic signal labels may be used in these declarations, which can be used to associate MCU     
 * device pins in MCAL to signals defined in HAL.                                                  
 *                                                                                     
 * EXAMPLE OF BOTH USE CASES                                                           
 *                                                                                     
 * a) Direct pin assignment using ONE header file in HAL                               
 *                                                                                     
 *  File:       MyBoard_RXX_pinmap.h                                                   
 * -----------------------------------------------------------------------             
 *                                                                                     
 *              #define CLKOUT  _LATB1                                                 
 *                                                                                     
 * Any usage of the label CLKOUT in user code will automatically be mapped to the      
 * specific device pin RB1. Thus board hardware and MCU itself become independent,     
 * exchangeable elements in the firmware and pin-out changes made won't affect         
 * the rest of the firmware.                                                           
 *                                                                                     
 * However, although this assignment simplifies the hardware abstraction, HAL and MCAL 
 * are not clearly separated as MCU specific registers are assigned here.              
 *                                                                                     
 *                                                                                     
 * b) Indirect pin assignment using TWO header files in HAL and MCAL                   
 *          
 *  File:       MyBoard_RXX_pinmap.h            MyController_pinmap.h                  
 * -----------------------------------------------------------------------             
 *          
 *              #define CLKOUT  ECP08            #define TP08    _LATB1                
 *     
 * Any usage of the label CLKOUT in user code will automatically be mapped to the          
 * specific device pin RB1. Thus board hardware, MCU adapter card and MCU itself become    
 * independent, exchangeable elements in the firmware and changes made here won't affect   
 * the rest of the firmware.                                                           
 *                                                                                     
 * This functional assignment scheme clearly separates HAL and MCAL, but adds more complexity  
 * to the structure. This scheme works best when working with CPU adapter cards like   
 * Microchip's Digital Power Plug-In Modules.                                          
 *                                                                                     
 *                                                                                     
 * ***********************************************************************************************/    
// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef __MA330048_P33CK_R30_PINMAP_H__
#define __MA330048_P33CK_R30_PINMAP_H__

#include <xc.h> // include processor files - each processor file is guarded 
#include <stdint.h> // Include standard integer types                       
#include <stdbool.h> // Include standard boolean types                      
#include <stddef.h> // Include standard definition types                    

/* @@Hardware Identifiers
* *************************************************************************************************
 * Summary:
 * Global defines of hardware identifiers
 *
 * Description:
 * This section is used to define hardware specific identifiers which can be used in user firmware
 * to tailor and switch between different versions of a certain hardware. The identifiers provided
 * are using the product number and a board name flag together with the hardware version number.
 *
 * In addition a macro is defined helping to identify the hardware revision as integer number,
 * allowing to use this macro in ´compare statements like
 *
 *   #if (__MA330048_VERSION > 10)
 *     #pragma message 'Warning: This code has not been tested for the selected hardware'
 *   #endif
 *
 * *************************************************************************************************/

#ifndef __MA330048_R30 // hardware indentifier macro using the product number
#define __MA330048_R30 // hardware version is encoded by R<MAJOR><MINOR> (e.g. revision 2.1 = R21)
#endif

#ifndef __MA330048_VERSION // hardware version as integer number
#define __MA330048_VERSION 30 // is encoded by <MAJOR><MINOR> (e.g. revision 2.1 = R21)
#endif


/* ***********************************************************************************************/

// Generated Content: Generic defines used to map device pins to board signals
#ifndef PINDIR_INPUT
    #define PINDIR_INPUT 1
#endif
#ifndef PINDIR_OUTPUT
    #define PINDIR_OUTPUT 0
#endif

#ifndef PINSTATE_HIGH
    #define PINSTATE_HIGH 1
#endif
#ifndef PINSTATE_LOW
    #define PINSTATE_LOW 0
#endif

#ifndef PINCFG_OPEN_DRAIN
    #define PINCFG_OPEN_DRAIN 1
#endif
#ifndef PINCFG_PUSH_PULL
    #define PINCFG_PUSH_PULL 0
#endif

#ifndef LED_ON
    #define LED_ON 0
#endif
#ifndef LED_OFF
    #define LED_OFF 1
#endif


// Common PPS Labels		
#define RPOR_U1TX     	0b000001	// RPn tied to UART1 Transmit
#define RPOR_U1RTS    	0b000010	// RPn tied to UART1 Request-to-Send
#define RPOR_U2TX     	0b000011	// RPn tied to UART2 Transmit
#define RPOR_U2RTS    	0b000100	// RPn tied to UART2 Request-to-Send
#define RPOR_U3TX     	0b011011	// RPn tied to UART3 Transmit
#define RPOR_U3RTS    	0b011100	// RPn tied to UART3 Request-to-Send
#define RPOR_SDO1     	0b000101	// RPn tied to SPI1 Data Output
#define RPOR_SCK1     	0b000110	// RPn tied to SPI1 Clock Output
#define RPOR_SS1      	0b000111	// RPn tied to SPI1 Slave Select
#define RPOR_SDO2     	0b001000	// RPn tied to SPI2 Data Output
#define RPOR_SCK2     	0b001001	// RPn tied to SPI2 Clock Output
#define RPOR_SS2      	0b001010	// RPn tied to SPI2 Slave Select
#define RPOR_SDO3     	0b001011	// RPn tied to SPI3 Data Output
#define RPOR_SCK3     	0b001100	// RPn tied to SPI3 Clock Output
#define RPOR_SS3      	0b001101	// RPn tied to SPI3 Slave Select
#define RPOR_REFCLKO  	0b001110	// RPn tied to Reference Clock Output
#define RPOR_OCM1     	0b001111	// RPn tied to SCCP1 Output
#define RPOR_OCM2     	0b010000	// RPn tied to SCCP2 Output
#define RPOR_OCM3     	0b010001	// RPn tied to SCCP3 Output
#define RPOR_OCM4     	0b010010	// RPn tied to SCCP4 Output
#define RPOR_OCM5     	0b010011	// RPn tied to SCCP5 Output
#define RPOR_OCM6     	0b010100	// RPn tied to SCCP6 Output
#define RPOR_CAN1TX   	0b010101	// RPn tied to CAN1 Transmit
#define RPOR_CMP1     	0b010111	// RPn tied to Comparator 1 Output
#define RPOR_CMP2     	0b011000	// RPn tied to Comparator 2 Output
#define RPOR_CMP3     	0b011001	// RPn tied to Comparator 3 Output
#define RPOR_PWM4H    	0b100010	// RPn tied to PWM4H Output
#define RPOR_PWM4L    	0b100011	// RPn tied to PWM4L Output
#define RPOR_PWMEA    	0b100100	// RPn tied to PWM Event A Output
#define RPOR_PWMEB    	0b100101	// RPn tied to PWM Event B Output
#define RPOR_QEICMP1  	0b100110	// RPn tied to QEI1 Comparator Output
#define RPOR_QEICMP2  	0b100111	// RPn tied to QEI2 Comparator Output
#define RPOR_CLC1OUT  	0b101000	// RPn tied to CLC1 Output
#define RPOR_CLC2OUT  	0b101001	// RPn tied to CLC2 Output
#define RPOR_OCM7     	0b101010	// RPn tied to SCCP7 Output
#define RPOR_OCM8     	0b101011	// RPn tied to SCCP8 Output
#define RPOR_PWMEC    	0b101100	// RPn tied to PWM Event C Output
#define RPOR_PWMED    	0b101101	// RPn tied to PWM Event D Output
#define RPOR_PTGTRG24 	0b101110	// PTG Trigger Output 24
#define RPOR_PTGTRG25 	0b101111	// PTG Trigger Output 25
#define RPOR_SENT1OUT 	0b110000	// RPn tied to SENT1 Output
#define RPOR_SENT2OUT 	0b110001	// RPn tied to SENT2 Output
#define RPOR_MCCP9A   	0b110010	// RPn tied to MCCP9 Output A
#define RPOR_MCCP9B   	0b110011	// RPn tied to MCCP9 Output B
#define RPOR_MCCP9C   	0b110100	// RPn tied to MCCP9 Output C
#define RPOR_MCCP9D   	0b110101	// RPn tied to MCCP9 Output D
#define RPOR_MCCP9E   	0b110110	// RPn tied to MCCP9 Output E
#define RPOR_MCCP9F   	0b110111	// RPn tied to MCCP9 Output F
#define RPOR_CLC3OUT  	0b111011	// RPn tied to CLC4 Output
#define RPOR_CLC4OUT  	0b111100	// RPn tied to CLC4 Output
#define RPOR_U1DTR    	0b111101	// RPn tied to UART1 DTR
#define RPOR_U2DTR    	0b111110	// RPn tied to UART2 DTR
#define RPOR_U3DTR    	0b111111	// RPn tied to UART3 DTR

// Common ADC Trigger Source Labels		
#define TRGSRC_ADTRIG31 	0b11111	// ADTRG31 (PPS input)
#define TRGSRC_PTG      	0b11110	// PTG
#define TRGSRC_CLC2     	0b11101	// CLC2
#define TRGSRC_CLC1     	0b11100	// CLC1
#define TRGSRC_MCCP9    	0b11011	// MCCP9
#define TRGSRC_SCCP7    	0b11010	// SCCP7
#define TRGSRC_SCCP6    	0b11001	// SCCP6
#define TRGSRC_SCCP5    	0b11000	// SCCP5
#define TRGSRC_SCCP4    	0b10111	// SCCP4
#define TRGSRC_SCCP3    	0b10110	// SCCP3
#define TRGSRC_SCCP2    	0b10101	// SCCP2
#define TRGSRC_SCCP1    	0b10100	// SCCP1
#define TRGSRC_PWM8_TRG2	0b10011	// PWM8 Trigger 2
#define TRGSRC_PWM8_TRG1	0b10010	// PWM8 Trigger 1
#define TRGSRC_PWM7_TRG2	0b10001	// PWM7 Trigger 2
#define TRGSRC_PWM7_TRG1	0b10000	// PWM7 Trigger 1
#define TRGSRC_PWM6_TRG2	0b01111	// PWM6 Trigger 2
#define TRGSRC_PWM6_TRG1	0b01110	// PWM6 Trigger 1
#define TRGSRC_PWM5_TRG2	0b01101	// PWM5 Trigger 2
#define TRGSRC_PWM5_TRG1	0b01100	// PWM5 Trigger 1
#define TRGSRC_PWM4_TRG2	0b01011	// PWM4 Trigger 2
#define TRGSRC_PWM4_TRG1	0b01010	// PWM4 Trigger 1
#define TRGSRC_PWM3_TRG2	0b01001	// PWM3 Trigger 2
#define TRGSRC_PWM3_TRG1	0b01000	// PWM3 Trigger 1
#define TRGSRC_PWM2_TRG2	0b00111	// PWM2 Trigger 2
#define TRGSRC_PWM2_TRG1	0b00110	// PWM2 Trigger 1
#define TRGSRC_PWM1_TRG2	0b00101	// PWM1 Trigger 2
#define TRGSRC_PWM1_TRG1	0b00100	// PWM1 Trigger 1
#define TRGSRC_SWLVLTRG 	0b00010	// Level software trigger
#define TRGSRC_SWCOMTRG 	0b00001	// Common software trigger
#define TRGSRC_DISABLED 	0b00000	// No trigger is enabled

// Device Pin #28 is RB0
#define CLKI_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define CLKI_GPIO_PORT_PIN 0 // Port Pin Number
#define CLKI_TRIS    TRISBbits.TRISB0 // GPIO direction register bit
#define CLKI_WR      LATBbits.LATB0 // GPIO port latch register bit
#define CLKI_RD      PORTBbits.RB0 // GPIO port register bit
#define CLKI_ODC     ODCBbits.ODCB0 // GPIO port open drain configuration register bit
#define CLKI_CNPU    CNPUBbits.CNPUB0 // GPIO port pull-up resistor register bit
#define CLKI_CNPD    CNPDBbits.CNPDB0 // GPIO port pull-down resistor register bit
#define CLKI_CNEN0   CNEN0Bbits.CNEN0B0 // GPIO port change notification Enable register bit
#define CLKI_CNSTAT  CNSTATBbits.CNSTATB0 // GPIO port change notification Status register bit
#define CLKI_CNEN1   CNEN1Bbits.CNEN1B0 // GPIO port change notification Edge Select Enable register bit
#define CLKI_CNF     CNFBbits.CNFB0 // GPIO port change notification flag bit register bit
#define CLKI_RP      32 // Number of Remappable Pin
#define _CLKI_RPxR    _RP32R // Remappable Pin Register
#define CLKI_SET     { asm volatile ("bset _LATB, #0 \n"); }
#define CLKI_CLEAR   { asm volatile ("bclr _LATB, #0 \n"); }
#define CLKI_TOGGLE  { asm volatile ("btg  _LATB, #0 \n"); }
#define CLKI_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define CLKI_ANSEL   _ANSELB0 // analog/digital pin configuration register bit
#define CLKI_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define CLKI_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define CLKI_ADCAN   5   // ANx input pin number
#define CLKI_ADCBUF  ADCBUF5 // ADC buffer register for this input
#define CLKI_ADIE_IEx ADIELbits.IE5
#define CLKI_ADEIE_EIEx ADEIELbits.EIEN5
#define CLKI_ADCANxIF  _ADCAN5IF // interrupt flag bit
#define CLKI_ADCANxIE  _ADCAN5IE // interrupt enable bit
#define CLKI_ADCANxIP  _ADCAN5IP // interrupt priority for this analog input
#define CLKI_ANxRDY    _AN5RDY // ADC buffer ready bit
#define _CLKI_ADCANxInterrupt _ADCAN5Interrupt
#define CLKI_ANxTRGSRC _TRGSRC5 // ADC input trigger source register
#define CLKI_INIT_ANALOG	{CLKI_ANSEL = 1; CLKI_WR = PINSTATE_HIGH; CLKI_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define CLKI_DISPOSE      {CLKI_WR = PINSTATE_HIGH; CLKI_TRIS = PINDIR_INPUT; CLKI_ANSEL = 0;} // disposing macro for digital input with analog function
#define CLKI_INIT_OUTPUT  {CLKI_WR = PINSTATE_LOW; CLKI_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define CLKI_INIT_INPUT   {CLKI_WR = PINSTATE_HIGH; CLKI_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #8 is RD15
#define DBGLED_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define DBGLED_GPIO_PORT_PIN 15 // Port Pin Number
#define DBGLED_TRIS    TRISDbits.TRISD15 // GPIO direction register bit
#define DBGLED_WR      LATDbits.LATD15 // GPIO port latch register bit
#define DBGLED_RD      PORTDbits.RD15 // GPIO port register bit
#define DBGLED_ODC     ODCDbits.ODCD15 // GPIO port open drain configuration register bit
#define DBGLED_CNPU    CNPUDbits.CNPUD15 // GPIO port pull-up resistor register bit
#define DBGLED_CNPD    CNPDDbits.CNPDD15 // GPIO port pull-down resistor register bit
#define DBGLED_CNEN0   CNEN0Dbits.CNEN0D15 // GPIO port change notification Enable register bit
#define DBGLED_CNSTAT  CNSTATDbits.CNSTATD15 // GPIO port change notification Status register bit
#define DBGLED_CNEN1   CNEN1Dbits.CNEN1D15 // GPIO port change notification Edge Select Enable register bit
#define DBGLED_CNF     CNFDbits.CNFD15 // GPIO port change notification flag bit register bit
#define DBGLED_RP      79 // Number of Remappable Pin
#define _DBGLED_RPxR    _RP79R // Remappable Pin Register
#define DBGLED_SET     { asm volatile ("bset _LATD, #15 \n"); }
#define DBGLED_CLEAR   { asm volatile ("bclr _LATD, #15 \n"); }
#define DBGLED_TOGGLE  { asm volatile ("btg  _LATD, #15 \n"); }
#define DBGLED_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define DBGLED_DISPOSE      {DBGLED_WR = PINSTATE_HIGH; DBGLED_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define DBGLED_INIT_OUTPUT  {DBGLED_WR = PINSTATE_LOW; DBGLED_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define DBGLED_INIT_INPUT   {DBGLED_WR = PINSTATE_HIGH; DBGLED_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #21 is RD12
#define DBGPIN_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define DBGPIN_GPIO_PORT_PIN 12 // Port Pin Number
#define DBGPIN_TRIS    TRISDbits.TRISD12 // GPIO direction register bit
#define DBGPIN_WR      LATDbits.LATD12 // GPIO port latch register bit
#define DBGPIN_RD      PORTDbits.RD12 // GPIO port register bit
#define DBGPIN_ODC     ODCDbits.ODCD12 // GPIO port open drain configuration register bit
#define DBGPIN_CNPU    CNPUDbits.CNPUD12 // GPIO port pull-up resistor register bit
#define DBGPIN_CNPD    CNPDDbits.CNPDD12 // GPIO port pull-down resistor register bit
#define DBGPIN_CNEN0   CNEN0Dbits.CNEN0D12 // GPIO port change notification Enable register bit
#define DBGPIN_CNSTAT  CNSTATDbits.CNSTATD12 // GPIO port change notification Status register bit
#define DBGPIN_CNEN1   CNEN1Dbits.CNEN1D12 // GPIO port change notification Edge Select Enable register bit
#define DBGPIN_CNF     CNFDbits.CNFD12 // GPIO port change notification flag bit register bit
#define DBGPIN_RP      76 // Number of Remappable Pin
#define _DBGPIN_RPxR    _RP76R // Remappable Pin Register
#define DBGPIN_SET     { asm volatile ("bset _LATD, #12 \n"); }
#define DBGPIN_CLEAR   { asm volatile ("bclr _LATD, #12 \n"); }
#define DBGPIN_TOGGLE  { asm volatile ("btg  _LATD, #12 \n"); }
#define DBGPIN_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define DBGPIN_DISPOSE      {DBGPIN_WR = PINSTATE_HIGH; DBGPIN_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define DBGPIN_INIT_OUTPUT  {DBGPIN_WR = PINSTATE_LOW; DBGPIN_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define DBGPIN_INIT_INPUT   {DBGPIN_WR = PINSTATE_HIGH; DBGPIN_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #17 is RA3
#define DACOUT_GPIO_INSTANCE 1 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define DACOUT_GPIO_PORT_PIN 3 // Port Pin Number
#define DACOUT_TRIS    TRISAbits.TRISA3 // GPIO direction register bit
#define DACOUT_WR      LATAbits.LATA3 // GPIO port latch register bit
#define DACOUT_RD      PORTAbits.RA3 // GPIO port register bit
#define DACOUT_ODC     ODCAbits.ODCA3 // GPIO port open drain configuration register bit
#define DACOUT_CNPU    CNPUAbits.CNPUA3 // GPIO port pull-up resistor register bit
#define DACOUT_CNPD    CNPDAbits.CNPDA3 // GPIO port pull-down resistor register bit
#define DACOUT_CNEN0   CNEN0Abits.CNEN0A3 // GPIO port change notification Enable register bit
#define DACOUT_CNSTAT  CNSTATAbits.CNSTATA3 // GPIO port change notification Status register bit
#define DACOUT_CNEN1   CNEN1Abits.CNEN1A3 // GPIO port change notification Edge Select Enable register bit
#define DACOUT_CNF     CNFAbits.CNFA3 // GPIO port change notification flag bit register bit
#define DACOUT_SET     { asm volatile ("bset _LATA, #3 \n"); }
#define DACOUT_CLEAR   { asm volatile ("bclr _LATA, #3 \n"); }
#define DACOUT_TOGGLE  { asm volatile ("btg  _LATA, #3 \n"); }
#define DACOUT_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define DACOUT_ANSEL   _ANSELA3 // analog/digital pin configuration register bit
#define DACOUT_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define DACOUT_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define DACOUT_ADCAN   3   // ANx input pin number
#define DACOUT_ADCBUF  ADCBUF3 // ADC buffer register for this input
#define DACOUT_ADIE_IEx ADIELbits.IE3
#define DACOUT_ADEIE_EIEx ADEIELbits.EIEN3
#define DACOUT_ADCANxIF  _ADCAN3IF // interrupt flag bit
#define DACOUT_ADCANxIE  _ADCAN3IE // interrupt enable bit
#define DACOUT_ADCANxIP  _ADCAN3IP // interrupt priority for this analog input
#define DACOUT_ANxRDY    _AN3RDY // ADC buffer ready bit
#define _DACOUT_ADCANxInterrupt _ADCAN3Interrupt
#define DACOUT_ANxTRGSRC _TRGSRC3 // ADC input trigger source register
#define DACOUT_INIT_ANALOG	{DACOUT_ANSEL = 1; DACOUT_WR = PINSTATE_HIGH; DACOUT_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define DACOUT_DISPOSE      {DACOUT_WR = PINSTATE_HIGH; DACOUT_TRIS = PINDIR_INPUT; DACOUT_ANSEL = 0;} // disposing macro for digital input with analog function
#define DACOUT_INIT_OUTPUT  {DACOUT_WR = PINSTATE_LOW; DACOUT_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define DACOUT_INIT_INPUT   {DACOUT_WR = PINSTATE_HIGH; DACOUT_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #27 is RC3
#define ECP04_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP04_GPIO_PORT_PIN 3 // Port Pin Number
#define ECP04_TRIS    TRISCbits.TRISC3 // GPIO direction register bit
#define ECP04_WR      LATCbits.LATC3 // GPIO port latch register bit
#define ECP04_RD      PORTCbits.RC3 // GPIO port register bit
#define ECP04_ODC     ODCCbits.ODCC3 // GPIO port open drain configuration register bit
#define ECP04_CNPU    CNPUCbits.CNPUC3 // GPIO port pull-up resistor register bit
#define ECP04_CNPD    CNPDCbits.CNPDC3 // GPIO port pull-down resistor register bit
#define ECP04_CNEN0   CNEN0Cbits.CNEN0C3 // GPIO port change notification Enable register bit
#define ECP04_CNSTAT  CNSTATCbits.CNSTATC3 // GPIO port change notification Status register bit
#define ECP04_CNEN1   CNEN1Cbits.CNEN1C3 // GPIO port change notification Edge Select Enable register bit
#define ECP04_CNF     CNFCbits.CNFC3 // GPIO port change notification flag bit register bit
#define ECP04_RP      51 // Number of Remappable Pin
#define _ECP04_RPxR    _RP51R // Remappable Pin Register
#define ECP04_SET     { asm volatile ("bset _LATC, #3 \n"); }
#define ECP04_CLEAR   { asm volatile ("bclr _LATC, #3 \n"); }
#define ECP04_TOGGLE  { asm volatile ("btg  _LATC, #3 \n"); }
#define ECP04_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP04_ANSEL   _ANSELC3 // analog/digital pin configuration register bit
#define ECP04_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP04_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP04_ADCAN   15   // ANx input pin number
#define ECP04_ADCBUF  ADCBUF15 // ADC buffer register for this input
#define ECP04_ADIE_IEx ADIELbits.IE15
#define ECP04_ADEIE_EIEx ADEIELbits.EIEN15
#define ECP04_ADCANxIF  _ADCAN15IF // interrupt flag bit
#define ECP04_ADCANxIE  _ADCAN15IE // interrupt enable bit
#define ECP04_ADCANxIP  _ADCAN15IP // interrupt priority for this analog input
#define ECP04_ANxRDY    _AN15RDY // ADC buffer ready bit
#define _ECP04_ADCANxInterrupt _ADCAN15Interrupt
#define ECP04_ANxTRGSRC _TRGSRC15 // ADC input trigger source register
#define ECP04_INIT_ANALOG	{ECP04_ANSEL = 1; ECP04_WR = PINSTATE_HIGH; ECP04_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP04_DISPOSE      {ECP04_WR = PINSTATE_HIGH; ECP04_TRIS = PINDIR_INPUT; ECP04_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP04_INIT_OUTPUT  {ECP04_WR = PINSTATE_LOW; ECP04_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP04_INIT_INPUT   {ECP04_WR = PINSTATE_HIGH; ECP04_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #48 is RB8
#define ECP05_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP05_GPIO_PORT_PIN 8 // Port Pin Number
#define ECP05_TRIS    TRISBbits.TRISB8 // GPIO direction register bit
#define ECP05_WR      LATBbits.LATB8 // GPIO port latch register bit
#define ECP05_RD      PORTBbits.RB8 // GPIO port register bit
#define ECP05_ODC     ODCBbits.ODCB8 // GPIO port open drain configuration register bit
#define ECP05_CNPU    CNPUBbits.CNPUB8 // GPIO port pull-up resistor register bit
#define ECP05_CNPD    CNPDBbits.CNPDB8 // GPIO port pull-down resistor register bit
#define ECP05_CNEN0   CNEN0Bbits.CNEN0B8 // GPIO port change notification Enable register bit
#define ECP05_CNSTAT  CNSTATBbits.CNSTATB8 // GPIO port change notification Status register bit
#define ECP05_CNEN1   CNEN1Bbits.CNEN1B8 // GPIO port change notification Edge Select Enable register bit
#define ECP05_CNF     CNFBbits.CNFB8 // GPIO port change notification flag bit register bit
#define ECP05_RP      40 // Number of Remappable Pin
#define _ECP05_RPxR    _RP40R // Remappable Pin Register
#define ECP05_SET     { asm volatile ("bset _LATB, #8 \n"); }
#define ECP05_CLEAR   { asm volatile ("bclr _LATB, #8 \n"); }
#define ECP05_TOGGLE  { asm volatile ("btg  _LATB, #8 \n"); }
#define ECP05_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP05_ANSEL   _ANSELB8 // analog/digital pin configuration register bit
#define ECP05_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP05_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP05_ADCAN   10   // ANx input pin number
#define ECP05_ADCBUF  ADCBUF10 // ADC buffer register for this input
#define ECP05_ADIE_IEx ADIELbits.IE10
#define ECP05_ADEIE_EIEx ADEIELbits.EIEN10
#define ECP05_ADCANxIF  _ADCAN10IF // interrupt flag bit
#define ECP05_ADCANxIE  _ADCAN10IE // interrupt enable bit
#define ECP05_ADCANxIP  _ADCAN10IP // interrupt priority for this analog input
#define ECP05_ANxRDY    _AN10RDY // ADC buffer ready bit
#define _ECP05_ADCANxInterrupt _ADCAN10Interrupt
#define ECP05_ANxTRGSRC _TRGSRC10 // ADC input trigger source register
#define ECP05_INIT_ANALOG	{ECP05_ANSEL = 1; ECP05_WR = PINSTATE_HIGH; ECP05_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP05_DISPOSE      {ECP05_WR = PINSTATE_HIGH; ECP05_TRIS = PINDIR_INPUT; ECP05_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP05_INIT_OUTPUT  {ECP05_WR = PINSTATE_LOW; ECP05_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP05_INIT_INPUT   {ECP05_WR = PINSTATE_HIGH; ECP05_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #33 is RB2
#define ECP06_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP06_GPIO_PORT_PIN 2 // Port Pin Number
#define ECP06_TRIS    TRISBbits.TRISB2 // GPIO direction register bit
#define ECP06_WR      LATBbits.LATB2 // GPIO port latch register bit
#define ECP06_RD      PORTBbits.RB2 // GPIO port register bit
#define ECP06_ODC     ODCBbits.ODCB2 // GPIO port open drain configuration register bit
#define ECP06_CNPU    CNPUBbits.CNPUB2 // GPIO port pull-up resistor register bit
#define ECP06_CNPD    CNPDBbits.CNPDB2 // GPIO port pull-down resistor register bit
#define ECP06_CNEN0   CNEN0Bbits.CNEN0B2 // GPIO port change notification Enable register bit
#define ECP06_CNSTAT  CNSTATBbits.CNSTATB2 // GPIO port change notification Status register bit
#define ECP06_CNEN1   CNEN1Bbits.CNEN1B2 // GPIO port change notification Edge Select Enable register bit
#define ECP06_CNF     CNFBbits.CNFB2 // GPIO port change notification flag bit register bit
#define ECP06_RP      34 // Number of Remappable Pin
#define _ECP06_RPxR    _RP34R // Remappable Pin Register
#define ECP06_SET     { asm volatile ("bset _LATB, #2 \n"); }
#define ECP06_CLEAR   { asm volatile ("bclr _LATB, #2 \n"); }
#define ECP06_TOGGLE  { asm volatile ("btg  _LATB, #2 \n"); }
#define ECP06_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP06_ANSEL   _ANSELB2 // analog/digital pin configuration register bit
#define ECP06_ADCCORE 1 // index starts from zero, last index indicated shared adC core
#define ECP06_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP06_ADCAN   1   // ANx input pin number
#define ECP06_ADCBUF  ADCBUF1 // ADC buffer register for this input
#define ECP06_ADIE_IEx ADIELbits.IE1
#define ECP06_ADEIE_EIEx ADEIELbits.EIEN1
#define ECP06_ADCANxIF  _ADCAN1IF // interrupt flag bit
#define ECP06_ADCANxIE  _ADCAN1IE // interrupt enable bit
#define ECP06_ADCANxIP  _ADCAN1IP // interrupt priority for this analog input
#define ECP06_ANxRDY    _AN1RDY // ADC buffer ready bit
#define _ECP06_ADCANxInterrupt _ADCAN1Interrupt
#define ECP06_ANxTRGSRC _TRGSRC1 // ADC input trigger source register
#define ECP06_INIT_ANALOG	{ECP06_ANSEL = 1; ECP06_WR = PINSTATE_HIGH; ECP06_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP06_DISPOSE      {ECP06_WR = PINSTATE_HIGH; ECP06_TRIS = PINDIR_INPUT; ECP06_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP06_INIT_OUTPUT  {ECP06_WR = PINSTATE_LOW; ECP06_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP06_INIT_INPUT   {ECP06_WR = PINSTATE_HIGH; ECP06_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #18 is RA4
#define ECP08_GPIO_INSTANCE 1 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP08_GPIO_PORT_PIN 4 // Port Pin Number
#define ECP08_TRIS    TRISAbits.TRISA4 // GPIO direction register bit
#define ECP08_WR      LATAbits.LATA4 // GPIO port latch register bit
#define ECP08_RD      PORTAbits.RA4 // GPIO port register bit
#define ECP08_ODC     ODCAbits.ODCA4 // GPIO port open drain configuration register bit
#define ECP08_CNPU    CNPUAbits.CNPUA4 // GPIO port pull-up resistor register bit
#define ECP08_CNPD    CNPDAbits.CNPDA4 // GPIO port pull-down resistor register bit
#define ECP08_CNEN0   CNEN0Abits.CNEN0A4 // GPIO port change notification Enable register bit
#define ECP08_CNSTAT  CNSTATAbits.CNSTATA4 // GPIO port change notification Status register bit
#define ECP08_CNEN1   CNEN1Abits.CNEN1A4 // GPIO port change notification Edge Select Enable register bit
#define ECP08_CNF     CNFAbits.CNFA4 // GPIO port change notification flag bit register bit
#define ECP08_SET     { asm volatile ("bset _LATA, #4 \n"); }
#define ECP08_CLEAR   { asm volatile ("bclr _LATA, #4 \n"); }
#define ECP08_TOGGLE  { asm volatile ("btg  _LATA, #4 \n"); }
#define ECP08_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP08_ANSEL   _ANSELA4 // analog/digital pin configuration register bit
#define ECP08_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP08_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP08_ADCAN   4   // ANx input pin number
#define ECP08_ADCBUF  ADCBUF4 // ADC buffer register for this input
#define ECP08_ADIE_IEx ADIELbits.IE4
#define ECP08_ADEIE_EIEx ADEIELbits.EIEN4
#define ECP08_ADCANxIF  _ADCAN4IF // interrupt flag bit
#define ECP08_ADCANxIE  _ADCAN4IE // interrupt enable bit
#define ECP08_ADCANxIP  _ADCAN4IP // interrupt priority for this analog input
#define ECP08_ANxRDY    _AN4RDY // ADC buffer ready bit
#define _ECP08_ADCANxInterrupt _ADCAN4Interrupt
#define ECP08_ANxTRGSRC _TRGSRC4 // ADC input trigger source register
#define ECP08_INIT_ANALOG	{ECP08_ANSEL = 1; ECP08_WR = PINSTATE_HIGH; ECP08_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP08_DISPOSE      {ECP08_WR = PINSTATE_HIGH; ECP08_TRIS = PINDIR_INPUT; ECP08_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP08_INIT_OUTPUT  {ECP08_WR = PINSTATE_LOW; ECP08_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP08_INIT_INPUT   {ECP08_WR = PINSTATE_HIGH; ECP08_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #24 is RC6
#define ECP09_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP09_GPIO_PORT_PIN 6 // Port Pin Number
#define ECP09_TRIS    TRISCbits.TRISC6 // GPIO direction register bit
#define ECP09_WR      LATCbits.LATC6 // GPIO port latch register bit
#define ECP09_RD      PORTCbits.RC6 // GPIO port register bit
#define ECP09_ODC     ODCCbits.ODCC6 // GPIO port open drain configuration register bit
#define ECP09_CNPU    CNPUCbits.CNPUC6 // GPIO port pull-up resistor register bit
#define ECP09_CNPD    CNPDCbits.CNPDC6 // GPIO port pull-down resistor register bit
#define ECP09_CNEN0   CNEN0Cbits.CNEN0C6 // GPIO port change notification Enable register bit
#define ECP09_CNSTAT  CNSTATCbits.CNSTATC6 // GPIO port change notification Status register bit
#define ECP09_CNEN1   CNEN1Cbits.CNEN1C6 // GPIO port change notification Edge Select Enable register bit
#define ECP09_CNF     CNFCbits.CNFC6 // GPIO port change notification flag bit register bit
#define ECP09_RP      54 // Number of Remappable Pin
#define _ECP09_RPxR    _RP54R // Remappable Pin Register
#define ECP09_SET     { asm volatile ("bset _LATC, #6 \n"); }
#define ECP09_CLEAR   { asm volatile ("bclr _LATC, #6 \n"); }
#define ECP09_TOGGLE  { asm volatile ("btg  _LATC, #6 \n"); }
#define ECP09_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP09_ANSEL   _ANSELC6 // analog/digital pin configuration register bit
#define ECP09_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP09_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP09_ADCAN   17   // ANx input pin number
#define ECP09_ADCBUF  ADCBUF17 // ADC buffer register for this input
#define ECP09_ADIE_IEx ADIEHbits.IE17
#define ECP09_ADEIE_EIEx ADEIEHbits.EIEN17
#define ECP09_ADCANxIF  _ADCAN17IF // interrupt flag bit
#define ECP09_ADCANxIE  _ADCAN17IE // interrupt enable bit
#define ECP09_ADCANxIP  _ADCAN17IP // interrupt priority for this analog input
#define ECP09_ANxRDY    _AN17RDY // ADC buffer ready bit
#define _ECP09_ADCANxInterrupt _ADCAN17Interrupt
#define ECP09_ANxTRGSRC _TRGSRC17 // ADC input trigger source register
#define ECP09_INIT_ANALOG	{ECP09_ANSEL = 1; ECP09_WR = PINSTATE_HIGH; ECP09_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP09_DISPOSE      {ECP09_WR = PINSTATE_HIGH; ECP09_TRIS = PINDIR_INPUT; ECP09_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP09_INIT_OUTPUT  {ECP09_WR = PINSTATE_LOW; ECP09_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP09_INIT_INPUT   {ECP09_WR = PINSTATE_HIGH; ECP09_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #47 is RB7
#define ECP10_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP10_GPIO_PORT_PIN 7 // Port Pin Number
#define ECP10_TRIS    TRISBbits.TRISB7 // GPIO direction register bit
#define ECP10_WR      LATBbits.LATB7 // GPIO port latch register bit
#define ECP10_RD      PORTBbits.RB7 // GPIO port register bit
#define ECP10_ODC     ODCBbits.ODCB7 // GPIO port open drain configuration register bit
#define ECP10_CNPU    CNPUBbits.CNPUB7 // GPIO port pull-up resistor register bit
#define ECP10_CNPD    CNPDBbits.CNPDB7 // GPIO port pull-down resistor register bit
#define ECP10_CNEN0   CNEN0Bbits.CNEN0B7 // GPIO port change notification Enable register bit
#define ECP10_CNSTAT  CNSTATBbits.CNSTATB7 // GPIO port change notification Status register bit
#define ECP10_CNEN1   CNEN1Bbits.CNEN1B7 // GPIO port change notification Edge Select Enable register bit
#define ECP10_CNF     CNFBbits.CNFB7 // GPIO port change notification flag bit register bit
#define ECP10_RP      39 // Number of Remappable Pin
#define _ECP10_RPxR    _RP39R // Remappable Pin Register
#define ECP10_SET     { asm volatile ("bset _LATB, #7 \n"); }
#define ECP10_CLEAR   { asm volatile ("bclr _LATB, #7 \n"); }
#define ECP10_TOGGLE  { asm volatile ("btg  _LATB, #7 \n"); }
#define ECP10_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP10_ANSEL   _ANSELB7 // analog/digital pin configuration register bit
#define ECP10_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP10_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP10_ADCAN   2   // ANx input pin number
#define ECP10_ADCBUF  ADCBUF2 // ADC buffer register for this input
#define ECP10_ADIE_IEx ADIELbits.IE2
#define ECP10_ADEIE_EIEx ADEIELbits.EIEN2
#define ECP10_ADCANxIF  _ADCAN2IF // interrupt flag bit
#define ECP10_ADCANxIE  _ADCAN2IE // interrupt enable bit
#define ECP10_ADCANxIP  _ADCAN2IP // interrupt priority for this analog input
#define ECP10_ANxRDY    _AN2RDY // ADC buffer ready bit
#define _ECP10_ADCANxInterrupt _ADCAN2Interrupt
#define ECP10_ANxTRGSRC _TRGSRC2 // ADC input trigger source register
#define ECP10_INIT_ANALOG	{ECP10_ANSEL = 1; ECP10_WR = PINSTATE_HIGH; ECP10_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP10_DISPOSE      {ECP10_WR = PINSTATE_HIGH; ECP10_TRIS = PINDIR_INPUT; ECP10_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP10_INIT_OUTPUT  {ECP10_WR = PINSTATE_LOW; ECP10_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP10_INIT_INPUT   {ECP10_WR = PINSTATE_HIGH; ECP10_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #15 is RA1
#define ECP11_GPIO_INSTANCE 1 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP11_GPIO_PORT_PIN 1 // Port Pin Number
#define ECP11_TRIS    TRISAbits.TRISA1 // GPIO direction register bit
#define ECP11_WR      LATAbits.LATA1 // GPIO port latch register bit
#define ECP11_RD      PORTAbits.RA1 // GPIO port register bit
#define ECP11_ODC     ODCAbits.ODCA1 // GPIO port open drain configuration register bit
#define ECP11_CNPU    CNPUAbits.CNPUA1 // GPIO port pull-up resistor register bit
#define ECP11_CNPD    CNPDAbits.CNPDA1 // GPIO port pull-down resistor register bit
#define ECP11_CNEN0   CNEN0Abits.CNEN0A1 // GPIO port change notification Enable register bit
#define ECP11_CNSTAT  CNSTATAbits.CNSTATA1 // GPIO port change notification Status register bit
#define ECP11_CNEN1   CNEN1Abits.CNEN1A1 // GPIO port change notification Edge Select Enable register bit
#define ECP11_CNF     CNFAbits.CNFA1 // GPIO port change notification flag bit register bit
#define ECP11_SET     { asm volatile ("bset _LATA, #1 \n"); }
#define ECP11_CLEAR   { asm volatile ("bclr _LATA, #1 \n"); }
#define ECP11_TOGGLE  { asm volatile ("btg  _LATA, #1 \n"); }
#define ECP11_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP11_DISPOSE      {ECP11_WR = PINSTATE_HIGH; ECP11_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP11_INIT_OUTPUT  {ECP11_WR = PINSTATE_LOW; ECP11_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP11_INIT_INPUT   {ECP11_WR = PINSTATE_HIGH; ECP11_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #14 is RA0
#define ECP12_GPIO_INSTANCE 1 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP12_GPIO_PORT_PIN 0 // Port Pin Number
#define ECP12_TRIS    TRISAbits.TRISA0 // GPIO direction register bit
#define ECP12_WR      LATAbits.LATA0 // GPIO port latch register bit
#define ECP12_RD      PORTAbits.RA0 // GPIO port register bit
#define ECP12_ODC     ODCAbits.ODCA0 // GPIO port open drain configuration register bit
#define ECP12_CNPU    CNPUAbits.CNPUA0 // GPIO port pull-up resistor register bit
#define ECP12_CNPD    CNPDAbits.CNPDA0 // GPIO port pull-down resistor register bit
#define ECP12_CNEN0   CNEN0Abits.CNEN0A0 // GPIO port change notification Enable register bit
#define ECP12_CNSTAT  CNSTATAbits.CNSTATA0 // GPIO port change notification Status register bit
#define ECP12_CNEN1   CNEN1Abits.CNEN1A0 // GPIO port change notification Edge Select Enable register bit
#define ECP12_CNF     CNFAbits.CNFA0 // GPIO port change notification flag bit register bit
#define ECP12_SET     { asm volatile ("bset _LATA, #0 \n"); }
#define ECP12_CLEAR   { asm volatile ("bclr _LATA, #0 \n"); }
#define ECP12_TOGGLE  { asm volatile ("btg  _LATA, #0 \n"); }
#define ECP12_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP12_ANSEL   _ANSELA0 // analog/digital pin configuration register bit
#define ECP12_ADCCORE 0 // index starts from zero, last index indicated shared adC core
#define ECP12_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP12_ADCAN   0   // ANx input pin number
#define ECP12_ADCBUF  ADCBUF0 // ADC buffer register for this input
#define ECP12_ADIE_IEx ADIELbits.IE0
#define ECP12_ADEIE_EIEx ADEIELbits.EIEN0
#define ECP12_ADCANxIF  _ADCAN0IF // interrupt flag bit
#define ECP12_ADCANxIE  _ADCAN0IE // interrupt enable bit
#define ECP12_ADCANxIP  _ADCAN0IP // interrupt priority for this analog input
#define ECP12_ANxRDY    _AN0RDY // ADC buffer ready bit
#define _ECP12_ADCANxInterrupt _ADCAN0Interrupt
#define ECP12_ANxTRGSRC _TRGSRC0 // ADC input trigger source register
#define ECP12_INIT_ANALOG	{ECP12_ANSEL = 1; ECP12_WR = PINSTATE_HIGH; ECP12_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP12_DISPOSE      {ECP12_WR = PINSTATE_HIGH; ECP12_TRIS = PINDIR_INPUT; ECP12_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP12_INIT_OUTPUT  {ECP12_WR = PINSTATE_LOW; ECP12_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP12_INIT_INPUT   {ECP12_WR = PINSTATE_HIGH; ECP12_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #30 is RD11
#define ECP13_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP13_GPIO_PORT_PIN 11 // Port Pin Number
#define ECP13_TRIS    TRISDbits.TRISD11 // GPIO direction register bit
#define ECP13_WR      LATDbits.LATD11 // GPIO port latch register bit
#define ECP13_RD      PORTDbits.RD11 // GPIO port register bit
#define ECP13_ODC     ODCDbits.ODCD11 // GPIO port open drain configuration register bit
#define ECP13_CNPU    CNPUDbits.CNPUD11 // GPIO port pull-up resistor register bit
#define ECP13_CNPD    CNPDDbits.CNPDD11 // GPIO port pull-down resistor register bit
#define ECP13_CNEN0   CNEN0Dbits.CNEN0D11 // GPIO port change notification Enable register bit
#define ECP13_CNSTAT  CNSTATDbits.CNSTATD11 // GPIO port change notification Status register bit
#define ECP13_CNEN1   CNEN1Dbits.CNEN1D11 // GPIO port change notification Edge Select Enable register bit
#define ECP13_CNF     CNFDbits.CNFD11 // GPIO port change notification flag bit register bit
#define ECP13_RP      75 // Number of Remappable Pin
#define _ECP13_RPxR    _RP75R // Remappable Pin Register
#define ECP13_SET     { asm volatile ("bset _LATD, #11 \n"); }
#define ECP13_CLEAR   { asm volatile ("bclr _LATD, #11 \n"); }
#define ECP13_TOGGLE  { asm volatile ("btg  _LATD, #11 \n"); }
#define ECP13_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP13_ANSEL   _ANSELD11 // analog/digital pin configuration register bit
#define ECP13_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP13_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP13_ADCAN   19   // ANx input pin number
#define ECP13_ADCBUF  ADCBUF19 // ADC buffer register for this input
#define ECP13_ADIE_IEx ADIEHbits.IE19
#define ECP13_ADEIE_EIEx ADEIEHbits.EIEN19
#define ECP13_ADCANxIF  _ADCAN19IF // interrupt flag bit
#define ECP13_ADCANxIE  _ADCAN19IE // interrupt enable bit
#define ECP13_ADCANxIP  _ADCAN19IP // interrupt priority for this analog input
#define ECP13_ANxRDY    _AN19RDY // ADC buffer ready bit
#define _ECP13_ADCANxInterrupt _ADCAN19Interrupt
#define ECP13_ANxTRGSRC _TRGSRC19 // ADC input trigger source register
#define ECP13_INIT_ANALOG	{ECP13_ANSEL = 1; ECP13_WR = PINSTATE_HIGH; ECP13_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP13_DISPOSE      {ECP13_WR = PINSTATE_HIGH; ECP13_TRIS = PINDIR_INPUT; ECP13_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP13_INIT_OUTPUT  {ECP13_WR = PINSTATE_LOW; ECP13_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP13_INIT_INPUT   {ECP13_WR = PINSTATE_HIGH; ECP13_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #32 is RC7
#define ECP14_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP14_GPIO_PORT_PIN 7 // Port Pin Number
#define ECP14_TRIS    TRISCbits.TRISC7 // GPIO direction register bit
#define ECP14_WR      LATCbits.LATC7 // GPIO port latch register bit
#define ECP14_RD      PORTCbits.RC7 // GPIO port register bit
#define ECP14_ODC     ODCCbits.ODCC7 // GPIO port open drain configuration register bit
#define ECP14_CNPU    CNPUCbits.CNPUC7 // GPIO port pull-up resistor register bit
#define ECP14_CNPD    CNPDCbits.CNPDC7 // GPIO port pull-down resistor register bit
#define ECP14_CNEN0   CNEN0Cbits.CNEN0C7 // GPIO port change notification Enable register bit
#define ECP14_CNSTAT  CNSTATCbits.CNSTATC7 // GPIO port change notification Status register bit
#define ECP14_CNEN1   CNEN1Cbits.CNEN1C7 // GPIO port change notification Edge Select Enable register bit
#define ECP14_CNF     CNFCbits.CNFC7 // GPIO port change notification flag bit register bit
#define ECP14_RP      55 // Number of Remappable Pin
#define _ECP14_RPxR    _RP55R // Remappable Pin Register
#define ECP14_SET     { asm volatile ("bset _LATC, #7 \n"); }
#define ECP14_CLEAR   { asm volatile ("bclr _LATC, #7 \n"); }
#define ECP14_TOGGLE  { asm volatile ("btg  _LATC, #7 \n"); }
#define ECP14_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP14_ANSEL   _ANSELC7 // analog/digital pin configuration register bit
#define ECP14_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP14_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP14_ADCAN   16   // ANx input pin number
#define ECP14_ADCBUF  ADCBUF16 // ADC buffer register for this input
#define ECP14_ADIE_IEx ADIEHbits.IE16
#define ECP14_ADEIE_EIEx ADEIEHbits.EIEN16
#define ECP14_ADCANxIF  _ADCAN16IF // interrupt flag bit
#define ECP14_ADCANxIE  _ADCAN16IE // interrupt enable bit
#define ECP14_ADCANxIP  _ADCAN16IP // interrupt priority for this analog input
#define ECP14_ANxRDY    _AN16RDY // ADC buffer ready bit
#define _ECP14_ADCANxInterrupt _ADCAN16Interrupt
#define ECP14_ANxTRGSRC _TRGSRC16 // ADC input trigger source register
#define ECP14_INIT_ANALOG	{ECP14_ANSEL = 1; ECP14_WR = PINSTATE_HIGH; ECP14_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP14_DISPOSE      {ECP14_WR = PINSTATE_HIGH; ECP14_TRIS = PINDIR_INPUT; ECP14_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP14_INIT_OUTPUT  {ECP14_WR = PINSTATE_LOW; ECP14_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP14_INIT_INPUT   {ECP14_WR = PINSTATE_HIGH; ECP14_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #31 is RD10
#define ECP15_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP15_GPIO_PORT_PIN 10 // Port Pin Number
#define ECP15_TRIS    TRISDbits.TRISD10 // GPIO direction register bit
#define ECP15_WR      LATDbits.LATD10 // GPIO port latch register bit
#define ECP15_RD      PORTDbits.RD10 // GPIO port register bit
#define ECP15_ODC     ODCDbits.ODCD10 // GPIO port open drain configuration register bit
#define ECP15_CNPU    CNPUDbits.CNPUD10 // GPIO port pull-up resistor register bit
#define ECP15_CNPD    CNPDDbits.CNPDD10 // GPIO port pull-down resistor register bit
#define ECP15_CNEN0   CNEN0Dbits.CNEN0D10 // GPIO port change notification Enable register bit
#define ECP15_CNSTAT  CNSTATDbits.CNSTATD10 // GPIO port change notification Status register bit
#define ECP15_CNEN1   CNEN1Dbits.CNEN1D10 // GPIO port change notification Edge Select Enable register bit
#define ECP15_CNF     CNFDbits.CNFD10 // GPIO port change notification flag bit register bit
#define ECP15_RP      74 // Number of Remappable Pin
#define _ECP15_RPxR    _RP74R // Remappable Pin Register
#define ECP15_SET     { asm volatile ("bset _LATD, #10 \n"); }
#define ECP15_CLEAR   { asm volatile ("bclr _LATD, #10 \n"); }
#define ECP15_TOGGLE  { asm volatile ("btg  _LATD, #10 \n"); }
#define ECP15_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP15_ANSEL   _ANSELD10 // analog/digital pin configuration register bit
#define ECP15_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP15_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP15_ADCAN   18   // ANx input pin number
#define ECP15_ADCBUF  ADCBUF18 // ADC buffer register for this input
#define ECP15_ADIE_IEx ADIEHbits.IE18
#define ECP15_ADEIE_EIEx ADEIEHbits.EIEN18
#define ECP15_ADCANxIF  _ADCAN18IF // interrupt flag bit
#define ECP15_ADCANxIE  _ADCAN18IE // interrupt enable bit
#define ECP15_ADCANxIP  _ADCAN18IP // interrupt priority for this analog input
#define ECP15_ANxRDY    _AN18RDY // ADC buffer ready bit
#define _ECP15_ADCANxInterrupt _ADCAN18Interrupt
#define ECP15_ANxTRGSRC _TRGSRC18 // ADC input trigger source register
#define ECP15_INIT_ANALOG	{ECP15_ANSEL = 1; ECP15_WR = PINSTATE_HIGH; ECP15_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP15_DISPOSE      {ECP15_WR = PINSTATE_HIGH; ECP15_TRIS = PINDIR_INPUT; ECP15_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP15_INIT_OUTPUT  {ECP15_WR = PINSTATE_LOW; ECP15_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP15_INIT_INPUT   {ECP15_WR = PINSTATE_HIGH; ECP15_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #13 is RC0
#define ECP16_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP16_GPIO_PORT_PIN 0 // Port Pin Number
#define ECP16_TRIS    TRISCbits.TRISC0 // GPIO direction register bit
#define ECP16_WR      LATCbits.LATC0 // GPIO port latch register bit
#define ECP16_RD      PORTCbits.RC0 // GPIO port register bit
#define ECP16_ODC     ODCCbits.ODCC0 // GPIO port open drain configuration register bit
#define ECP16_CNPU    CNPUCbits.CNPUC0 // GPIO port pull-up resistor register bit
#define ECP16_CNPD    CNPDCbits.CNPDC0 // GPIO port pull-down resistor register bit
#define ECP16_CNEN0   CNEN0Cbits.CNEN0C0 // GPIO port change notification Enable register bit
#define ECP16_CNSTAT  CNSTATCbits.CNSTATC0 // GPIO port change notification Status register bit
#define ECP16_CNEN1   CNEN1Cbits.CNEN1C0 // GPIO port change notification Edge Select Enable register bit
#define ECP16_CNF     CNFCbits.CNFC0 // GPIO port change notification flag bit register bit
#define ECP16_RP      48 // Number of Remappable Pin
#define _ECP16_RPxR    _RP48R // Remappable Pin Register
#define ECP16_SET     { asm volatile ("bset _LATC, #0 \n"); }
#define ECP16_CLEAR   { asm volatile ("bclr _LATC, #0 \n"); }
#define ECP16_TOGGLE  { asm volatile ("btg  _LATC, #0 \n"); }
#define ECP16_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP16_ANSEL   _ANSELC0 // analog/digital pin configuration register bit
#define ECP16_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP16_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP16_ADCAN   12   // ANx input pin number
#define ECP16_ADCBUF  ADCBUF12 // ADC buffer register for this input
#define ECP16_ADIE_IEx ADIELbits.IE12
#define ECP16_ADEIE_EIEx ADEIELbits.EIEN12
#define ECP16_ADCANxIF  _ADCAN12IF // interrupt flag bit
#define ECP16_ADCANxIE  _ADCAN12IE // interrupt enable bit
#define ECP16_ADCANxIP  _ADCAN12IP // interrupt priority for this analog input
#define ECP16_ANxRDY    _AN12RDY // ADC buffer ready bit
#define _ECP16_ADCANxInterrupt _ADCAN12Interrupt
#define ECP16_ANxTRGSRC _TRGSRC12 // ADC input trigger source register
#define ECP16_INIT_ANALOG	{ECP16_ANSEL = 1; ECP16_WR = PINSTATE_HIGH; ECP16_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP16_DISPOSE      {ECP16_WR = PINSTATE_HIGH; ECP16_TRIS = PINDIR_INPUT; ECP16_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP16_INIT_OUTPUT  {ECP16_WR = PINSTATE_LOW; ECP16_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP16_INIT_INPUT   {ECP16_WR = PINSTATE_HIGH; ECP16_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #23 is RC2
#define ECP17_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP17_GPIO_PORT_PIN 2 // Port Pin Number
#define ECP17_TRIS    TRISCbits.TRISC2 // GPIO direction register bit
#define ECP17_WR      LATCbits.LATC2 // GPIO port latch register bit
#define ECP17_RD      PORTCbits.RC2 // GPIO port register bit
#define ECP17_ODC     ODCCbits.ODCC2 // GPIO port open drain configuration register bit
#define ECP17_CNPU    CNPUCbits.CNPUC2 // GPIO port pull-up resistor register bit
#define ECP17_CNPD    CNPDCbits.CNPDC2 // GPIO port pull-down resistor register bit
#define ECP17_CNEN0   CNEN0Cbits.CNEN0C2 // GPIO port change notification Enable register bit
#define ECP17_CNSTAT  CNSTATCbits.CNSTATC2 // GPIO port change notification Status register bit
#define ECP17_CNEN1   CNEN1Cbits.CNEN1C2 // GPIO port change notification Edge Select Enable register bit
#define ECP17_CNF     CNFCbits.CNFC2 // GPIO port change notification flag bit register bit
#define ECP17_RP      50 // Number of Remappable Pin
#define _ECP17_RPxR    _RP50R // Remappable Pin Register
#define ECP17_SET     { asm volatile ("bset _LATC, #2 \n"); }
#define ECP17_CLEAR   { asm volatile ("bclr _LATC, #2 \n"); }
#define ECP17_TOGGLE  { asm volatile ("btg  _LATC, #2 \n"); }
#define ECP17_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP17_ANSEL   _ANSELC2 // analog/digital pin configuration register bit
#define ECP17_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP17_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP17_ADCAN   14   // ANx input pin number
#define ECP17_ADCBUF  ADCBUF14 // ADC buffer register for this input
#define ECP17_ADIE_IEx ADIELbits.IE14
#define ECP17_ADEIE_EIEx ADEIELbits.EIEN14
#define ECP17_ADCANxIF  _ADCAN14IF // interrupt flag bit
#define ECP17_ADCANxIE  _ADCAN14IE // interrupt enable bit
#define ECP17_ADCANxIP  _ADCAN14IP // interrupt priority for this analog input
#define ECP17_ANxRDY    _AN14RDY // ADC buffer ready bit
#define _ECP17_ADCANxInterrupt _ADCAN14Interrupt
#define ECP17_ANxTRGSRC _TRGSRC14 // ADC input trigger source register
#define ECP17_INIT_ANALOG	{ECP17_ANSEL = 1; ECP17_WR = PINSTATE_HIGH; ECP17_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP17_DISPOSE      {ECP17_WR = PINSTATE_HIGH; ECP17_TRIS = PINDIR_INPUT; ECP17_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP17_INIT_OUTPUT  {ECP17_WR = PINSTATE_LOW; ECP17_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP17_INIT_INPUT   {ECP17_WR = PINSTATE_HIGH; ECP17_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #22 is RC1
#define ECP18_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP18_GPIO_PORT_PIN 1 // Port Pin Number
#define ECP18_TRIS    TRISCbits.TRISC1 // GPIO direction register bit
#define ECP18_WR      LATCbits.LATC1 // GPIO port latch register bit
#define ECP18_RD      PORTCbits.RC1 // GPIO port register bit
#define ECP18_ODC     ODCCbits.ODCC1 // GPIO port open drain configuration register bit
#define ECP18_CNPU    CNPUCbits.CNPUC1 // GPIO port pull-up resistor register bit
#define ECP18_CNPD    CNPDCbits.CNPDC1 // GPIO port pull-down resistor register bit
#define ECP18_CNEN0   CNEN0Cbits.CNEN0C1 // GPIO port change notification Enable register bit
#define ECP18_CNSTAT  CNSTATCbits.CNSTATC1 // GPIO port change notification Status register bit
#define ECP18_CNEN1   CNEN1Cbits.CNEN1C1 // GPIO port change notification Edge Select Enable register bit
#define ECP18_CNF     CNFCbits.CNFC1 // GPIO port change notification flag bit register bit
#define ECP18_RP      49 // Number of Remappable Pin
#define _ECP18_RPxR    _RP49R // Remappable Pin Register
#define ECP18_SET     { asm volatile ("bset _LATC, #1 \n"); }
#define ECP18_CLEAR   { asm volatile ("bclr _LATC, #1 \n"); }
#define ECP18_TOGGLE  { asm volatile ("btg  _LATC, #1 \n"); }
#define ECP18_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP18_ANSEL   _ANSELC1 // analog/digital pin configuration register bit
#define ECP18_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP18_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP18_ADCAN   13   // ANx input pin number
#define ECP18_ADCBUF  ADCBUF13 // ADC buffer register for this input
#define ECP18_ADIE_IEx ADIELbits.IE13
#define ECP18_ADEIE_EIEx ADEIELbits.EIEN13
#define ECP18_ADCANxIF  _ADCAN13IF // interrupt flag bit
#define ECP18_ADCANxIE  _ADCAN13IE // interrupt enable bit
#define ECP18_ADCANxIP  _ADCAN13IP // interrupt priority for this analog input
#define ECP18_ANxRDY    _AN13RDY // ADC buffer ready bit
#define _ECP18_ADCANxInterrupt _ADCAN13Interrupt
#define ECP18_ANxTRGSRC _TRGSRC13 // ADC input trigger source register
#define ECP18_INIT_ANALOG	{ECP18_ANSEL = 1; ECP18_WR = PINSTATE_HIGH; ECP18_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP18_DISPOSE      {ECP18_WR = PINSTATE_HIGH; ECP18_TRIS = PINDIR_INPUT; ECP18_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP18_INIT_OUTPUT  {ECP18_WR = PINSTATE_LOW; ECP18_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP18_INIT_INPUT   {ECP18_WR = PINSTATE_HIGH; ECP18_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #16 is RA2
#define ECP19_GPIO_INSTANCE 1 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP19_GPIO_PORT_PIN 2 // Port Pin Number
#define ECP19_TRIS    TRISAbits.TRISA2 // GPIO direction register bit
#define ECP19_WR      LATAbits.LATA2 // GPIO port latch register bit
#define ECP19_RD      PORTAbits.RA2 // GPIO port register bit
#define ECP19_ODC     ODCAbits.ODCA2 // GPIO port open drain configuration register bit
#define ECP19_CNPU    CNPUAbits.CNPUA2 // GPIO port pull-up resistor register bit
#define ECP19_CNPD    CNPDAbits.CNPDA2 // GPIO port pull-down resistor register bit
#define ECP19_CNEN0   CNEN0Abits.CNEN0A2 // GPIO port change notification Enable register bit
#define ECP19_CNSTAT  CNSTATAbits.CNSTATA2 // GPIO port change notification Status register bit
#define ECP19_CNEN1   CNEN1Abits.CNEN1A2 // GPIO port change notification Edge Select Enable register bit
#define ECP19_CNF     CNFAbits.CNFA2 // GPIO port change notification flag bit register bit
#define ECP19_SET     { asm volatile ("bset _LATA, #2 \n"); }
#define ECP19_CLEAR   { asm volatile ("bclr _LATA, #2 \n"); }
#define ECP19_TOGGLE  { asm volatile ("btg  _LATA, #2 \n"); }
#define ECP19_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP19_ANSEL   _ANSELA2 // analog/digital pin configuration register bit
#define ECP19_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP19_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP19_ADCAN   9   // ANx input pin number
#define ECP19_ADCBUF  ADCBUF9 // ADC buffer register for this input
#define ECP19_ADIE_IEx ADIELbits.IE9
#define ECP19_ADEIE_EIEx ADEIELbits.EIEN9
#define ECP19_ADCANxIF  _ADCAN9IF // interrupt flag bit
#define ECP19_ADCANxIE  _ADCAN9IE // interrupt enable bit
#define ECP19_ADCANxIP  _ADCAN9IP // interrupt priority for this analog input
#define ECP19_ANxRDY    _AN9RDY // ADC buffer ready bit
#define _ECP19_ADCANxInterrupt _ADCAN9Interrupt
#define ECP19_ANxTRGSRC _TRGSRC9 // ADC input trigger source register
#define ECP19_INIT_ANALOG	{ECP19_ANSEL = 1; ECP19_WR = PINSTATE_HIGH; ECP19_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP19_DISPOSE      {ECP19_WR = PINSTATE_HIGH; ECP19_TRIS = PINDIR_INPUT; ECP19_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP19_INIT_OUTPUT  {ECP19_WR = PINSTATE_LOW; ECP19_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP19_INIT_INPUT   {ECP19_WR = PINSTATE_HIGH; ECP19_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #29 is RB1
#define ECP20_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP20_GPIO_PORT_PIN 1 // Port Pin Number
#define ECP20_TRIS    TRISBbits.TRISB1 // GPIO direction register bit
#define ECP20_WR      LATBbits.LATB1 // GPIO port latch register bit
#define ECP20_RD      PORTBbits.RB1 // GPIO port register bit
#define ECP20_ODC     ODCBbits.ODCB1 // GPIO port open drain configuration register bit
#define ECP20_CNPU    CNPUBbits.CNPUB1 // GPIO port pull-up resistor register bit
#define ECP20_CNPD    CNPDBbits.CNPDB1 // GPIO port pull-down resistor register bit
#define ECP20_CNEN0   CNEN0Bbits.CNEN0B1 // GPIO port change notification Enable register bit
#define ECP20_CNSTAT  CNSTATBbits.CNSTATB1 // GPIO port change notification Status register bit
#define ECP20_CNEN1   CNEN1Bbits.CNEN1B1 // GPIO port change notification Edge Select Enable register bit
#define ECP20_CNF     CNFBbits.CNFB1 // GPIO port change notification flag bit register bit
#define ECP20_RP      33 // Number of Remappable Pin
#define _ECP20_RPxR    _RP33R // Remappable Pin Register
#define ECP20_SET     { asm volatile ("bset _LATB, #1 \n"); }
#define ECP20_CLEAR   { asm volatile ("bclr _LATB, #1 \n"); }
#define ECP20_TOGGLE  { asm volatile ("btg  _LATB, #1 \n"); }
#define ECP20_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP20_ANSEL   _ANSELB1 // analog/digital pin configuration register bit
#define ECP20_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP20_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP20_ADCAN   6   // ANx input pin number
#define ECP20_ADCBUF  ADCBUF6 // ADC buffer register for this input
#define ECP20_ADIE_IEx ADIELbits.IE6
#define ECP20_ADEIE_EIEx ADEIELbits.EIEN6
#define ECP20_ADCANxIF  _ADCAN6IF // interrupt flag bit
#define ECP20_ADCANxIE  _ADCAN6IE // interrupt enable bit
#define ECP20_ADCANxIP  _ADCAN6IP // interrupt priority for this analog input
#define ECP20_ANxRDY    _AN6RDY // ADC buffer ready bit
#define _ECP20_ADCANxInterrupt _ADCAN6Interrupt
#define ECP20_ANxTRGSRC _TRGSRC6 // ADC input trigger source register
#define ECP20_INIT_ANALOG	{ECP20_ANSEL = 1; ECP20_WR = PINSTATE_HIGH; ECP20_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP20_DISPOSE      {ECP20_WR = PINSTATE_HIGH; ECP20_TRIS = PINDIR_INPUT; ECP20_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP20_INIT_OUTPUT  {ECP20_WR = PINSTATE_LOW; ECP20_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP20_INIT_INPUT   {ECP20_WR = PINSTATE_HIGH; ECP20_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #49 is RB9
#define ECP23_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP23_GPIO_PORT_PIN 9 // Port Pin Number
#define ECP23_TRIS    TRISBbits.TRISB9 // GPIO direction register bit
#define ECP23_WR      LATBbits.LATB9 // GPIO port latch register bit
#define ECP23_RD      PORTBbits.RB9 // GPIO port register bit
#define ECP23_ODC     ODCBbits.ODCB9 // GPIO port open drain configuration register bit
#define ECP23_CNPU    CNPUBbits.CNPUB9 // GPIO port pull-up resistor register bit
#define ECP23_CNPD    CNPDBbits.CNPDB9 // GPIO port pull-down resistor register bit
#define ECP23_CNEN0   CNEN0Bbits.CNEN0B9 // GPIO port change notification Enable register bit
#define ECP23_CNSTAT  CNSTATBbits.CNSTATB9 // GPIO port change notification Status register bit
#define ECP23_CNEN1   CNEN1Bbits.CNEN1B9 // GPIO port change notification Edge Select Enable register bit
#define ECP23_CNF     CNFBbits.CNFB9 // GPIO port change notification flag bit register bit
#define ECP23_RP      41 // Number of Remappable Pin
#define _ECP23_RPxR    _RP41R // Remappable Pin Register
#define ECP23_SET     { asm volatile ("bset _LATB, #9 \n"); }
#define ECP23_CLEAR   { asm volatile ("bclr _LATB, #9 \n"); }
#define ECP23_TOGGLE  { asm volatile ("btg  _LATB, #9 \n"); }
#define ECP23_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP23_ANSEL   _ANSELB9 // analog/digital pin configuration register bit
#define ECP23_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP23_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP23_ADCAN   11   // ANx input pin number
#define ECP23_ADCBUF  ADCBUF11 // ADC buffer register for this input
#define ECP23_ADIE_IEx ADIELbits.IE11
#define ECP23_ADEIE_EIEx ADEIELbits.EIEN11
#define ECP23_ADCANxIF  _ADCAN11IF // interrupt flag bit
#define ECP23_ADCANxIE  _ADCAN11IE // interrupt enable bit
#define ECP23_ADCANxIP  _ADCAN11IP // interrupt priority for this analog input
#define ECP23_ANxRDY    _AN11RDY // ADC buffer ready bit
#define _ECP23_ADCANxInterrupt _ADCAN11Interrupt
#define ECP23_ANxTRGSRC _TRGSRC11 // ADC input trigger source register
#define ECP23_INIT_ANALOG	{ECP23_ANSEL = 1; ECP23_WR = PINSTATE_HIGH; ECP23_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP23_DISPOSE      {ECP23_WR = PINSTATE_HIGH; ECP23_TRIS = PINDIR_INPUT; ECP23_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP23_INIT_OUTPUT  {ECP23_WR = PINSTATE_LOW; ECP23_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP23_INIT_INPUT   {ECP23_WR = PINSTATE_HIGH; ECP23_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #36 is RC8
#define ECP24_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP24_GPIO_PORT_PIN 8 // Port Pin Number
#define ECP24_TRIS    TRISCbits.TRISC8 // GPIO direction register bit
#define ECP24_WR      LATCbits.LATC8 // GPIO port latch register bit
#define ECP24_RD      PORTCbits.RC8 // GPIO port register bit
#define ECP24_ODC     ODCCbits.ODCC8 // GPIO port open drain configuration register bit
#define ECP24_CNPU    CNPUCbits.CNPUC8 // GPIO port pull-up resistor register bit
#define ECP24_CNPD    CNPDCbits.CNPDC8 // GPIO port pull-down resistor register bit
#define ECP24_CNEN0   CNEN0Cbits.CNEN0C8 // GPIO port change notification Enable register bit
#define ECP24_CNSTAT  CNSTATCbits.CNSTATC8 // GPIO port change notification Status register bit
#define ECP24_CNEN1   CNEN1Cbits.CNEN1C8 // GPIO port change notification Edge Select Enable register bit
#define ECP24_CNF     CNFCbits.CNFC8 // GPIO port change notification flag bit register bit
#define ECP24_RP      56 // Number of Remappable Pin
#define _ECP24_RPxR    _RP56R // Remappable Pin Register
#define ECP24_SET     { asm volatile ("bset _LATC, #8 \n"); }
#define ECP24_CLEAR   { asm volatile ("bclr _LATC, #8 \n"); }
#define ECP24_TOGGLE  { asm volatile ("btg  _LATC, #8 \n"); }
#define ECP24_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP24_DISPOSE      {ECP24_WR = PINSTATE_HIGH; ECP24_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP24_INIT_OUTPUT  {ECP24_WR = PINSTATE_LOW; ECP24_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP24_INIT_INPUT   {ECP24_WR = PINSTATE_HIGH; ECP24_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #52 is RC10
#define ECP25_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP25_GPIO_PORT_PIN 10 // Port Pin Number
#define ECP25_TRIS    TRISCbits.TRISC10 // GPIO direction register bit
#define ECP25_WR      LATCbits.LATC10 // GPIO port latch register bit
#define ECP25_RD      PORTCbits.RC10 // GPIO port register bit
#define ECP25_ODC     ODCCbits.ODCC10 // GPIO port open drain configuration register bit
#define ECP25_CNPU    CNPUCbits.CNPUC10 // GPIO port pull-up resistor register bit
#define ECP25_CNPD    CNPDCbits.CNPDC10 // GPIO port pull-down resistor register bit
#define ECP25_CNEN0   CNEN0Cbits.CNEN0C10 // GPIO port change notification Enable register bit
#define ECP25_CNSTAT  CNSTATCbits.CNSTATC10 // GPIO port change notification Status register bit
#define ECP25_CNEN1   CNEN1Cbits.CNEN1C10 // GPIO port change notification Edge Select Enable register bit
#define ECP25_CNF     CNFCbits.CNFC10 // GPIO port change notification flag bit register bit
#define ECP25_RP      58 // Number of Remappable Pin
#define _ECP25_RPxR    _RP58R // Remappable Pin Register
#define ECP25_SET     { asm volatile ("bset _LATC, #10 \n"); }
#define ECP25_CLEAR   { asm volatile ("bclr _LATC, #10 \n"); }
#define ECP25_TOGGLE  { asm volatile ("btg  _LATC, #10 \n"); }
#define ECP25_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP25_DISPOSE      {ECP25_WR = PINSTATE_HIGH; ECP25_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP25_INIT_OUTPUT  {ECP25_WR = PINSTATE_LOW; ECP25_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP25_INIT_INPUT   {ECP25_WR = PINSTATE_HIGH; ECP25_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP25_PGxCHANNEL  7 // PWM channel index
#define ECP25_PGxPER      PG7PER // PWM channel period register
#define ECP25_PGxPHASE    PG7PHASE // PWM channel phase register
#define ECP25_PGxDC       PG7DC // PWM channel duty cycle register
#define ECP25_PGxDCA      PG7DCA// PWM channel duty cycle A register
#define ECP25_PGxDTH      PG7DTH // PWM channel rising edge dead time register
#define ECP25_PGxDTL      PG7DTL // PWM channel falling edge dead time register
#define ECP25_PGx_OVRENH   PG7IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP25_PGx_PENH     PG7IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP25_PGxUPDREQ    PG7STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP25_PGxTRIGA     PG7TRIGA // PWM channel ADC trigger A register
#define ECP25_PGxTRIGB     PG7TRIGB // PWM channel ADC trigger A register
#define ECP25_PGxTRIGC     PG7TRIGC // PWM channel ADC trigger A register
#define ECP25_PWMxIF       _PWM7IF // interrupt flag bit
#define ECP25_PWMxIE       _PWM7IE // interrupt enable bit
#define ECP25_PWMxIP       _PWM7IP // interrupt priority for this analog input
#define _ECP25_PWMxInterrupt _PWM7Interrupt // Interrupt Service Routine name declaration
#define ECP25_TRGSRC_PWMxTRG1   TRGSRC_PWM7_TRG1 // PWM channel trigger 1
#define ECP25_TRGSRC_PWMxTRG2   TRGSRC_PWM7_TRG2 // PWM channel trigger 2

// Device Pin #11 is RD14
#define ECP26_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP26_GPIO_PORT_PIN 14 // Port Pin Number
#define ECP26_TRIS    TRISDbits.TRISD14 // GPIO direction register bit
#define ECP26_WR      LATDbits.LATD14 // GPIO port latch register bit
#define ECP26_RD      PORTDbits.RD14 // GPIO port register bit
#define ECP26_ODC     ODCDbits.ODCD14 // GPIO port open drain configuration register bit
#define ECP26_CNPU    CNPUDbits.CNPUD14 // GPIO port pull-up resistor register bit
#define ECP26_CNPD    CNPDDbits.CNPDD14 // GPIO port pull-down resistor register bit
#define ECP26_CNEN0   CNEN0Dbits.CNEN0D14 // GPIO port change notification Enable register bit
#define ECP26_CNSTAT  CNSTATDbits.CNSTATD14 // GPIO port change notification Status register bit
#define ECP26_CNEN1   CNEN1Dbits.CNEN1D14 // GPIO port change notification Edge Select Enable register bit
#define ECP26_CNF     CNFDbits.CNFD14 // GPIO port change notification flag bit register bit
#define ECP26_RP      78 // Number of Remappable Pin
#define _ECP26_RPxR    _RP78R // Remappable Pin Register
#define ECP26_SET     { asm volatile ("bset _LATD, #14 \n"); }
#define ECP26_CLEAR   { asm volatile ("bclr _LATD, #14 \n"); }
#define ECP26_TOGGLE  { asm volatile ("btg  _LATD, #14 \n"); }
#define ECP26_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP26_DISPOSE      {ECP26_WR = PINSTATE_HIGH; ECP26_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP26_INIT_OUTPUT  {ECP26_WR = PINSTATE_LOW; ECP26_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP26_INIT_INPUT   {ECP26_WR = PINSTATE_HIGH; ECP26_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #53 is RC11
#define ECP27_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP27_GPIO_PORT_PIN 11 // Port Pin Number
#define ECP27_TRIS    TRISCbits.TRISC11 // GPIO direction register bit
#define ECP27_WR      LATCbits.LATC11 // GPIO port latch register bit
#define ECP27_RD      PORTCbits.RC11 // GPIO port register bit
#define ECP27_ODC     ODCCbits.ODCC11 // GPIO port open drain configuration register bit
#define ECP27_CNPU    CNPUCbits.CNPUC11 // GPIO port pull-up resistor register bit
#define ECP27_CNPD    CNPDCbits.CNPDC11 // GPIO port pull-down resistor register bit
#define ECP27_CNEN0   CNEN0Cbits.CNEN0C11 // GPIO port change notification Enable register bit
#define ECP27_CNSTAT  CNSTATCbits.CNSTATC11 // GPIO port change notification Status register bit
#define ECP27_CNEN1   CNEN1Cbits.CNEN1C11 // GPIO port change notification Edge Select Enable register bit
#define ECP27_CNF     CNFCbits.CNFC11 // GPIO port change notification flag bit register bit
#define ECP27_RP      59 // Number of Remappable Pin
#define _ECP27_RPxR    _RP59R // Remappable Pin Register
#define ECP27_SET     { asm volatile ("bset _LATC, #11 \n"); }
#define ECP27_CLEAR   { asm volatile ("bclr _LATC, #11 \n"); }
#define ECP27_TOGGLE  { asm volatile ("btg  _LATC, #11 \n"); }
#define ECP27_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP27_DISPOSE      {ECP27_WR = PINSTATE_HIGH; ECP27_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP27_INIT_OUTPUT  {ECP27_WR = PINSTATE_LOW; ECP27_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP27_INIT_INPUT   {ECP27_WR = PINSTATE_HIGH; ECP27_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP27_PGxCHANNEL  7 // PWM channel index
#define ECP27_PGxPER      PG7PER // PWM channel period register
#define ECP27_PGxPHASE    PG7PHASE // PWM channel phase register
#define ECP27_PGxDC       PG7DC // PWM channel duty cycle register
#define ECP27_PGxDCA      PG7DCA// PWM channel duty cycle A register
#define ECP27_PGxDTH      PG7DTH // PWM channel rising edge dead time register
#define ECP27_PGxDTL      PG7DTL // PWM channel falling edge dead time register
#define ECP27_PGx_OVRENL   PG7IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP27_PGx_PENL     PG7IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP27_PGxUPDREQ    PG7STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP27_PGxTRIGA     PG7TRIGA // PWM channel ADC trigger A register
#define ECP27_PGxTRIGB     PG7TRIGB // PWM channel ADC trigger A register
#define ECP27_PGxTRIGC     PG7TRIGC // PWM channel ADC trigger A register

// Device Pin #38 is RD9
#define ECP28_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP28_GPIO_PORT_PIN 9 // Port Pin Number
#define ECP28_TRIS    TRISDbits.TRISD9 // GPIO direction register bit
#define ECP28_WR      LATDbits.LATD9 // GPIO port latch register bit
#define ECP28_RD      PORTDbits.RD9 // GPIO port register bit
#define ECP28_ODC     ODCDbits.ODCD9 // GPIO port open drain configuration register bit
#define ECP28_CNPU    CNPUDbits.CNPUD9 // GPIO port pull-up resistor register bit
#define ECP28_CNPD    CNPDDbits.CNPDD9 // GPIO port pull-down resistor register bit
#define ECP28_CNEN0   CNEN0Dbits.CNEN0D9 // GPIO port change notification Enable register bit
#define ECP28_CNSTAT  CNSTATDbits.CNSTATD9 // GPIO port change notification Status register bit
#define ECP28_CNEN1   CNEN1Dbits.CNEN1D9 // GPIO port change notification Edge Select Enable register bit
#define ECP28_CNF     CNFDbits.CNFD9 // GPIO port change notification flag bit register bit
#define ECP28_RP      73 // Number of Remappable Pin
#define _ECP28_RPxR    _RP73R // Remappable Pin Register
#define ECP28_SET     { asm volatile ("bset _LATD, #9 \n"); }
#define ECP28_CLEAR   { asm volatile ("bclr _LATD, #9 \n"); }
#define ECP28_TOGGLE  { asm volatile ("btg  _LATD, #9 \n"); }
#define ECP28_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP28_DISPOSE      {ECP28_WR = PINSTATE_HIGH; ECP28_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP28_INIT_OUTPUT  {ECP28_WR = PINSTATE_LOW; ECP28_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP28_INIT_INPUT   {ECP28_WR = PINSTATE_HIGH; ECP28_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #5 is RC14
#define ECP31_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP31_GPIO_PORT_PIN 14 // Port Pin Number
#define ECP31_TRIS    TRISCbits.TRISC14 // GPIO direction register bit
#define ECP31_WR      LATCbits.LATC14 // GPIO port latch register bit
#define ECP31_RD      PORTCbits.RC14 // GPIO port register bit
#define ECP31_ODC     ODCCbits.ODCC14 // GPIO port open drain configuration register bit
#define ECP31_CNPU    CNPUCbits.CNPUC14 // GPIO port pull-up resistor register bit
#define ECP31_CNPD    CNPDCbits.CNPDC14 // GPIO port pull-down resistor register bit
#define ECP31_CNEN0   CNEN0Cbits.CNEN0C14 // GPIO port change notification Enable register bit
#define ECP31_CNSTAT  CNSTATCbits.CNSTATC14 // GPIO port change notification Status register bit
#define ECP31_CNEN1   CNEN1Cbits.CNEN1C14 // GPIO port change notification Edge Select Enable register bit
#define ECP31_CNF     CNFCbits.CNFC14 // GPIO port change notification flag bit register bit
#define ECP31_RP      62 // Number of Remappable Pin
#define _ECP31_RPxR    _RP62R // Remappable Pin Register
#define ECP31_SET     { asm volatile ("bset _LATC, #14 \n"); }
#define ECP31_CLEAR   { asm volatile ("bclr _LATC, #14 \n"); }
#define ECP31_TOGGLE  { asm volatile ("btg  _LATC, #14 \n"); }
#define ECP31_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP31_DISPOSE      {ECP31_WR = PINSTATE_HIGH; ECP31_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP31_INIT_OUTPUT  {ECP31_WR = PINSTATE_LOW; ECP31_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP31_INIT_INPUT   {ECP31_WR = PINSTATE_HIGH; ECP31_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP31_PGxCHANNEL  6 // PWM channel index
#define ECP31_PGxPER      PG6PER // PWM channel period register
#define ECP31_PGxPHASE    PG6PHASE // PWM channel phase register
#define ECP31_PGxDC       PG6DC // PWM channel duty cycle register
#define ECP31_PGxDCA      PG6DCA// PWM channel duty cycle A register
#define ECP31_PGxDTH      PG6DTH // PWM channel rising edge dead time register
#define ECP31_PGxDTL      PG6DTL // PWM channel falling edge dead time register
#define ECP31_PGx_OVRENH   PG6IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP31_PGx_PENH     PG6IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP31_PGxUPDREQ    PG6STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP31_PGxTRIGA     PG6TRIGA // PWM channel ADC trigger A register
#define ECP31_PGxTRIGB     PG6TRIGB // PWM channel ADC trigger A register
#define ECP31_PGxTRIGC     PG6TRIGC // PWM channel ADC trigger A register
#define ECP31_PWMxIF       _PWM6IF // interrupt flag bit
#define ECP31_PWMxIE       _PWM6IE // interrupt enable bit
#define ECP31_PWMxIP       _PWM6IP // interrupt priority for this analog input
#define _ECP31_PWMxInterrupt _PWM6Interrupt // Interrupt Service Routine name declaration
#define ECP31_TRGSRC_PWMxTRG1   TRGSRC_PWM6_TRG1 // PWM channel trigger 1
#define ECP31_TRGSRC_PWMxTRG2   TRGSRC_PWM6_TRG2 // PWM channel trigger 2

// Device Pin #37 is RC9
#define ECP32_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP32_GPIO_PORT_PIN 9 // Port Pin Number
#define ECP32_TRIS    TRISCbits.TRISC9 // GPIO direction register bit
#define ECP32_WR      LATCbits.LATC9 // GPIO port latch register bit
#define ECP32_RD      PORTCbits.RC9 // GPIO port register bit
#define ECP32_ODC     ODCCbits.ODCC9 // GPIO port open drain configuration register bit
#define ECP32_CNPU    CNPUCbits.CNPUC9 // GPIO port pull-up resistor register bit
#define ECP32_CNPD    CNPDCbits.CNPDC9 // GPIO port pull-down resistor register bit
#define ECP32_CNEN0   CNEN0Cbits.CNEN0C9 // GPIO port change notification Enable register bit
#define ECP32_CNSTAT  CNSTATCbits.CNSTATC9 // GPIO port change notification Status register bit
#define ECP32_CNEN1   CNEN1Cbits.CNEN1C9 // GPIO port change notification Edge Select Enable register bit
#define ECP32_CNF     CNFCbits.CNFC9 // GPIO port change notification flag bit register bit
#define ECP32_RP      57 // Number of Remappable Pin
#define _ECP32_RPxR    _RP57R // Remappable Pin Register
#define ECP32_SET     { asm volatile ("bset _LATC, #9 \n"); }
#define ECP32_CLEAR   { asm volatile ("bclr _LATC, #9 \n"); }
#define ECP32_TOGGLE  { asm volatile ("btg  _LATC, #9 \n"); }
#define ECP32_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP32_DISPOSE      {ECP32_WR = PINSTATE_HIGH; ECP32_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP32_INIT_OUTPUT  {ECP32_WR = PINSTATE_LOW; ECP32_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP32_INIT_INPUT   {ECP32_WR = PINSTATE_HIGH; ECP32_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #6 is RC15
#define ECP33_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP33_GPIO_PORT_PIN 15 // Port Pin Number
#define ECP33_TRIS    TRISCbits.TRISC15 // GPIO direction register bit
#define ECP33_WR      LATCbits.LATC15 // GPIO port latch register bit
#define ECP33_RD      PORTCbits.RC15 // GPIO port register bit
#define ECP33_ODC     ODCCbits.ODCC15 // GPIO port open drain configuration register bit
#define ECP33_CNPU    CNPUCbits.CNPUC15 // GPIO port pull-up resistor register bit
#define ECP33_CNPD    CNPDCbits.CNPDC15 // GPIO port pull-down resistor register bit
#define ECP33_CNEN0   CNEN0Cbits.CNEN0C15 // GPIO port change notification Enable register bit
#define ECP33_CNSTAT  CNSTATCbits.CNSTATC15 // GPIO port change notification Status register bit
#define ECP33_CNEN1   CNEN1Cbits.CNEN1C15 // GPIO port change notification Edge Select Enable register bit
#define ECP33_CNF     CNFCbits.CNFC15 // GPIO port change notification flag bit register bit
#define ECP33_RP      63 // Number of Remappable Pin
#define _ECP33_RPxR    _RP63R // Remappable Pin Register
#define ECP33_SET     { asm volatile ("bset _LATC, #15 \n"); }
#define ECP33_CLEAR   { asm volatile ("bclr _LATC, #15 \n"); }
#define ECP33_TOGGLE  { asm volatile ("btg  _LATC, #15 \n"); }
#define ECP33_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP33_DISPOSE      {ECP33_WR = PINSTATE_HIGH; ECP33_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP33_INIT_OUTPUT  {ECP33_WR = PINSTATE_LOW; ECP33_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP33_INIT_INPUT   {ECP33_WR = PINSTATE_HIGH; ECP33_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP33_PGxCHANNEL  6 // PWM channel index
#define ECP33_PGxPER      PG6PER // PWM channel period register
#define ECP33_PGxPHASE    PG6PHASE // PWM channel phase register
#define ECP33_PGxDC       PG6DC // PWM channel duty cycle register
#define ECP33_PGxDCA      PG6DCA// PWM channel duty cycle A register
#define ECP33_PGxDTH      PG6DTH // PWM channel rising edge dead time register
#define ECP33_PGxDTL      PG6DTL // PWM channel falling edge dead time register
#define ECP33_PGx_OVRENL   PG6IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP33_PGx_PENL     PG6IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP33_PGxUPDREQ    PG6STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP33_PGxTRIGA     PG6TRIGA // PWM channel ADC trigger A register
#define ECP33_PGxTRIGB     PG6TRIGB // PWM channel ADC trigger A register
#define ECP33_PGxTRIGC     PG6TRIGC // PWM channel ADC trigger A register

// Device Pin #44 is RD5
#define ECP34_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP34_GPIO_PORT_PIN 5 // Port Pin Number
#define ECP34_TRIS    TRISDbits.TRISD5 // GPIO direction register bit
#define ECP34_WR      LATDbits.LATD5 // GPIO port latch register bit
#define ECP34_RD      PORTDbits.RD5 // GPIO port register bit
#define ECP34_ODC     ODCDbits.ODCD5 // GPIO port open drain configuration register bit
#define ECP34_CNPU    CNPUDbits.CNPUD5 // GPIO port pull-up resistor register bit
#define ECP34_CNPD    CNPDDbits.CNPDD5 // GPIO port pull-down resistor register bit
#define ECP34_CNEN0   CNEN0Dbits.CNEN0D5 // GPIO port change notification Enable register bit
#define ECP34_CNSTAT  CNSTATDbits.CNSTATD5 // GPIO port change notification Status register bit
#define ECP34_CNEN1   CNEN1Dbits.CNEN1D5 // GPIO port change notification Edge Select Enable register bit
#define ECP34_CNF     CNFDbits.CNFD5 // GPIO port change notification flag bit register bit
#define ECP34_RP      69 // Number of Remappable Pin
#define _ECP34_RPxR    _RP69R // Remappable Pin Register
#define ECP34_SET     { asm volatile ("bset _LATD, #5 \n"); }
#define ECP34_CLEAR   { asm volatile ("bclr _LATD, #5 \n"); }
#define ECP34_TOGGLE  { asm volatile ("btg  _LATD, #5 \n"); }
#define ECP34_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP34_DISPOSE      {ECP34_WR = PINSTATE_HIGH; ECP34_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP34_INIT_OUTPUT  {ECP34_WR = PINSTATE_LOW; ECP34_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP34_INIT_INPUT   {ECP34_WR = PINSTATE_HIGH; ECP34_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #50 is RC4
#define ECP35_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP35_GPIO_PORT_PIN 4 // Port Pin Number
#define ECP35_TRIS    TRISCbits.TRISC4 // GPIO direction register bit
#define ECP35_WR      LATCbits.LATC4 // GPIO port latch register bit
#define ECP35_RD      PORTCbits.RC4 // GPIO port register bit
#define ECP35_ODC     ODCCbits.ODCC4 // GPIO port open drain configuration register bit
#define ECP35_CNPU    CNPUCbits.CNPUC4 // GPIO port pull-up resistor register bit
#define ECP35_CNPD    CNPDCbits.CNPDC4 // GPIO port pull-down resistor register bit
#define ECP35_CNEN0   CNEN0Cbits.CNEN0C4 // GPIO port change notification Enable register bit
#define ECP35_CNSTAT  CNSTATCbits.CNSTATC4 // GPIO port change notification Status register bit
#define ECP35_CNEN1   CNEN1Cbits.CNEN1C4 // GPIO port change notification Edge Select Enable register bit
#define ECP35_CNF     CNFCbits.CNFC4 // GPIO port change notification flag bit register bit
#define ECP35_RP      52 // Number of Remappable Pin
#define _ECP35_RPxR    _RP52R // Remappable Pin Register
#define ECP35_SET     { asm volatile ("bset _LATC, #4 \n"); }
#define ECP35_CLEAR   { asm volatile ("bclr _LATC, #4 \n"); }
#define ECP35_TOGGLE  { asm volatile ("btg  _LATC, #4 \n"); }
#define ECP35_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP35_DISPOSE      {ECP35_WR = PINSTATE_HIGH; ECP35_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP35_INIT_OUTPUT  {ECP35_WR = PINSTATE_LOW; ECP35_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP35_INIT_INPUT   {ECP35_WR = PINSTATE_HIGH; ECP35_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP35_PGxCHANNEL  5 // PWM channel index
#define ECP35_PGxPER      PG5PER // PWM channel period register
#define ECP35_PGxPHASE    PG5PHASE // PWM channel phase register
#define ECP35_PGxDC       PG5DC // PWM channel duty cycle register
#define ECP35_PGxDCA      PG5DCA// PWM channel duty cycle A register
#define ECP35_PGxDTH      PG5DTH // PWM channel rising edge dead time register
#define ECP35_PGxDTL      PG5DTL // PWM channel falling edge dead time register
#define ECP35_PGx_OVRENH   PG5IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP35_PGx_PENH     PG5IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP35_PGxUPDREQ    PG5STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP35_PGxTRIGA     PG5TRIGA // PWM channel ADC trigger A register
#define ECP35_PGxTRIGB     PG5TRIGB // PWM channel ADC trigger A register
#define ECP35_PGxTRIGC     PG5TRIGC // PWM channel ADC trigger A register
#define ECP35_PWMxIF       _PWM5IF // interrupt flag bit
#define ECP35_PWMxIE       _PWM5IE // interrupt enable bit
#define ECP35_PWMxIP       _PWM5IP // interrupt priority for this analog input
#define _ECP35_PWMxInterrupt _PWM5Interrupt // Interrupt Service Routine name declaration
#define ECP35_TRGSRC_PWMxTRG1   TRGSRC_PWM5_TRG1 // PWM channel trigger 1
#define ECP35_TRGSRC_PWMxTRG2   TRGSRC_PWM5_TRG2 // PWM channel trigger 2

// Device Pin #43 is RD6
#define ECP36_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP36_GPIO_PORT_PIN 6 // Port Pin Number
#define ECP36_TRIS    TRISDbits.TRISD6 // GPIO direction register bit
#define ECP36_WR      LATDbits.LATD6 // GPIO port latch register bit
#define ECP36_RD      PORTDbits.RD6 // GPIO port register bit
#define ECP36_ODC     ODCDbits.ODCD6 // GPIO port open drain configuration register bit
#define ECP36_CNPU    CNPUDbits.CNPUD6 // GPIO port pull-up resistor register bit
#define ECP36_CNPD    CNPDDbits.CNPDD6 // GPIO port pull-down resistor register bit
#define ECP36_CNEN0   CNEN0Dbits.CNEN0D6 // GPIO port change notification Enable register bit
#define ECP36_CNSTAT  CNSTATDbits.CNSTATD6 // GPIO port change notification Status register bit
#define ECP36_CNEN1   CNEN1Dbits.CNEN1D6 // GPIO port change notification Edge Select Enable register bit
#define ECP36_CNF     CNFDbits.CNFD6 // GPIO port change notification flag bit register bit
#define ECP36_RP      70 // Number of Remappable Pin
#define _ECP36_RPxR    _RP70R // Remappable Pin Register
#define ECP36_SET     { asm volatile ("bset _LATD, #6 \n"); }
#define ECP36_CLEAR   { asm volatile ("bclr _LATD, #6 \n"); }
#define ECP36_TOGGLE  { asm volatile ("btg  _LATD, #6 \n"); }
#define ECP36_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP36_DISPOSE      {ECP36_WR = PINSTATE_HIGH; ECP36_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP36_INIT_OUTPUT  {ECP36_WR = PINSTATE_LOW; ECP36_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP36_INIT_INPUT   {ECP36_WR = PINSTATE_HIGH; ECP36_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #61 is RB10
#define ECP37_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP37_GPIO_PORT_PIN 10 // Port Pin Number
#define ECP37_TRIS    TRISBbits.TRISB10 // GPIO direction register bit
#define ECP37_WR      LATBbits.LATB10 // GPIO port latch register bit
#define ECP37_RD      PORTBbits.RB10 // GPIO port register bit
#define ECP37_ODC     ODCBbits.ODCB10 // GPIO port open drain configuration register bit
#define ECP37_CNPU    CNPUBbits.CNPUB10 // GPIO port pull-up resistor register bit
#define ECP37_CNPD    CNPDBbits.CNPDB10 // GPIO port pull-down resistor register bit
#define ECP37_CNEN0   CNEN0Bbits.CNEN0B10 // GPIO port change notification Enable register bit
#define ECP37_CNSTAT  CNSTATBbits.CNSTATB10 // GPIO port change notification Status register bit
#define ECP37_CNEN1   CNEN1Bbits.CNEN1B10 // GPIO port change notification Edge Select Enable register bit
#define ECP37_CNF     CNFBbits.CNFB10 // GPIO port change notification flag bit register bit
#define ECP37_RP      42 // Number of Remappable Pin
#define _ECP37_RPxR    _RP42R // Remappable Pin Register
#define ECP37_SET     { asm volatile ("bset _LATB, #10 \n"); }
#define ECP37_CLEAR   { asm volatile ("bclr _LATB, #10 \n"); }
#define ECP37_TOGGLE  { asm volatile ("btg  _LATB, #10 \n"); }
#define ECP37_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP37_DISPOSE      {ECP37_WR = PINSTATE_HIGH; ECP37_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP37_INIT_OUTPUT  {ECP37_WR = PINSTATE_LOW; ECP37_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP37_INIT_INPUT   {ECP37_WR = PINSTATE_HIGH; ECP37_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP37_PGxCHANNEL  3 // PWM channel index
#define ECP37_PGxPER      PG3PER // PWM channel period register
#define ECP37_PGxPHASE    PG3PHASE // PWM channel phase register
#define ECP37_PGxDC       PG3DC // PWM channel duty cycle register
#define ECP37_PGxDCA      PG3DCA// PWM channel duty cycle A register
#define ECP37_PGxDTH      PG3DTH // PWM channel rising edge dead time register
#define ECP37_PGxDTL      PG3DTL // PWM channel falling edge dead time register
#define ECP37_PGx_OVRENH   PG3IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP37_PGx_PENH     PG3IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP37_PGxUPDREQ    PG3STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP37_PGxTRIGA     PG3TRIGA // PWM channel ADC trigger A register
#define ECP37_PGxTRIGB     PG3TRIGB // PWM channel ADC trigger A register
#define ECP37_PGxTRIGC     PG3TRIGC // PWM channel ADC trigger A register
#define ECP37_PWMxIF       _PWM3IF // interrupt flag bit
#define ECP37_PWMxIE       _PWM3IE // interrupt enable bit
#define ECP37_PWMxIP       _PWM3IP // interrupt priority for this analog input
#define _ECP37_PWMxInterrupt _PWM3Interrupt // Interrupt Service Routine name declaration
#define ECP37_TRGSRC_PWMxTRG1   TRGSRC_PWM3_TRG1 // PWM channel trigger 1
#define ECP37_TRGSRC_PWMxTRG2   TRGSRC_PWM3_TRG2 // PWM channel trigger 2

// Device Pin #51 is RC5
#define ECP38_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP38_GPIO_PORT_PIN 5 // Port Pin Number
#define ECP38_TRIS    TRISCbits.TRISC5 // GPIO direction register bit
#define ECP38_WR      LATCbits.LATC5 // GPIO port latch register bit
#define ECP38_RD      PORTCbits.RC5 // GPIO port register bit
#define ECP38_ODC     ODCCbits.ODCC5 // GPIO port open drain configuration register bit
#define ECP38_CNPU    CNPUCbits.CNPUC5 // GPIO port pull-up resistor register bit
#define ECP38_CNPD    CNPDCbits.CNPDC5 // GPIO port pull-down resistor register bit
#define ECP38_CNEN0   CNEN0Cbits.CNEN0C5 // GPIO port change notification Enable register bit
#define ECP38_CNSTAT  CNSTATCbits.CNSTATC5 // GPIO port change notification Status register bit
#define ECP38_CNEN1   CNEN1Cbits.CNEN1C5 // GPIO port change notification Edge Select Enable register bit
#define ECP38_CNF     CNFCbits.CNFC5 // GPIO port change notification flag bit register bit
#define ECP38_RP      53 // Number of Remappable Pin
#define _ECP38_RPxR    _RP53R // Remappable Pin Register
#define ECP38_SET     { asm volatile ("bset _LATC, #5 \n"); }
#define ECP38_CLEAR   { asm volatile ("bclr _LATC, #5 \n"); }
#define ECP38_TOGGLE  { asm volatile ("btg  _LATC, #5 \n"); }
#define ECP38_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP38_DISPOSE      {ECP38_WR = PINSTATE_HIGH; ECP38_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP38_INIT_OUTPUT  {ECP38_WR = PINSTATE_LOW; ECP38_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP38_INIT_INPUT   {ECP38_WR = PINSTATE_HIGH; ECP38_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP38_PGxCHANNEL  5 // PWM channel index
#define ECP38_PGxPER      PG5PER // PWM channel period register
#define ECP38_PGxPHASE    PG5PHASE // PWM channel phase register
#define ECP38_PGxDC       PG5DC // PWM channel duty cycle register
#define ECP38_PGxDCA      PG5DCA// PWM channel duty cycle A register
#define ECP38_PGxDTH      PG5DTH // PWM channel rising edge dead time register
#define ECP38_PGxDTL      PG5DTL // PWM channel falling edge dead time register
#define ECP38_PGx_OVRENL   PG5IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP38_PGx_PENL     PG5IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP38_PGxUPDREQ    PG5STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP38_PGxTRIGA     PG5TRIGA // PWM channel ADC trigger A register
#define ECP38_PGxTRIGB     PG5TRIGB // PWM channel ADC trigger A register
#define ECP38_PGxTRIGC     PG5TRIGC // PWM channel ADC trigger A register

// Device Pin #58 is RD2
#define ECP39_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP39_GPIO_PORT_PIN 2 // Port Pin Number
#define ECP39_TRIS    TRISDbits.TRISD2 // GPIO direction register bit
#define ECP39_WR      LATDbits.LATD2 // GPIO port latch register bit
#define ECP39_RD      PORTDbits.RD2 // GPIO port register bit
#define ECP39_ODC     ODCDbits.ODCD2 // GPIO port open drain configuration register bit
#define ECP39_CNPU    CNPUDbits.CNPUD2 // GPIO port pull-up resistor register bit
#define ECP39_CNPD    CNPDDbits.CNPDD2 // GPIO port pull-down resistor register bit
#define ECP39_CNEN0   CNEN0Dbits.CNEN0D2 // GPIO port change notification Enable register bit
#define ECP39_CNSTAT  CNSTATDbits.CNSTATD2 // GPIO port change notification Status register bit
#define ECP39_CNEN1   CNEN1Dbits.CNEN1D2 // GPIO port change notification Edge Select Enable register bit
#define ECP39_CNF     CNFDbits.CNFD2 // GPIO port change notification flag bit register bit
#define ECP39_RP      66 // Number of Remappable Pin
#define _ECP39_RPxR    _RP66R // Remappable Pin Register
#define ECP39_SET     { asm volatile ("bset _LATD, #2 \n"); }
#define ECP39_CLEAR   { asm volatile ("bclr _LATD, #2 \n"); }
#define ECP39_TOGGLE  { asm volatile ("btg  _LATD, #2 \n"); }
#define ECP39_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP39_DISPOSE      {ECP39_WR = PINSTATE_HIGH; ECP39_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP39_INIT_OUTPUT  {ECP39_WR = PINSTATE_LOW; ECP39_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP39_INIT_INPUT   {ECP39_WR = PINSTATE_HIGH; ECP39_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #64 is RB13
#define ECP40_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP40_GPIO_PORT_PIN 13 // Port Pin Number
#define ECP40_TRIS    TRISBbits.TRISB13 // GPIO direction register bit
#define ECP40_WR      LATBbits.LATB13 // GPIO port latch register bit
#define ECP40_RD      PORTBbits.RB13 // GPIO port register bit
#define ECP40_ODC     ODCBbits.ODCB13 // GPIO port open drain configuration register bit
#define ECP40_CNPU    CNPUBbits.CNPUB13 // GPIO port pull-up resistor register bit
#define ECP40_CNPD    CNPDBbits.CNPDB13 // GPIO port pull-down resistor register bit
#define ECP40_CNEN0   CNEN0Bbits.CNEN0B13 // GPIO port change notification Enable register bit
#define ECP40_CNSTAT  CNSTATBbits.CNSTATB13 // GPIO port change notification Status register bit
#define ECP40_CNEN1   CNEN1Bbits.CNEN1B13 // GPIO port change notification Edge Select Enable register bit
#define ECP40_CNF     CNFBbits.CNFB13 // GPIO port change notification flag bit register bit
#define ECP40_RP      45 // Number of Remappable Pin
#define _ECP40_RPxR    _RP45R // Remappable Pin Register
#define ECP40_SET     { asm volatile ("bset _LATB, #13 \n"); }
#define ECP40_CLEAR   { asm volatile ("bclr _LATB, #13 \n"); }
#define ECP40_TOGGLE  { asm volatile ("btg  _LATB, #13 \n"); }
#define ECP40_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP40_DISPOSE      {ECP40_WR = PINSTATE_HIGH; ECP40_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP40_INIT_OUTPUT  {ECP40_WR = PINSTATE_LOW; ECP40_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP40_INIT_INPUT   {ECP40_WR = PINSTATE_HIGH; ECP40_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP40_PGxCHANNEL  2 // PWM channel index
#define ECP40_PGxPER      PG2PER // PWM channel period register
#define ECP40_PGxPHASE    PG2PHASE // PWM channel phase register
#define ECP40_PGxDC       PG2DC // PWM channel duty cycle register
#define ECP40_PGxDCA      PG2DCA// PWM channel duty cycle A register
#define ECP40_PGxDTH      PG2DTH // PWM channel rising edge dead time register
#define ECP40_PGxDTL      PG2DTL // PWM channel falling edge dead time register
#define ECP40_PGx_OVRENL   PG2IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP40_PGx_PENL     PG2IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP40_PGxUPDREQ    PG2STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP40_PGxTRIGA     PG2TRIGA // PWM channel ADC trigger A register
#define ECP40_PGxTRIGB     PG2TRIGB // PWM channel ADC trigger A register
#define ECP40_PGxTRIGC     PG2TRIGC // PWM channel ADC trigger A register

// Device Pin #62 is RB11
#define ECP41_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP41_GPIO_PORT_PIN 11 // Port Pin Number
#define ECP41_TRIS    TRISBbits.TRISB11 // GPIO direction register bit
#define ECP41_WR      LATBbits.LATB11 // GPIO port latch register bit
#define ECP41_RD      PORTBbits.RB11 // GPIO port register bit
#define ECP41_ODC     ODCBbits.ODCB11 // GPIO port open drain configuration register bit
#define ECP41_CNPU    CNPUBbits.CNPUB11 // GPIO port pull-up resistor register bit
#define ECP41_CNPD    CNPDBbits.CNPDB11 // GPIO port pull-down resistor register bit
#define ECP41_CNEN0   CNEN0Bbits.CNEN0B11 // GPIO port change notification Enable register bit
#define ECP41_CNSTAT  CNSTATBbits.CNSTATB11 // GPIO port change notification Status register bit
#define ECP41_CNEN1   CNEN1Bbits.CNEN1B11 // GPIO port change notification Edge Select Enable register bit
#define ECP41_CNF     CNFBbits.CNFB11 // GPIO port change notification flag bit register bit
#define ECP41_RP      43 // Number of Remappable Pin
#define _ECP41_RPxR    _RP43R // Remappable Pin Register
#define ECP41_SET     { asm volatile ("bset _LATB, #11 \n"); }
#define ECP41_CLEAR   { asm volatile ("bclr _LATB, #11 \n"); }
#define ECP41_TOGGLE  { asm volatile ("btg  _LATB, #11 \n"); }
#define ECP41_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP41_DISPOSE      {ECP41_WR = PINSTATE_HIGH; ECP41_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP41_INIT_OUTPUT  {ECP41_WR = PINSTATE_LOW; ECP41_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP41_INIT_INPUT   {ECP41_WR = PINSTATE_HIGH; ECP41_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP41_PGxCHANNEL  3 // PWM channel index
#define ECP41_PGxPER      PG3PER // PWM channel period register
#define ECP41_PGxPHASE    PG3PHASE // PWM channel phase register
#define ECP41_PGxDC       PG3DC // PWM channel duty cycle register
#define ECP41_PGxDCA      PG3DCA// PWM channel duty cycle A register
#define ECP41_PGxDTH      PG3DTH // PWM channel rising edge dead time register
#define ECP41_PGxDTL      PG3DTL // PWM channel falling edge dead time register
#define ECP41_PGx_OVRENL   PG3IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP41_PGx_PENL     PG3IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP41_PGxUPDREQ    PG3STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP41_PGxTRIGA     PG3TRIGA // PWM channel ADC trigger A register
#define ECP41_PGxTRIGB     PG3TRIGB // PWM channel ADC trigger A register
#define ECP41_PGxTRIGC     PG3TRIGC // PWM channel ADC trigger A register

// Device Pin #63 is RB12
#define ECP42_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP42_GPIO_PORT_PIN 12 // Port Pin Number
#define ECP42_TRIS    TRISBbits.TRISB12 // GPIO direction register bit
#define ECP42_WR      LATBbits.LATB12 // GPIO port latch register bit
#define ECP42_RD      PORTBbits.RB12 // GPIO port register bit
#define ECP42_ODC     ODCBbits.ODCB12 // GPIO port open drain configuration register bit
#define ECP42_CNPU    CNPUBbits.CNPUB12 // GPIO port pull-up resistor register bit
#define ECP42_CNPD    CNPDBbits.CNPDB12 // GPIO port pull-down resistor register bit
#define ECP42_CNEN0   CNEN0Bbits.CNEN0B12 // GPIO port change notification Enable register bit
#define ECP42_CNSTAT  CNSTATBbits.CNSTATB12 // GPIO port change notification Status register bit
#define ECP42_CNEN1   CNEN1Bbits.CNEN1B12 // GPIO port change notification Edge Select Enable register bit
#define ECP42_CNF     CNFBbits.CNFB12 // GPIO port change notification flag bit register bit
#define ECP42_RP      44 // Number of Remappable Pin
#define _ECP42_RPxR    _RP44R // Remappable Pin Register
#define ECP42_SET     { asm volatile ("bset _LATB, #12 \n"); }
#define ECP42_CLEAR   { asm volatile ("bclr _LATB, #12 \n"); }
#define ECP42_TOGGLE  { asm volatile ("btg  _LATB, #12 \n"); }
#define ECP42_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP42_DISPOSE      {ECP42_WR = PINSTATE_HIGH; ECP42_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP42_INIT_OUTPUT  {ECP42_WR = PINSTATE_LOW; ECP42_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP42_INIT_INPUT   {ECP42_WR = PINSTATE_HIGH; ECP42_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP42_PGxCHANNEL  2 // PWM channel index
#define ECP42_PGxPER      PG2PER // PWM channel period register
#define ECP42_PGxPHASE    PG2PHASE // PWM channel phase register
#define ECP42_PGxDC       PG2DC // PWM channel duty cycle register
#define ECP42_PGxDCA      PG2DCA// PWM channel duty cycle A register
#define ECP42_PGxDTH      PG2DTH // PWM channel rising edge dead time register
#define ECP42_PGxDTL      PG2DTL // PWM channel falling edge dead time register
#define ECP42_PGx_OVRENH   PG2IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP42_PGx_PENH     PG2IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP42_PGxUPDREQ    PG2STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP42_PGxTRIGA     PG2TRIGA // PWM channel ADC trigger A register
#define ECP42_PGxTRIGB     PG2TRIGB // PWM channel ADC trigger A register
#define ECP42_PGxTRIGC     PG2TRIGC // PWM channel ADC trigger A register
#define ECP42_PWMxIF       _PWM2IF // interrupt flag bit
#define ECP42_PWMxIE       _PWM2IE // interrupt enable bit
#define ECP42_PWMxIP       _PWM2IP // interrupt priority for this analog input
#define _ECP42_PWMxInterrupt _PWM2Interrupt // Interrupt Service Routine name declaration
#define ECP42_TRGSRC_PWMxTRG1   TRGSRC_PWM2_TRG1 // PWM channel trigger 1
#define ECP42_TRGSRC_PWMxTRG2   TRGSRC_PWM2_TRG2 // PWM channel trigger 2

// Device Pin #59 is RD1
#define ECP43_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP43_GPIO_PORT_PIN 1 // Port Pin Number
#define ECP43_TRIS    TRISDbits.TRISD1 // GPIO direction register bit
#define ECP43_WR      LATDbits.LATD1 // GPIO port latch register bit
#define ECP43_RD      PORTDbits.RD1 // GPIO port register bit
#define ECP43_ODC     ODCDbits.ODCD1 // GPIO port open drain configuration register bit
#define ECP43_CNPU    CNPUDbits.CNPUD1 // GPIO port pull-up resistor register bit
#define ECP43_CNPD    CNPDDbits.CNPDD1 // GPIO port pull-down resistor register bit
#define ECP43_CNEN0   CNEN0Dbits.CNEN0D1 // GPIO port change notification Enable register bit
#define ECP43_CNSTAT  CNSTATDbits.CNSTATD1 // GPIO port change notification Status register bit
#define ECP43_CNEN1   CNEN1Dbits.CNEN1D1 // GPIO port change notification Edge Select Enable register bit
#define ECP43_CNF     CNFDbits.CNFD1 // GPIO port change notification flag bit register bit
#define ECP43_RP      65 // Number of Remappable Pin
#define _ECP43_RPxR    _RP65R // Remappable Pin Register
#define ECP43_SET     { asm volatile ("bset _LATD, #1 \n"); }
#define ECP43_CLEAR   { asm volatile ("bclr _LATD, #1 \n"); }
#define ECP43_TOGGLE  { asm volatile ("btg  _LATD, #1 \n"); }
#define ECP43_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP43_DISPOSE      {ECP43_WR = PINSTATE_HIGH; ECP43_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP43_INIT_OUTPUT  {ECP43_WR = PINSTATE_LOW; ECP43_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP43_INIT_INPUT   {ECP43_WR = PINSTATE_HIGH; ECP43_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP43_PGxCHANNEL  4 // PWM channel index
#define ECP43_PGxPER      PG4PER // PWM channel period register
#define ECP43_PGxPHASE    PG4PHASE // PWM channel phase register
#define ECP43_PGxDC       PG4DC // PWM channel duty cycle register
#define ECP43_PGxDCA      PG4DCA// PWM channel duty cycle A register
#define ECP43_PGxDTH      PG4DTH // PWM channel rising edge dead time register
#define ECP43_PGxDTL      PG4DTL // PWM channel falling edge dead time register
#define ECP43_PGx_OVRENH   PG4IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP43_PGx_PENH     PG4IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP43_PGxUPDREQ    PG4STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP43_PGxTRIGA     PG4TRIGA // PWM channel ADC trigger A register
#define ECP43_PGxTRIGB     PG4TRIGB // PWM channel ADC trigger A register
#define ECP43_PGxTRIGC     PG4TRIGC // PWM channel ADC trigger A register
#define ECP43_PWMxIF       _PWM4IF // interrupt flag bit
#define ECP43_PWMxIE       _PWM4IE // interrupt enable bit
#define ECP43_PWMxIP       _PWM4IP // interrupt priority for this analog input
#define _ECP43_PWMxInterrupt _PWM4Interrupt // Interrupt Service Routine name declaration
#define ECP43_TRGSRC_PWMxTRG1   TRGSRC_PWM4_TRG1 // PWM channel trigger 1
#define ECP43_TRGSRC_PWMxTRG2   TRGSRC_PWM4_TRG2 // PWM channel trigger 2

// Device Pin #60 is RD0
#define ECP44_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP44_GPIO_PORT_PIN 0 // Port Pin Number
#define ECP44_TRIS    TRISDbits.TRISD0 // GPIO direction register bit
#define ECP44_WR      LATDbits.LATD0 // GPIO port latch register bit
#define ECP44_RD      PORTDbits.RD0 // GPIO port register bit
#define ECP44_ODC     ODCDbits.ODCD0 // GPIO port open drain configuration register bit
#define ECP44_CNPU    CNPUDbits.CNPUD0 // GPIO port pull-up resistor register bit
#define ECP44_CNPD    CNPDDbits.CNPDD0 // GPIO port pull-down resistor register bit
#define ECP44_CNEN0   CNEN0Dbits.CNEN0D0 // GPIO port change notification Enable register bit
#define ECP44_CNSTAT  CNSTATDbits.CNSTATD0 // GPIO port change notification Status register bit
#define ECP44_CNEN1   CNEN1Dbits.CNEN1D0 // GPIO port change notification Edge Select Enable register bit
#define ECP44_CNF     CNFDbits.CNFD0 // GPIO port change notification flag bit register bit
#define ECP44_RP      64 // Number of Remappable Pin
#define _ECP44_RPxR    _RP64R // Remappable Pin Register
#define ECP44_SET     { asm volatile ("bset _LATD, #0 \n"); }
#define ECP44_CLEAR   { asm volatile ("bclr _LATD, #0 \n"); }
#define ECP44_TOGGLE  { asm volatile ("btg  _LATD, #0 \n"); }
#define ECP44_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP44_DISPOSE      {ECP44_WR = PINSTATE_HIGH; ECP44_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP44_INIT_OUTPUT  {ECP44_WR = PINSTATE_LOW; ECP44_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP44_INIT_INPUT   {ECP44_WR = PINSTATE_HIGH; ECP44_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP44_PGxCHANNEL  4 // PWM channel index
#define ECP44_PGxPER      PG4PER // PWM channel period register
#define ECP44_PGxPHASE    PG4PHASE // PWM channel phase register
#define ECP44_PGxDC       PG4DC // PWM channel duty cycle register
#define ECP44_PGxDCA      PG4DCA// PWM channel duty cycle A register
#define ECP44_PGxDTH      PG4DTH // PWM channel rising edge dead time register
#define ECP44_PGxDTL      PG4DTL // PWM channel falling edge dead time register
#define ECP44_PGx_OVRENL   PG4IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP44_PGx_PENL     PG4IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP44_PGxUPDREQ    PG4STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP44_PGxTRIGA     PG4TRIGA // PWM channel ADC trigger A register
#define ECP44_PGxTRIGB     PG4TRIGB // PWM channel ADC trigger A register
#define ECP44_PGxTRIGC     PG4TRIGC // PWM channel ADC trigger A register

// Device Pin #1 is RB14
#define ECP45_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP45_GPIO_PORT_PIN 14 // Port Pin Number
#define ECP45_TRIS    TRISBbits.TRISB14 // GPIO direction register bit
#define ECP45_WR      LATBbits.LATB14 // GPIO port latch register bit
#define ECP45_RD      PORTBbits.RB14 // GPIO port register bit
#define ECP45_ODC     ODCBbits.ODCB14 // GPIO port open drain configuration register bit
#define ECP45_CNPU    CNPUBbits.CNPUB14 // GPIO port pull-up resistor register bit
#define ECP45_CNPD    CNPDBbits.CNPDB14 // GPIO port pull-down resistor register bit
#define ECP45_CNEN0   CNEN0Bbits.CNEN0B14 // GPIO port change notification Enable register bit
#define ECP45_CNSTAT  CNSTATBbits.CNSTATB14 // GPIO port change notification Status register bit
#define ECP45_CNEN1   CNEN1Bbits.CNEN1B14 // GPIO port change notification Edge Select Enable register bit
#define ECP45_CNF     CNFBbits.CNFB14 // GPIO port change notification flag bit register bit
#define ECP45_RP      46 // Number of Remappable Pin
#define _ECP45_RPxR    _RP46R // Remappable Pin Register
#define ECP45_SET     { asm volatile ("bset _LATB, #14 \n"); }
#define ECP45_CLEAR   { asm volatile ("bclr _LATB, #14 \n"); }
#define ECP45_TOGGLE  { asm volatile ("btg  _LATB, #14 \n"); }
#define ECP45_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP45_DISPOSE      {ECP45_WR = PINSTATE_HIGH; ECP45_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP45_INIT_OUTPUT  {ECP45_WR = PINSTATE_LOW; ECP45_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP45_INIT_INPUT   {ECP45_WR = PINSTATE_HIGH; ECP45_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP45_PGxCHANNEL  1 // PWM channel index
#define ECP45_PGxPER      PG1PER // PWM channel period register
#define ECP45_PGxPHASE    PG1PHASE // PWM channel phase register
#define ECP45_PGxDC       PG1DC // PWM channel duty cycle register
#define ECP45_PGxDCA      PG1DCA// PWM channel duty cycle A register
#define ECP45_PGxDTH      PG1DTH // PWM channel rising edge dead time register
#define ECP45_PGxDTL      PG1DTL // PWM channel falling edge dead time register
#define ECP45_PGx_OVRENH   PG1IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP45_PGx_PENH     PG1IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP45_PGxUPDREQ    PG1STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP45_PGxTRIGA     PG1TRIGA // PWM channel ADC trigger A register
#define ECP45_PGxTRIGB     PG1TRIGB // PWM channel ADC trigger A register
#define ECP45_PGxTRIGC     PG1TRIGC // PWM channel ADC trigger A register
#define ECP45_PWMxIF       _PWM1IF // interrupt flag bit
#define ECP45_PWMxIE       _PWM1IE // interrupt enable bit
#define ECP45_PWMxIP       _PWM1IP // interrupt priority for this analog input
#define _ECP45_PWMxInterrupt _PWM1Interrupt // Interrupt Service Routine name declaration
#define ECP45_TRGSRC_PWMxTRG1   TRGSRC_PWM1_TRG1 // PWM channel trigger 1
#define ECP45_TRGSRC_PWMxTRG2   TRGSRC_PWM1_TRG2 // PWM channel trigger 2

// Device Pin #3 is RC12
#define ECP46_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP46_GPIO_PORT_PIN 12 // Port Pin Number
#define ECP46_TRIS    TRISCbits.TRISC12 // GPIO direction register bit
#define ECP46_WR      LATCbits.LATC12 // GPIO port latch register bit
#define ECP46_RD      PORTCbits.RC12 // GPIO port register bit
#define ECP46_ODC     ODCCbits.ODCC12 // GPIO port open drain configuration register bit
#define ECP46_CNPU    CNPUCbits.CNPUC12 // GPIO port pull-up resistor register bit
#define ECP46_CNPD    CNPDCbits.CNPDC12 // GPIO port pull-down resistor register bit
#define ECP46_CNEN0   CNEN0Cbits.CNEN0C12 // GPIO port change notification Enable register bit
#define ECP46_CNSTAT  CNSTATCbits.CNSTATC12 // GPIO port change notification Status register bit
#define ECP46_CNEN1   CNEN1Cbits.CNEN1C12 // GPIO port change notification Edge Select Enable register bit
#define ECP46_CNF     CNFCbits.CNFC12 // GPIO port change notification flag bit register bit
#define ECP46_RP      60 // Number of Remappable Pin
#define _ECP46_RPxR    _RP60R // Remappable Pin Register
#define ECP46_SET     { asm volatile ("bset _LATC, #12 \n"); }
#define ECP46_CLEAR   { asm volatile ("bclr _LATC, #12 \n"); }
#define ECP46_TOGGLE  { asm volatile ("btg  _LATC, #12 \n"); }
#define ECP46_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP46_DISPOSE      {ECP46_WR = PINSTATE_HIGH; ECP46_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP46_INIT_OUTPUT  {ECP46_WR = PINSTATE_LOW; ECP46_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP46_INIT_INPUT   {ECP46_WR = PINSTATE_HIGH; ECP46_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP46_PGxCHANNEL  8 // PWM channel index
#define ECP46_PGxPER      PG8PER // PWM channel period register
#define ECP46_PGxPHASE    PG8PHASE // PWM channel phase register
#define ECP46_PGxDC       PG8DC // PWM channel duty cycle register
#define ECP46_PGxDCA      PG8DCA// PWM channel duty cycle A register
#define ECP46_PGxDTH      PG8DTH // PWM channel rising edge dead time register
#define ECP46_PGxDTL      PG8DTL // PWM channel falling edge dead time register
#define ECP46_PGx_OVRENH   PG8IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP46_PGx_PENH     PG8IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP46_PGxUPDREQ    PG8STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP46_PGxTRIGA     PG8TRIGA // PWM channel ADC trigger A register
#define ECP46_PGxTRIGB     PG8TRIGB // PWM channel ADC trigger A register
#define ECP46_PGxTRIGC     PG8TRIGC // PWM channel ADC trigger A register
#define ECP46_PWMxIF       _PWM8IF // interrupt flag bit
#define ECP46_PWMxIE       _PWM8IE // interrupt enable bit
#define ECP46_PWMxIP       _PWM8IP // interrupt priority for this analog input
#define _ECP46_PWMxInterrupt _PWM8Interrupt // Interrupt Service Routine name declaration
#define ECP46_TRGSRC_PWMxTRG1   TRGSRC_PWM8_TRG1 // PWM channel trigger 1
#define ECP46_TRGSRC_PWMxTRG2   TRGSRC_PWM8_TRG2 // PWM channel trigger 2

// Device Pin #2 is RB15
#define ECP47_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP47_GPIO_PORT_PIN 15 // Port Pin Number
#define ECP47_TRIS    TRISBbits.TRISB15 // GPIO direction register bit
#define ECP47_WR      LATBbits.LATB15 // GPIO port latch register bit
#define ECP47_RD      PORTBbits.RB15 // GPIO port register bit
#define ECP47_ODC     ODCBbits.ODCB15 // GPIO port open drain configuration register bit
#define ECP47_CNPU    CNPUBbits.CNPUB15 // GPIO port pull-up resistor register bit
#define ECP47_CNPD    CNPDBbits.CNPDB15 // GPIO port pull-down resistor register bit
#define ECP47_CNEN0   CNEN0Bbits.CNEN0B15 // GPIO port change notification Enable register bit
#define ECP47_CNSTAT  CNSTATBbits.CNSTATB15 // GPIO port change notification Status register bit
#define ECP47_CNEN1   CNEN1Bbits.CNEN1B15 // GPIO port change notification Edge Select Enable register bit
#define ECP47_CNF     CNFBbits.CNFB15 // GPIO port change notification flag bit register bit
#define ECP47_RP      47 // Number of Remappable Pin
#define _ECP47_RPxR    _RP47R // Remappable Pin Register
#define ECP47_SET     { asm volatile ("bset _LATB, #15 \n"); }
#define ECP47_CLEAR   { asm volatile ("bclr _LATB, #15 \n"); }
#define ECP47_TOGGLE  { asm volatile ("btg  _LATB, #15 \n"); }
#define ECP47_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP47_DISPOSE      {ECP47_WR = PINSTATE_HIGH; ECP47_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP47_INIT_OUTPUT  {ECP47_WR = PINSTATE_LOW; ECP47_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP47_INIT_INPUT   {ECP47_WR = PINSTATE_HIGH; ECP47_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP47_PGxCHANNEL  1 // PWM channel index
#define ECP47_PGxPER      PG1PER // PWM channel period register
#define ECP47_PGxPHASE    PG1PHASE // PWM channel phase register
#define ECP47_PGxDC       PG1DC // PWM channel duty cycle register
#define ECP47_PGxDCA      PG1DCA// PWM channel duty cycle A register
#define ECP47_PGxDTH      PG1DTH // PWM channel rising edge dead time register
#define ECP47_PGxDTL      PG1DTL // PWM channel falling edge dead time register
#define ECP47_PGx_OVRENL   PG1IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP47_PGx_PENL     PG1IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP47_PGxUPDREQ    PG1STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP47_PGxTRIGA     PG1TRIGA // PWM channel ADC trigger A register
#define ECP47_PGxTRIGB     PG1TRIGB // PWM channel ADC trigger A register
#define ECP47_PGxTRIGC     PG1TRIGC // PWM channel ADC trigger A register

// Device Pin #4 is RC13
#define ECP48_GPIO_INSTANCE 3 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP48_GPIO_PORT_PIN 13 // Port Pin Number
#define ECP48_TRIS    TRISCbits.TRISC13 // GPIO direction register bit
#define ECP48_WR      LATCbits.LATC13 // GPIO port latch register bit
#define ECP48_RD      PORTCbits.RC13 // GPIO port register bit
#define ECP48_ODC     ODCCbits.ODCC13 // GPIO port open drain configuration register bit
#define ECP48_CNPU    CNPUCbits.CNPUC13 // GPIO port pull-up resistor register bit
#define ECP48_CNPD    CNPDCbits.CNPDC13 // GPIO port pull-down resistor register bit
#define ECP48_CNEN0   CNEN0Cbits.CNEN0C13 // GPIO port change notification Enable register bit
#define ECP48_CNSTAT  CNSTATCbits.CNSTATC13 // GPIO port change notification Status register bit
#define ECP48_CNEN1   CNEN1Cbits.CNEN1C13 // GPIO port change notification Edge Select Enable register bit
#define ECP48_CNF     CNFCbits.CNFC13 // GPIO port change notification flag bit register bit
#define ECP48_RP      61 // Number of Remappable Pin
#define _ECP48_RPxR    _RP61R // Remappable Pin Register
#define ECP48_SET     { asm volatile ("bset _LATC, #13 \n"); }
#define ECP48_CLEAR   { asm volatile ("bclr _LATC, #13 \n"); }
#define ECP48_TOGGLE  { asm volatile ("btg  _LATC, #13 \n"); }
#define ECP48_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP48_DISPOSE      {ECP48_WR = PINSTATE_HIGH; ECP48_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP48_INIT_OUTPUT  {ECP48_WR = PINSTATE_LOW; ECP48_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP48_INIT_INPUT   {ECP48_WR = PINSTATE_HIGH; ECP48_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP48_PGxCHANNEL  8 // PWM channel index
#define ECP48_PGxPER      PG8PER // PWM channel period register
#define ECP48_PGxPHASE    PG8PHASE // PWM channel phase register
#define ECP48_PGxDC       PG8DC // PWM channel duty cycle register
#define ECP48_PGxDCA      PG8DCA// PWM channel duty cycle A register
#define ECP48_PGxDTH      PG8DTH // PWM channel rising edge dead time register
#define ECP48_PGxDTL      PG8DTL // PWM channel falling edge dead time register
#define ECP48_PGx_OVRENL   PG8IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP48_PGx_PENL     PG8IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP48_PGxUPDREQ    PG8STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP48_PGxTRIGA     PG8TRIGA // PWM channel ADC trigger A register
#define ECP48_PGxTRIGB     PG8TRIGB // PWM channel ADC trigger A register
#define ECP48_PGxTRIGC     PG8TRIGC // PWM channel ADC trigger A register

// Device Pin #42 is RD7
#define ECP50_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP50_GPIO_PORT_PIN 7 // Port Pin Number
#define ECP50_TRIS    TRISDbits.TRISD7 // GPIO direction register bit
#define ECP50_WR      LATDbits.LATD7 // GPIO port latch register bit
#define ECP50_RD      PORTDbits.RD7 // GPIO port register bit
#define ECP50_ODC     ODCDbits.ODCD7 // GPIO port open drain configuration register bit
#define ECP50_CNPU    CNPUDbits.CNPUD7 // GPIO port pull-up resistor register bit
#define ECP50_CNPD    CNPDDbits.CNPDD7 // GPIO port pull-down resistor register bit
#define ECP50_CNEN0   CNEN0Dbits.CNEN0D7 // GPIO port change notification Enable register bit
#define ECP50_CNSTAT  CNSTATDbits.CNSTATD7 // GPIO port change notification Status register bit
#define ECP50_CNEN1   CNEN1Dbits.CNEN1D7 // GPIO port change notification Edge Select Enable register bit
#define ECP50_CNF     CNFDbits.CNFD7 // GPIO port change notification flag bit register bit
#define ECP50_RP      71 // Number of Remappable Pin
#define _ECP50_RPxR    _RP71R // Remappable Pin Register
#define ECP50_SET     { asm volatile ("bset _LATD, #7 \n"); }
#define ECP50_CLEAR   { asm volatile ("bclr _LATD, #7 \n"); }
#define ECP50_TOGGLE  { asm volatile ("btg  _LATD, #7 \n"); }
#define ECP50_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP50_DISPOSE      {ECP50_WR = PINSTATE_HIGH; ECP50_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP50_INIT_OUTPUT  {ECP50_WR = PINSTATE_LOW; ECP50_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP50_INIT_INPUT   {ECP50_WR = PINSTATE_HIGH; ECP50_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #35 is RB4
#define ECP51_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP51_GPIO_PORT_PIN 4 // Port Pin Number
#define ECP51_TRIS    TRISBbits.TRISB4 // GPIO direction register bit
#define ECP51_WR      LATBbits.LATB4 // GPIO port latch register bit
#define ECP51_RD      PORTBbits.RB4 // GPIO port register bit
#define ECP51_ODC     ODCBbits.ODCB4 // GPIO port open drain configuration register bit
#define ECP51_CNPU    CNPUBbits.CNPUB4 // GPIO port pull-up resistor register bit
#define ECP51_CNPD    CNPDBbits.CNPDB4 // GPIO port pull-down resistor register bit
#define ECP51_CNEN0   CNEN0Bbits.CNEN0B4 // GPIO port change notification Enable register bit
#define ECP51_CNSTAT  CNSTATBbits.CNSTATB4 // GPIO port change notification Status register bit
#define ECP51_CNEN1   CNEN1Bbits.CNEN1B4 // GPIO port change notification Edge Select Enable register bit
#define ECP51_CNF     CNFBbits.CNFB4 // GPIO port change notification flag bit register bit
#define ECP51_RP      36 // Number of Remappable Pin
#define _ECP51_RPxR    _RP36R // Remappable Pin Register
#define ECP51_SET     { asm volatile ("bset _LATB, #4 \n"); }
#define ECP51_CLEAR   { asm volatile ("bclr _LATB, #4 \n"); }
#define ECP51_TOGGLE  { asm volatile ("btg  _LATB, #4 \n"); }
#define ECP51_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP51_DISPOSE      {ECP51_WR = PINSTATE_HIGH; ECP51_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP51_INIT_OUTPUT  {ECP51_WR = PINSTATE_LOW; ECP51_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP51_INIT_INPUT   {ECP51_WR = PINSTATE_HIGH; ECP51_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #39 is RD8
#define ECP52_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP52_GPIO_PORT_PIN 8 // Port Pin Number
#define ECP52_TRIS    TRISDbits.TRISD8 // GPIO direction register bit
#define ECP52_WR      LATDbits.LATD8 // GPIO port latch register bit
#define ECP52_RD      PORTDbits.RD8 // GPIO port register bit
#define ECP52_ODC     ODCDbits.ODCD8 // GPIO port open drain configuration register bit
#define ECP52_CNPU    CNPUDbits.CNPUD8 // GPIO port pull-up resistor register bit
#define ECP52_CNPD    CNPDDbits.CNPDD8 // GPIO port pull-down resistor register bit
#define ECP52_CNEN0   CNEN0Dbits.CNEN0D8 // GPIO port change notification Enable register bit
#define ECP52_CNSTAT  CNSTATDbits.CNSTATD8 // GPIO port change notification Status register bit
#define ECP52_CNEN1   CNEN1Dbits.CNEN1D8 // GPIO port change notification Edge Select Enable register bit
#define ECP52_CNF     CNFDbits.CNFD8 // GPIO port change notification flag bit register bit
#define ECP52_RP      72 // Number of Remappable Pin
#define _ECP52_RPxR    _RP72R // Remappable Pin Register
#define ECP52_SET     { asm volatile ("bset _LATD, #8 \n"); }
#define ECP52_CLEAR   { asm volatile ("bclr _LATD, #8 \n"); }
#define ECP52_TOGGLE  { asm volatile ("btg  _LATD, #8 \n"); }
#define ECP52_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP52_DISPOSE      {ECP52_WR = PINSTATE_HIGH; ECP52_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP52_INIT_OUTPUT  {ECP52_WR = PINSTATE_LOW; ECP52_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP52_INIT_INPUT   {ECP52_WR = PINSTATE_HIGH; ECP52_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #12 is RD13
#define ECP54_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP54_GPIO_PORT_PIN 13 // Port Pin Number
#define ECP54_TRIS    TRISDbits.TRISD13 // GPIO direction register bit
#define ECP54_WR      LATDbits.LATD13 // GPIO port latch register bit
#define ECP54_RD      PORTDbits.RD13 // GPIO port register bit
#define ECP54_ODC     ODCDbits.ODCD13 // GPIO port open drain configuration register bit
#define ECP54_CNPU    CNPUDbits.CNPUD13 // GPIO port pull-up resistor register bit
#define ECP54_CNPD    CNPDDbits.CNPDD13 // GPIO port pull-down resistor register bit
#define ECP54_CNEN0   CNEN0Dbits.CNEN0D13 // GPIO port change notification Enable register bit
#define ECP54_CNSTAT  CNSTATDbits.CNSTATD13 // GPIO port change notification Status register bit
#define ECP54_CNEN1   CNEN1Dbits.CNEN1D13 // GPIO port change notification Edge Select Enable register bit
#define ECP54_CNF     CNFDbits.CNFD13 // GPIO port change notification flag bit register bit
#define ECP54_RP      77 // Number of Remappable Pin
#define _ECP54_RPxR    _RP77R // Remappable Pin Register
#define ECP54_SET     { asm volatile ("bset _LATD, #13 \n"); }
#define ECP54_CLEAR   { asm volatile ("bclr _LATD, #13 \n"); }
#define ECP54_TOGGLE  { asm volatile ("btg  _LATD, #13 \n"); }
#define ECP54_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define ECP54_DISPOSE      {ECP54_WR = PINSTATE_HIGH; ECP54_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define ECP54_INIT_OUTPUT  {ECP54_WR = PINSTATE_LOW; ECP54_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP54_INIT_INPUT   {ECP54_WR = PINSTATE_HIGH; ECP54_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #34 is RB3
#define ECP56_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define ECP56_GPIO_PORT_PIN 3 // Port Pin Number
#define ECP56_TRIS    TRISBbits.TRISB3 // GPIO direction register bit
#define ECP56_WR      LATBbits.LATB3 // GPIO port latch register bit
#define ECP56_RD      PORTBbits.RB3 // GPIO port register bit
#define ECP56_ODC     ODCBbits.ODCB3 // GPIO port open drain configuration register bit
#define ECP56_CNPU    CNPUBbits.CNPUB3 // GPIO port pull-up resistor register bit
#define ECP56_CNPD    CNPDBbits.CNPDB3 // GPIO port pull-down resistor register bit
#define ECP56_CNEN0   CNEN0Bbits.CNEN0B3 // GPIO port change notification Enable register bit
#define ECP56_CNSTAT  CNSTATBbits.CNSTATB3 // GPIO port change notification Status register bit
#define ECP56_CNEN1   CNEN1Bbits.CNEN1B3 // GPIO port change notification Edge Select Enable register bit
#define ECP56_CNF     CNFBbits.CNFB3 // GPIO port change notification flag bit register bit
#define ECP56_RP      35 // Number of Remappable Pin
#define _ECP56_RPxR    _RP35R // Remappable Pin Register
#define ECP56_SET     { asm volatile ("bset _LATB, #3 \n"); }
#define ECP56_CLEAR   { asm volatile ("bclr _LATB, #3 \n"); }
#define ECP56_TOGGLE  { asm volatile ("btg  _LATB, #3 \n"); }
#define ECP56_IS_ANALOG_INPUT  true // Pin is/is not analog input 
#define ECP56_ANSEL   _ANSELB3 // analog/digital pin configuration register bit
#define ECP56_ADCCORE 8 // index starts from zero, last index indicated shared adC core
#define ECP56_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP56_ADCAN   8   // ANx input pin number
#define ECP56_ADCBUF  ADCBUF8 // ADC buffer register for this input
#define ECP56_ADIE_IEx ADIELbits.IE8
#define ECP56_ADEIE_EIEx ADEIELbits.EIEN8
#define ECP56_ADCANxIF  _ADCAN8IF // interrupt flag bit
#define ECP56_ADCANxIE  _ADCAN8IE // interrupt enable bit
#define ECP56_ADCANxIP  _ADCAN8IP // interrupt priority for this analog input
#define ECP56_ANxRDY    _AN8RDY // ADC buffer ready bit
#define _ECP56_ADCANxInterrupt _ADCAN8Interrupt
#define ECP56_ANxTRGSRC _TRGSRC8 // ADC input trigger source register
#define ECP56_INIT_ANALOG	{ECP56_ANSEL = 1; ECP56_WR = PINSTATE_HIGH; ECP56_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP56_DISPOSE      {ECP56_WR = PINSTATE_HIGH; ECP56_TRIS = PINDIR_INPUT; ECP56_ANSEL = 0;} // disposing macro for digital input with analog function
#define ECP56_INIT_OUTPUT  {ECP56_WR = PINSTATE_LOW; ECP56_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP56_INIT_INPUT   {ECP56_WR = PINSTATE_HIGH; ECP56_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #46 is RB6
#define SCL_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define SCL_GPIO_PORT_PIN 6 // Port Pin Number
#define SCL_TRIS    TRISBbits.TRISB6 // GPIO direction register bit
#define SCL_WR      LATBbits.LATB6 // GPIO port latch register bit
#define SCL_RD      PORTBbits.RB6 // GPIO port register bit
#define SCL_ODC     ODCBbits.ODCB6 // GPIO port open drain configuration register bit
#define SCL_CNPU    CNPUBbits.CNPUB6 // GPIO port pull-up resistor register bit
#define SCL_CNPD    CNPDBbits.CNPDB6 // GPIO port pull-down resistor register bit
#define SCL_CNEN0   CNEN0Bbits.CNEN0B6 // GPIO port change notification Enable register bit
#define SCL_CNSTAT  CNSTATBbits.CNSTATB6 // GPIO port change notification Status register bit
#define SCL_CNEN1   CNEN1Bbits.CNEN1B6 // GPIO port change notification Edge Select Enable register bit
#define SCL_CNF     CNFBbits.CNFB6 // GPIO port change notification flag bit register bit
#define SCL_RP      38 // Number of Remappable Pin
#define _SCL_RPxR    _RP38R // Remappable Pin Register
#define SCL_SET     { asm volatile ("bset _LATB, #6 \n"); }
#define SCL_CLEAR   { asm volatile ("bclr _LATB, #6 \n"); }
#define SCL_TOGGLE  { asm volatile ("btg  _LATB, #6 \n"); }
#define SCL_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define SCL_DISPOSE      {SCL_WR = PINSTATE_HIGH; SCL_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define SCL_INIT_OUTPUT  {SCL_WR = PINSTATE_LOW; SCL_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SCL_INIT_INPUT   {SCL_WR = PINSTATE_HIGH; SCL_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #45 is RB5
#define SDA_GPIO_INSTANCE 2 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define SDA_GPIO_PORT_PIN 5 // Port Pin Number
#define SDA_TRIS    TRISBbits.TRISB5 // GPIO direction register bit
#define SDA_WR      LATBbits.LATB5 // GPIO port latch register bit
#define SDA_RD      PORTBbits.RB5 // GPIO port register bit
#define SDA_ODC     ODCBbits.ODCB5 // GPIO port open drain configuration register bit
#define SDA_CNPU    CNPUBbits.CNPUB5 // GPIO port pull-up resistor register bit
#define SDA_CNPD    CNPDBbits.CNPDB5 // GPIO port pull-down resistor register bit
#define SDA_CNEN0   CNEN0Bbits.CNEN0B5 // GPIO port change notification Enable register bit
#define SDA_CNSTAT  CNSTATBbits.CNSTATB5 // GPIO port change notification Status register bit
#define SDA_CNEN1   CNEN1Bbits.CNEN1B5 // GPIO port change notification Edge Select Enable register bit
#define SDA_CNF     CNFBbits.CNFB5 // GPIO port change notification flag bit register bit
#define SDA_RP      37 // Number of Remappable Pin
#define _SDA_RPxR    _RP37R // Remappable Pin Register
#define SDA_SET     { asm volatile ("bset _LATB, #5 \n"); }
#define SDA_CLEAR   { asm volatile ("bclr _LATB, #5 \n"); }
#define SDA_TOGGLE  { asm volatile ("btg  _LATB, #5 \n"); }
#define SDA_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define SDA_DISPOSE      {SDA_WR = PINSTATE_HIGH; SDA_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define SDA_INIT_OUTPUT  {SDA_WR = PINSTATE_LOW; SDA_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SDA_INIT_INPUT   {SDA_WR = PINSTATE_HIGH; SDA_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #54 is RD4
#define UART_RX_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define UART_RX_GPIO_PORT_PIN 4 // Port Pin Number
#define UART_RX_TRIS    TRISDbits.TRISD4 // GPIO direction register bit
#define UART_RX_WR      LATDbits.LATD4 // GPIO port latch register bit
#define UART_RX_RD      PORTDbits.RD4 // GPIO port register bit
#define UART_RX_ODC     ODCDbits.ODCD4 // GPIO port open drain configuration register bit
#define UART_RX_CNPU    CNPUDbits.CNPUD4 // GPIO port pull-up resistor register bit
#define UART_RX_CNPD    CNPDDbits.CNPDD4 // GPIO port pull-down resistor register bit
#define UART_RX_CNEN0   CNEN0Dbits.CNEN0D4 // GPIO port change notification Enable register bit
#define UART_RX_CNSTAT  CNSTATDbits.CNSTATD4 // GPIO port change notification Status register bit
#define UART_RX_CNEN1   CNEN1Dbits.CNEN1D4 // GPIO port change notification Edge Select Enable register bit
#define UART_RX_CNF     CNFDbits.CNFD4 // GPIO port change notification flag bit register bit
#define UART_RX_RP      68 // Number of Remappable Pin
#define _UART_RX_RPxR    _RP68R // Remappable Pin Register
#define UART_RX_SET     { asm volatile ("bset _LATD, #4 \n"); }
#define UART_RX_CLEAR   { asm volatile ("bclr _LATD, #4 \n"); }
#define UART_RX_TOGGLE  { asm volatile ("btg  _LATD, #4 \n"); }
#define UART_RX_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define UART_RX_DISPOSE      {UART_RX_WR = PINSTATE_HIGH; UART_RX_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define UART_RX_INIT_OUTPUT  {UART_RX_WR = PINSTATE_LOW; UART_RX_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define UART_RX_INIT_INPUT   {UART_RX_WR = PINSTATE_HIGH; UART_RX_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #55 is RD3
#define UART_TX_GPIO_INSTANCE 4 // Number indicating device port, where 1=A, 2=B, 3=C, etc.
#define UART_TX_GPIO_PORT_PIN 3 // Port Pin Number
#define UART_TX_TRIS    TRISDbits.TRISD3 // GPIO direction register bit
#define UART_TX_WR      LATDbits.LATD3 // GPIO port latch register bit
#define UART_TX_RD      PORTDbits.RD3 // GPIO port register bit
#define UART_TX_ODC     ODCDbits.ODCD3 // GPIO port open drain configuration register bit
#define UART_TX_CNPU    CNPUDbits.CNPUD3 // GPIO port pull-up resistor register bit
#define UART_TX_CNPD    CNPDDbits.CNPDD3 // GPIO port pull-down resistor register bit
#define UART_TX_CNEN0   CNEN0Dbits.CNEN0D3 // GPIO port change notification Enable register bit
#define UART_TX_CNSTAT  CNSTATDbits.CNSTATD3 // GPIO port change notification Status register bit
#define UART_TX_CNEN1   CNEN1Dbits.CNEN1D3 // GPIO port change notification Edge Select Enable register bit
#define UART_TX_CNF     CNFDbits.CNFD3 // GPIO port change notification flag bit register bit
#define UART_TX_RP      67 // Number of Remappable Pin
#define _UART_TX_RPxR    _RP67R // Remappable Pin Register
#define UART_TX_SET     { asm volatile ("bset _LATD, #3 \n"); }
#define UART_TX_CLEAR   { asm volatile ("bclr _LATD, #3 \n"); }
#define UART_TX_TOGGLE  { asm volatile ("btg  _LATD, #3 \n"); }
#define UART_TX_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define UART_TX_DISPOSE      {UART_TX_WR = PINSTATE_HIGH; UART_TX_TRIS = PINDIR_INPUT;} // disposing macro for digital input
#define UART_TX_INIT_OUTPUT  {UART_TX_WR = PINSTATE_LOW; UART_TX_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define UART_TX_INIT_INPUT   {UART_TX_WR = PINSTATE_HIGH; UART_TX_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #7 is MCLR

// Device Pin #9 is VSS

// Device Pin #10 is VDD

// Device Pin #19 is AVDD

// Device Pin #20 is AVss

// Device Pin #25 is VDD

// Device Pin #26 is VSS

// Device Pin #40 is VSS

// Device Pin #41 is VDD

// Device Pin #56 is VSS

// Device Pin #57 is VDD



#endif	/* __MA330048_P33CK_R30_PINMAP_H__ */
