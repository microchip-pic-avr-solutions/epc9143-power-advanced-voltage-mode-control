/*
 * File:   config_bits.c
 * Author: M91406
 *
 * Created on July 8, 2019, 2:39 PM
 */


#include <xc.h>

// Configuration bits: selected in the GUI

/*******************************************************************************************************/
// FICD

#pragma config ICS = PGD3    //ICD Communication Channel Select bits->Communicate on PGC2 and PGD2
#pragma config JTAGEN = OFF    //JTAG Enable bit->JTAG is disabled

/*******************************************************************************************************/
// FALTREG
#pragma config CTXT1 = IPL2   //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits->Not Assigned
#pragma config CTXT2 = IPL5   //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits->Not Assigned
#pragma config CTXT3 = OFF    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits->Not Assigned
#pragma config CTXT4 = OFF    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits->Not Assigned

/*******************************************************************************************************/
// FSEC
#pragma config BWRP = OFF    //Boot Segment Write-Protect bit->Boot Segment may be written
#pragma config BSS = DISABLED    //Boot Segment Code-Protect Level bits->No Protection (other than BWRP)
#pragma config BSEN = OFF    //Boot Segment Control bit->No Boot Segment
#pragma config GWRP = OFF    //General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = DISABLED    //General Segment Code-Protect Level bits->No Protection (other than GWRP)
#pragma config CWRP = OFF    //Configuration Segment Write-Protect bit->Configuration Segment may be written
#pragma config CSS = DISABLED    //Configuration Segment Code-Protect Level bits->No Protection (other than CWRP)
#pragma config AIVTDIS = OFF    //Alternate Interrupt Vector Table bit->Disabled AIVT

// FBSLIM
#pragma config BSLIM = 8191    //Boot Segment Flash Page Address Limit bits->8191

// FOSCSEL
#pragma config FNOSC = FRCDIVN    //Oscillator Source Selection->Fast RC Oscillator with divide-by-N with PLL module (FRCPLL) 
#pragma config IESO = OFF    //Two-speed Oscillator Start-up Enable bit->Start up with user-selected oscillator source

// FOSC
#pragma config POSCMD = NONE    //Primary Oscillator Mode Select bits->Primary Oscillator disabled
#pragma config OSCIOFNC = ON    //OSC2 Pin Function bit->OSC2 is general purpose digital I/O pin
#pragma config FCKSM = CSECMD   //Clock Switching Mode bits->Clock switching is enabled,Fail-safe Clock Monitor is disabled
#pragma config PLLKEN = ON      //PLL Lock Status Control->PLL lock signal will be used to disable PLL clock output if lock is lost
#pragma config XTCFG = G1       //XT Config->24-32 MHz crystals
#pragma config XTBST = DISABLE  //XT Boost->Boost the kick-start

// FWDT
//#pragma config RWDTPS = PS2147483648    //Run Mode Watchdog Timer Post Scaler select bits->1:2147483648
#pragma config RCLKSEL = LPRC    //Watchdog Timer Clock Select bits->Always use LPRC
#pragma config WINDIS = OFF    //Watchdog Timer Window Enable bit->Watchdog Timer in Window mode
#pragma config WDTWIN = WIN25    //Watchdog Timer Window Select bits->WDT Window is 25% of WDT period
#pragma config RWDTPS = PS128    //Run Mode Watchdog Timer Post Scaler select bits->1:128
#pragma config SWDTPS = PS2147483648    //Sleep Mode Watchdog Timer Post Scaler select bits->1:2147483648
#pragma config FWDTEN = ON_SW    //Watchdog Timer Enable bit->WDT controlled via SW, use WDTCON.ON bit

// FPOR
#pragma config BISTDIS = DISABLED    //Memory BIST Feature Disable->mBIST on reset feature disabled

// FDMTIVTL
#pragma config DMTIVTL = 0    //Dead Man Timer Interval low word->0

// FDMTIVTH
#pragma config DMTIVTH = 0    //Dead Man Timer Interval high word->0

// FDMTCNTL
#pragma config DMTCNTL = 0    //Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF)->0

// FDMTCNTH
#pragma config DMTCNTH = 0    //Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF)->0

// FDMT
#pragma config DMTDIS = OFF    //Dead Man Timer Disable bit->Dead Man Timer is Disabled and can be enabled by software

// FDEVOPT
#pragma config ALTI2C1 = OFF    //Alternate I2C1 Pin bit->I2C1 mapped to SDA1/SCL1 pins
#pragma config ALTI2C2 = OFF    //Alternate I2C2 Pin bit->I2C2 mapped to SDA2/SCL2 pins
#pragma config SPI2PIN = PPS    //SPI2 Pin Select bit->SPI2 uses I/O remap (PPS) pins
#pragma config SMB3EN = SMBUS3    //SM Bus Enable->SMBus 3.0 input levels

