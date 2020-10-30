/*!Software License Agreement
 * ************************************************************************************************
 *
 * Software License Agreement
 *
 * Copyright © 2020 Microchip Technology Inc.  All rights reserved. Microchip licenses to you the
 * right to use, modify, copy and distribute Software only when embedded on a Microchip 
 * microcontroller or digital signal controller, which is integrated into your product or third 
 * party product (pursuant to the sublicense terms in the accompanying license agreement).
 *
 * You should refer to the license agreement accompanying this Software for additional information 
 * regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR 
 * IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR 
 * OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT  
 * LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS  
 * OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY  
 * THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *
 * ***********************************************************************************************/

// Include Header Files
#include "p33c_pps.h"

/*@@p33c_pps.c
 * ************************************************************************************************
 * Summary:
 * Generic Peripheral Pin Select (PPS) Driver Module
 *
 * Dependencies:    
 * p33c_pps.h
 *
 * Description:
 * Some low-pin count devices have the capability to assign digital functions to a range of 
 * free configurable pins (RPx). This driver module offers functions to read from and write to
 * the configuration registers, which will connect a digital peripheral bock with a selected 
 * pin.
 *
 * References:
 * dsPIC33F Reference Manual, Section 10: I/O Ports, Chapter 10.3: Peripheral Multiplexing
 *
 * Author:	M91406
 * Version: 1.3
 *
 * History:
 *	11/04/2008	First Release
 *  08/25/2009	Added definitions for new peripherals
 *  02/05/2012	Format transfer
 *  04/11/2016	Added definitions and compile switches for dsPIC33EP GS
 *  05/29/2019  Added RPx pin configuration lock/unlock sequence for dsPIC33C
 *  10/14/2020  Removed support for dsPIC33F and dsPIC33E
 * ***********************************************************************************************/

/*@@PPS_LockIO
 * ************************************************************************************************
 * Summary:
 * Locks the Peripheral Pin Select Configuration registers against accidental changes
 *
 * Parameters:
 *	(none)
 *
 * Returns:
 *	1: Success
 *	0: Error
 *
 * Description:
 * This inline-assembly routine locks the Port Multiplexing Configuration registers by keeping
 * the required number of cycles during the Lock pocess. This function has to be called once 
 * before digital functions are mapped to a specific pin. Once called, a series of assignments
 * can be executed.
 * 
 * Note:
 * If bit IOL1WAY in the Oscillator Configuration Bits (FOSC) is set, only one pin assignment
 * operation will be allowed. all following calls of Unlock() or Lock() will be ignored. 
 *
 * See Also:
 *	p33c_pps.h
 * 
 * ***********************************************************************************************/
volatile uint16_t PPS_LockIO(void){

    __builtin_write_RPCON(0x0800); // lock PPS
    return(RPCONbits.IOLOCK);
    
}

/*@@PPS_UnlockIO
 * ************************************************************************************************
 * Summary:
 * Unlocks the Peripheral Pin Select Configuration registers to enable changes
 *
 * Parameters:
 *	(none)
 *
 * Returns:
 *	1: Success
 *	0: Error
 *
 * Description:
 * This inline-assembly routine unlocks the Port Multiplexing Configuration registers by keeping
 * the required number of cycles during the unlock pocess. This function has to be called once 
 * after digital functions have been mapped to a specific pin, to prevent accidential changes. 
 * 
 * Note:
 * If bit IOL1WAY in the Oscillator Configuration Bits (FOSC) is set, only one pin assignment
 * operation wil be allowed. all following calls of Unlock() or Lock() will be ignored. 
 *
 * See Also:
 *	p33c_pps.h
 * 
 * ***********************************************************************************************/
volatile uint16_t PPS_UnlockIO(void){

    __builtin_write_RPCON(0x0000); // unlock PPS
    return(1 - RPCONbits.IOLOCK);
    
}

/*@@PPS_RemapOutput
 * ************************************************************************************************
 * Summary:
 * Assigns a digital function output to a pin
 *
 * Parameters:
 *	unsigned char pinno: Number of the RPx-pin, which should be assigned to the function
 *	unsigned char peripheral: Function, which should be assigned to the pin
 *
 * Returns:
 *	1: Success
 *	0: Error
 *
 * Description:
 * Any supported digital function output (e.g. UART TxD) can be assigned to one of the RPx pins
 * of the MCU/DSC. To assign a function output to a pin, call 
 *
 *	smpsPPS_RemapOutput([RP-NUMBER], [FUNCTION])
 * 
 * Example:
 *	lres |= smpsPPS_RemapOutput(PIN_RP9 , PPSOUT_SYNCO1);	// Assign RP9 to PWMSyncClkOutput
 *
 * See Also:
 *	p33c_pps.h
 * 
 * ***********************************************************************************************/
volatile uint16_t PPS_RemapOutput(volatile uint8_t pinno, volatile uint8_t peripheral){
	
    volatile uint16_t retval = 0;
    volatile uint8_t *regptr;
    volatile uint8_t pin_offset=0;
    
    pin_offset = (pinno - RP_PINNO_MIN);    // Determine pin-offset
    regptr = (volatile uint8_t *)&RPOR0;    // get register block base address
    regptr += (volatile uint8_t)pin_offset; // add offset
    *regptr = (volatile uint8_t)peripheral;	// copy configuration into register location
   retval = (bool)(*regptr == (volatile uint8_t)peripheral);	// Check if contents have been written correctly
    
	return (retval);

}

/*@@PPS_RemapInput
 * ************************************************************************************************
 * Summary:
 * Assigns a pin to a digital function input
 *
 * Parameters:
 *	unsigned char pinno: Number of the RPx-pin, which should be assigned to the function
 *	unsigned char peripheral: Function, which should be assigned to the pin
 *
 * Returns:
 *	1: Success
 *	0: Error
 *
 * Description:
 * Any RPx pin can be assigned to a supported digital function input (e.g. UART RxD). To assign 
 * a pin to a function input, call 
 *
 *	smpsPPS_RemapInput([RP-NUMBER], [FUNCTION])
 * 
 * Example:
 *	lres |= smpsPPS_RemapInput(PIN_RP10, PPSIN_U1RX);		// Assign RP10 to UART1 RxD
 *
 * See Also:
 *	p33SMPS_pps.h, FOSC, IOL1WAY, IOL1WAY_ON, IOL1WAY_OFF, smpsPPS_LockIO, smpsPPS_UnlockIO, smpsPPS_RemapOutput, 
 *  smpsPPS_UnmapInput, smpsPPS_UnmapOutput
 * 
 * ***********************************************************************************************/
volatile uint16_t PPS_RemapInput(volatile uint8_t pinno, volatile uint8_t *peripheral)
{

	// Map selected pin function
    *peripheral = pinno;

	return 1;
  
}

/*@@PPS_UnmapOutput
 * ************************************************************************************************
 * Summary:
 * Disconnects a pin from a digital function output
 *
 * Parameters:
 *	unsigned char pinno: Number of the RPx-pin
 *
 * Returns:
 *	1: Success
 *	0: Error
 *
 * Description:
 * An existing assignment between any RPx pin and a supported digital function output will be
 * dissolved.
 *
 *	smpsPPS_UnmapOutput([RP-NUMBER])
 * 
 * Example:
 *	result = smpsPPS_UnmapOutput(PIN_RP9);		// Dissolve RP9 assignment
 *
 * See Also:
 *	p33c_pps.h
 * 
 * ***********************************************************************************************/
volatile uint16_t PPS_UnmapOutput(volatile uint8_t pinno)
{
    volatile uint16_t retval=0;

	// Unmap selected pin function
	retval = PPS_RemapOutput(pinno, PPSPIN_NULL);
	return retval;

}

/*@@PPS_UnmapInput
 * ************************************************************************************************
 * Summary:
 * Disconnects a pin from a digital function input
 *
 * Parameters:
 *	unsigned char pinno: Number of the RPx-pin
 *
 * Returns:
 *	1: Success
 *	0: Error
 *
 * Description:
 * An existing assignment between any RPx pin and a supported digital function input will be
 * dissolved.
 *
 *	smpsPPS_UnmapInput([RP-NUMBER])
 * 
 * Example:
 *	lres |= smpsPPS_UnmapInput(PIN_RP10);		// Dissolve RP10 assignment
 *
 * See Also:
 *	p33c_pps.h
 * 
 * ***********************************************************************************************/
volatile uint16_t PPS_UnmapInput(volatile uint8_t* peripheral)
{
    volatile uint16_t retval=0;

	// Unmap selected pin function
	retval = PPS_RemapInput(PPSPIN_NULL, peripheral);
	return retval;

}

// End Of File
