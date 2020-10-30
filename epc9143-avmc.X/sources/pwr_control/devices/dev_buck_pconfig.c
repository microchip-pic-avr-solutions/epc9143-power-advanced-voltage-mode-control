/*
 * File:   drv_buck_pconfig.c
 * Author: M91406
 *
 * Created on March 12, 2020, 4:31 PM
 */

#if (__XC16_VERSION__ > 1500)
  #pragma message ("Warning: Library file '" __FILE__ "' has not been tested with the recently selected compiler version")
#endif

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> // include standard integer types header file
#include <stdbool.h> // include standard boolean types header file

#include "dev_buck_pconfig.h"
#include "dev_buck_templates.h"

/* PRIVATE VARIABLES */
volatile uint16_t adcore_mask=0;
volatile uint16_t adcore_diff_mask=0;

/* @@buckPWM_ModuleInitialize
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckPWM_ModuleInitialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance)
{
    volatile uint16_t retval=1;
    volatile struct P33C_PWM_MODULE_s* pwm;
    
    pwm = (volatile struct P33C_PWM_MODULE_s*) ((volatile uint16_t*) &PCLKCON);
    
    // Make sure power to the peripheral is enabled
    PMD1bits.PWMMD = 0; // PWM Module Disable: PWM module is enabled
    
    // PWM GENERATOR ENABLE
    PG1CONLbits.ON = 0; // PWM Generator #1 Enable: PWM Generator is not enabled
    PG2CONLbits.ON = 0; // PWM Generator #2 Enable: PWM Generator is not enabled
    PG3CONLbits.ON = 0; // PWM Generator #3 Enable: PWM Generator is not enabled
    PG4CONLbits.ON = 0; // PWM Generator #4 Enable: PWM Generator is not enabled
    
    #if defined (PG5CONL)
    PG5CONLbits.ON = 0; // PWM Generator #5 Enable: PWM Generator is not enabled
    #endif
    #if defined (PG6CONL)
    PG6CONLbits.ON = 0; // PWM Generator #6 Enable: PWM Generator is not enabled
    #endif
    #if defined (PG7CONL)
    PG7CONLbits.ON = 0; // PWM Generator #7 Enable: PWM Generator is not enabled
    #endif
    #if defined (PG8CONL)
    PG8CONLbits.ON = 0; // PWM Generator #8 Enable: PWM Generator is not enabled
    #endif
    
    // PWM CLOCK CONTROL REGISTER
    pwm->vPCLKCON.value = 0b0000000000000011;
    
//    PCLKCONbits.LOCK = 0;       // Lock bit: Write-protected registers and bits are unlocked
//    PCLKCONbits.DIVSEL = 0b00;  // PWM Clock Divider Selection: Divide ratio is 1:2
//    PCLKCONbits.MCLKSEL = 0b11; // PWM Master Clock Selection: Auxiliary PLL post-divider output
    
    // FREQUENCY SCALE REGISTER & FREQUENCY SCALING MINIMUM PERIOD REGISTER
    pwm->vFSCL.value = 0x0000;      // Reset frequency scaling register
    pwm->vFSMINPER.value = 0x0000;  // Reset frequency scaling minimum register
    
    // MASTER PHASE, DUTY CYCLE AND PERIOD REGISTERS
    pwm->vMPHASE.value = 0;    // Reset master phase
    pwm->vMDC.value = 0x0000;  // Reset master duty cycle
    pwm->vMPER.value = 0x0000; // Reset Master period 
    
    // If buck converter has been configured in MASTER PERIOD mode
    if (buckInstance->sw_node[0].master_period_enable) // If master period mode is enabled...
        pwm->vMPER.value = buckInstance->sw_node[0].period; // Set Period of phase #1
    
    // LINEAR FEEDBACK SHIFT REGISTER
    pwm->vLFSR.value = 0x0000;      // Reset linear feedback shift register
    
    // COMBINATIONAL TRIGGER REGISTERS
    pwm->vCMBTRIGL.value = 0x0000;
    pwm->vCMBTRIGH.value = 0x0000;

    // COMBINATORIAL PWM LOGIC A CONTROL REGISTERS A-F
    pwm->LOGCON_A.value = 0x0000;
    pwm->LOGCON_B.value = 0x0000;
    pwm->LOGCON_C.value = 0x0000;
    pwm->LOGCON_D.value = 0x0000;
    pwm->LOGCON_E.value = 0x0000;
    pwm->LOGCON_F.value = 0x0000;
    
    // PWM EVENT OUTPUT CONTROL REGISTERS A-F
    pwm->PWMEVT_A.value = 0x0000;
    pwm->PWMEVT_B.value = 0x0000;
    pwm->PWMEVT_C.value = 0x0000;
    pwm->PWMEVT_D.value = 0x0000;
    pwm->PWMEVT_E.value = 0x0000;
    pwm->PWMEVT_F.value = 0x0000;

    return(retval);    
}

/* @@buckPWM_ChannelInitialize
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckPWM_ChannelInitialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance)
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;

    volatile struct P33C_GPIO_INSTANCE_s* gpio;
    volatile struct P33C_PWM_GENERATOR_s* pg;
    volatile uint16_t pwm_Instance;
    volatile uint16_t gpio_Instance;

    for (_i=0; _i<buckInstance->set_values.no_of_phases; _i++) {
    
        // LOAD PERIPHERAL INSTANCES FROM BUCK CONVERTER OBJECT
        pwm_Instance = buckInstance->sw_node[_i].pwm_instance;
        gpio_Instance = buckInstance->sw_node[_i].gpio_instance;

        // CAPTURE MEMORY ADDRESS OF GIVEN PWM GENERATOR INSTANCE
        gpio = (volatile struct P33C_GPIO_INSTANCE_s*)
            ((volatile uint8_t*)&ANSELA + (gpio_Instance * P33C_GPIO_SFR_OFFSET));

        pg   = (volatile struct P33C_PWM_GENERATOR_s*) 
            ((volatile uint16_t*)&PG1CONL + ((pwm_Instance - 1) * P33C_PWMGEN_SFR_OFFSET));

        // WRITE GPIO CONFIGURATION OF PWM OUTPUT(S)
        gpio->LATx.value  &= ~(0x0001 << buckInstance->sw_node[_i].gpio_high); // Clear PWMxH output LOW
        gpio->LATx.value  &= ~(0x0001 << buckInstance->sw_node[_i].gpio_low);  // Clear PWMxL output LOW
        gpio->TRISx.value &= ~(0x0001 << buckInstance->sw_node[_i].gpio_high); // Clear PWMxH output to OUTPUT
        gpio->TRISx.value &= ~(0x0001 << buckInstance->sw_node[_i].gpio_low);  // Clear PWMxL output to OUTPUT
        gpio->CNPDx.value |= (0x0001 << buckInstance->sw_node[_i].gpio_high);  // Enable intern pull down register (PWM1H)
        gpio->CNPDx.value |= (0x0001 << buckInstance->sw_node[_i].gpio_low);   // Enable intern pull down register (PWM1L)
    
        // COPY CONFIGURATION FROM TEMPLATE TO PWM GENERATOR x CONTROL REGISTERS
        retval &= p33c_PwmGenerator_ConfigWrite(buckInstance->sw_node[_i].pwm_instance, buckPwmGeneratorConfig);
//        pg->PGxCONL.value = REG_PGxCONL; // PGxCONL: PWM GENERATOR x CONTROL REGISTER LOW
//        pg->PGxCONH.value = REG_PGxCONH; // PGxCONH: PWM GENERATOR x CONTROL REGISTER HIGH
//        pg->PGxIOCONL.value = REG_PGxIOCONL; // PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER LOW
//        pg->PGxIOCONH.value = REG_PGxIOCONH; // PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER HIGH
//        pg->PGxEVTL.value = REG_PGxEVTL; // PGxEVTL: PWM GENERATOR x EVENT REGISTER LOW
//        pg->PGxEVTH.value = REG_PGxEVTH; // PGxEVTH: PWM GENERATOR x EVENT REGISTER HIGH
//        pg->PGxCLPCIL.value = REG_PGxCLPCIL; // PGxLCPCIL: PWM GENERATOR x CURRENT LIMIT PCI REGISTER LOW
//        pg->PGxCLPCIH.value = REG_PGxCLPCIH; // PGxLCPCIL: PWM GENERATOR x CURRENT LIMIT PCI REGISTER HIGH
//        pg->PGxFPCIL.value = REG_PGxFPCIL; // PGxFPCIL: PWM GENERATOR x FAULT PCI REGISTER LOW
//        pg->PGxFPCIH.value = REG_PGxFPCIH; // PGxFPCIL: PWM GENERATOR x FAULT PCI REGISTER HIGH
//        pg->PGxFFPCIL.value = REG_PGxFFPCIL; // PGxFFPCIL: PWM GENERATOR x FEED FORWARD PCI REGISTER LOW
//        pg->PGxFFPCIH.value = REG_PGxFFPCIH; // PGxFFPCIL: PWM GENERATOR x FEED FORWARD PCI REGISTER HIGH
//        pg->PGxSPCIL.value = REG_PGxSPCIL; // PGxSPCIL: PWM GENERATOR x SOFTWARE PCI REGISTER LOW
//        pg->PGxSPCIH.value = REG_PGxSPCIH; // PGxSPCIL: PWM GENERATOR x SOFTWARE PCI REGISTER HIGH
//        pg->PGxLEBL.value = REG_PGxLEBL; // PGxLEBL: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER LOW
//        pg->PGxLEBH.value = REG_PGxLEBH; // PGxLEBL: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER HIGH

        // LOAD PWM GENERATOR TIMING SETTINGS FROM BUCK CONVERTER OBJECT
        pg->PGxCONH.bits.MPERSEL = (uint16_t)buckInstance->sw_node[_i].master_period_enable;
        
        pg->PGxDC.value = buckInstance->sw_node[_i].duty_ratio_min; // PGxDC: PWM GENERATOR x DUTY CYCLE REGISTER
        pg->PGxPER.value = buckInstance->sw_node[_i].period; // PGxPER: PWM GENERATOR x PERIOD REGISTER
        pg->PGxDTL.value = buckInstance->sw_node[_i].dead_time_falling; // PGxDTL: PWM GENERATOR x DEAD-TIME REGISTER LOW
        pg->PGxDTH.value = buckInstance->sw_node[_i].dead_time_rising; // PGxDTH: PWM GENERATOR x DEAD-TIME REGISTER HIGH
        pg->PGxLEBL.value = buckInstance->sw_node[_i].leb_period; // PWM GENERATOR x LEADING-EDGE BLANKING REGISTER LOW 
        
        // First switch-node object of array is used as master PWM
        if( _i == 0) {
            pg->PGxCONH.bits.MSTEN = 1; // Make first PWM of switch node objects MASTER
            pg->PGxCONH.bits.UPDMOD = P33C_PGxCONH_UPDMOD_MSTR; // Master PWM updates PWM registers Immediately
            pg->PGxCONH.bits.SOCS = 0b0000; // Master PWM is self-triggered
            pg->PGxEVTL.bits.PGTRGSEL = 0b011; // Master PWM uses PGxTRIGC as master trigger output
            pg->PGxTRIGC.bits.TRIG = buckInstance->sw_node[_i].phase; // Set phase shift of trigger
        }
        else {
            pg->PGxCONH.bits.MSTEN = 0; // Make all other PWMs of switch node objects SLAVES
            pg->PGxCONH.bits.UPDMOD = P33C_PGxCONH_UPDMOD_SLV; // Slave PWMs update PWM registers Immediately at MASTER trigger
            pg->PGxCONH.bits.SOCS = BUCK_PWM_MASTER_SOCS; // Slave PWMs are triggered by MASTER PWM
            pg->PGxEVTL.bits.PGTRGSEL = 0b000; // Slave PWM does not have PWM trigger output 
            pg->PGxTRIGC.bits.TRIG = buckInstance->sw_node[_i].phase; // Set phase shift of trigger
        }
        
        // Update PWM generator timing registers
        pg->PGxSTAT.bits.UPDREQ = 1;
        
    }
        
    return(retval);    
}

/* @@buckPWM_Start
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckPWM_Start(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance) 
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    volatile uint16_t timeout=0;
    volatile uint16_t pwm_Instance=0;
    volatile struct P33C_PWM_GENERATOR_s* pg;

    // Enable all PWM channels of the recent buck converter configuration
    for(_i=0; _i< buckInstance->set_values.no_of_phases; _i++) {
    
        // Capture PWM instance of the recent channel
        pwm_Instance = buckInstance->sw_node[_i].pwm_instance;
        
        // CAPTURE MEMORY ADDRESS OF GIVEN PWM GENERATOR INSTANCE
        pg   = (volatile struct P33C_PWM_GENERATOR_s*) 
            ((volatile uint16_t*)&PG1CONL + ((pwm_Instance - 1) * P33C_PWMGEN_SFR_OFFSET));

        pg->PGxIOCONL.value |= P33C_PGxIOCONL_OVREN; // PWMxH/L Output Override Enable: PWM generator controls the PWMxH output pin
        pg->PGxIOCONH.value &= ~(P33C_PGxIOCONH_PEN); // PWMxH/L Output Port Disable: PWM generator controls the PWMxH output pin

//        pg->PGxCONL.value |= P33C_PGxCONL_PWM_ON; // PWM Generator Enable: PWM Generator is enabled
//        pg->PGxSTAT.value |= P33C_PGxSTAT_UPDREQ; // Update all PWM timing registers

        pg->PGxCONL.bits.ON = 1;  // PWM Generator Enable: PWM Generator is enabled
        pg->PGxSTAT.bits.UPDREQ = 1;  // Update all PWM timing registers
        
        if(pg->PGxCONL.value & P33C_PGxCONL_HRES_EN) // If high resolution is enabled
        {
            while((!PCLKCONbits.HRRDY) && (timeout++ < 5000));  // wait for high resolution to get ready
            if ((timeout >= 5000) || (PCLKCONbits.HRERR))       // if there is an error ...
                return(0);                                      // ... exit returning ERROR
        }

        pg->PGxIOCONH.value |= P33C_PGxIOCONH_PEN; // PWMxH/L Output Port Enable: PWM generator controls the PWMxH output pin

        retval &= (volatile uint16_t)(pg->PGxCONL.bits.ON);

    }
    
    return(retval);    
}

/* @@buckPWM_Stop
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckPWM_Stop(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance) 
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    volatile uint16_t pwm_Instance=0;
    volatile struct P33C_PWM_GENERATOR_s* pg;

    // Disable all PWM channels of the recent buck converter configuration
    for(_i=0; _i< buckInstance->set_values.no_of_phases; _i++) {
    
            // Capture PWM instance of the recent channel
        pwm_Instance = buckInstance->sw_node[_i].pwm_instance;

        // CAPTURE MEMORY ADDRESS OF GIVEN PWM GENERATOR INSTANCE
        pg   = (volatile struct P33C_PWM_GENERATOR_s*) 
            ((volatile uint16_t*)&PG1CONL + ((pwm_Instance - 1) * P33C_PWMGEN_SFR_OFFSET));

        pg->PGxIOCONL.value |= P33C_PGxIOCONL_OVREN;  // PWMxH/L Output Override Enable
        pg->PGxIOCONH.value &= ~(P33C_PGxIOCONH_PEN); // PWMxH/L Output Pint Control Disable
        pg->PGxCONL.value &= ~(P33C_PGxCONL_PWM_ON);  // PWM Generator Disable
        pg->PGxDC.value = buckInstance->sw_node[_i].duty_ratio_min; // Reset Duty Cycle
        pg->PGxSTAT.value |= P33C_PGxSTAT_UPDREQ;     // Set the Update Request bit to update PWM timing
        
        retval &= (volatile uint16_t)((volatile bool)(pg->PGxCONL.bits.ON == 0));

    }
        
    return(retval);    
}

/* @@buckPWM_Suspend
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckPWM_Suspend(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance) 
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    volatile uint16_t pwm_Instance;
    volatile struct P33C_PWM_GENERATOR_s* pg;

    // Disable all PWM outputs of the recent buck converter configuration
    for(_i=0; _i< buckInstance->set_values.no_of_phases; _i++) {
    
            // Capture PWM instance of the recent channel
        pwm_Instance = buckInstance->sw_node[_i].pwm_instance;

        // CAPTURE MEMORY ADDRESS OF GIVEN PWM GENERATOR INSTANCE
        pg   = (volatile struct P33C_PWM_GENERATOR_s*) 
            ((volatile uint16_t*)&PG1CONL + ((pwm_Instance - 1) * P33C_PWMGEN_SFR_OFFSET));
        
        pg->PGxIOCONL.value |= P33C_PGxIOCONL_OVREN; // PWMxH/L Output Override Enable
        pg->PGxDC.value = 0;  // Reset Duty Cycle
        pg->PGxSTAT.value |= P33C_PGxSTAT_UPDREQ; // Set the Update Request bit to update PWM timing

        retval &= (bool)(pg->PGxIOCONL.value & P33C_PGxIOCONL_OVREN);

    }
    
    return(retval);    
}

/* @@<function_name>
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckPWM_Resume(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance) 
{
    volatile uint16_t retval=1;
    volatile uint16_t _i=0;
    volatile uint16_t pwm_Instance=0;
    volatile struct P33C_PWM_GENERATOR_s* pg;

    // Disable all PWM channels of the recent buck converter configuration
    for(_i=0; _i< buckInstance->set_values.no_of_phases; _i++) {
    
            // Capture PWM instance of the recent channel
        pwm_Instance = (uint16_t)buckInstance->sw_node[_i].pwm_instance;

        // CAPTURE MEMORY ADDRESS OF GIVEN PWM GENERATOR INSTANCE
        pg   = (volatile struct P33C_PWM_GENERATOR_s*) 
            ((volatile uint16_t*)&PG1CONL + ((pwm_Instance - 1) * P33C_PWMGEN_SFR_OFFSET));
    
        pg->PGxSTAT.bits.UPDREQ = 1; // Set the Update Request bit to update PWM timing
        pg->PGxIOCONL.value &= (volatile uint16_t)(~(P33C_PGxIOCONL_OVREN)); // PWMxH/L Output Override Disable

        retval &= (uint16_t)((bool)(!(pg->PGxIOCONL.value & P33C_PGxIOCONL_OVREN)));

    }
        
    return(retval);    
}

/* @@<function_name>
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckADC_ModuleInitialize(void) 
{
    volatile uint16_t retval=1;
    
    // Make sure power to peripheral is enabled
    PMD1bits.ADC1MD = 0; // ADC Module Power Disable: ADC module power is enabled
    
    // ADCON1L: ADC CONTROL REGISTER 1 LOW
    ADCON1Lbits.ADON = 0; // ADC Enable: ADC module is off during configuration
    ADCON1Lbits.ADSIDL = 0; // ADC Stop in Idle Mode: Continues module operation in Idle mode
    
    // ADCON1H: ADC CONTROL REGISTER 1 HIGH
    ADCON1Hbits.SHRRES = 0b11; // Shared ADC Core Resolution Selection: 12-bit resolution ADC resolution = 12-bit (0...4095 ticks)
    ADCON1Hbits.FORM = 0; // Fractional Data Output Format: Integer

    // ADCON2L: ADC CONTROL REGISTER 2 LOW
    ADCON2Lbits.REFCIE = 0;; // Band Gap and Reference Voltage Ready Common Interrupt Enable: Common interrupt is disabled for the band gap ready event
    ADCON2Lbits.REFERCIE = 0; // Band Gap or Reference Voltage Error Common Interrupt Enable: Disabled
    ADCON2Lbits.EIEN = 1; // Early Interrupts Enable: The early interrupt feature is enabled
    ADCON2Lbits.SHREISEL = 0b111; // Shared Core Early Interrupt Time Selection: Early interrupt is set and interrupt is generated 8 TADCORE clocks prior to when the data are ready
    ADCON2Lbits.SHRADCS = 0b0000001; // Shared ADC Core Input Clock Divider: 2:1 (minimum)

    // ADCON2H: ADC CONTROL REGISTER 2 HIGH
    ADCON2Hbits.SHRSAMC = 8; // Shared ADC Core Sample Time Selection: 8x TADs sampling time 
    ADCON2Hbits.REFERR = 0; // reset error flag
    ADCON2Hbits.REFRDY = 0; // reset bandgap status bit

    // ADCON3L: ADC CONTROL REGISTER 3 LOW
    ADCON3Lbits.REFSEL = 0b000; // ADC Reference Voltage Selection: AVDD-toAVSS
    ADCON3Lbits.SUSPEND = 0; // All ADC Core Triggers Disable: All ADC cores can be triggered
    ADCON3Lbits.SUSPCIE = 0; // Suspend All ADC Cores Common Interrupt Enable: Common interrupt is not generated for suspend ADC cores
    ADCON3Lbits.SUSPRDY = 0; // All ADC Cores Suspended Flag: ADC cores have previous conversions in progress
    ADCON3Lbits.SHRSAMP = 0; // Shared ADC Core Sampling Direct Control: use hardware trigger
    ADCON3Lbits.CNVRTCH = 0; // Software Individual Channel Conversion Trigger: Next individual channel conversion trigger can be generated (not used)
    ADCON3Lbits.SWLCTRG = 0; // Software Level-Sensitive Common Trigger: No software, level-sensitive common triggers are generated (not used)
    ADCON3Lbits.SWCTRG = 0; // Software Common Trigger: Ready to generate the next software common trigger (not used)
    ADCON3Lbits.CNVCHSEL = 0; // Channel Number Selection for Software Individual Channel Conversion Trigger: AN0 (not used)
    
    // ADCON3H: ADC CONTROL REGISTER 3 HIGH
    ADCON3Hbits.CLKSEL = 0b01; // ADC Module Clock Source Selection: AVCODIV
    ADCON3Hbits.CLKDIV = 0b000000; // ADC Module Clock Source Divider: 1 Source Clock Period
    ADCON3Hbits.SHREN = 0; // Shared ADC Core Enable: Shared ADC core is disabled
    ADCON3Hbits.C0EN = 0; // Dedicated ADC Core 0 Enable: Dedicated ADC Core 0 is disabled
    ADCON3Hbits.C1EN = 0; // Dedicated ADC Core 1 Enable: Dedicated ADC Core 1 is disabled
    
    // ADCON4L: ADC CONTROL REGISTER 4 LOW
    ADCON4Lbits.SAMC0EN = 0;  // Dedicated ADC Core 0 Conversion Delay Enable: Immediate conversion
    ADCON4Lbits.SAMC1EN = 0;  // Dedicated ADC Core 1 Conversion Delay Enable: Immediate conversion
    
    // ADCON4H: ADC CONTROL REGISTER 4 HIGH
    ADCON4Hbits.C0CHS = 0b00; // Dedicated ADC Core 0 Input Channel Selection: AN0
    ADCON4Hbits.C1CHS = 0b01; // Dedicated ADC Core 1 Input Channel Selection: ANA1

    // ADCON5L: ADC CONTROL REGISTER 5 LOW
    // ADCON5Lbits.SHRRDY: Shared ADC Core Ready Flag (read only)
    // ADCON5Lbits.C0RDY: Dedicated ADC Core 0 Ready Flag (read only)
    // ADCON5Lbits.C1RDY: Dedicated ADC Core 1 Ready Flag (read only)
    ADCON5Lbits.SHRPWR = 0; // Shared ADC Core Power Enable: ADC core is off
    ADCON5Lbits.C0PWR = 0; // Dedicated ADC Core 0 Power Enable: ADC core is off
    ADCON5Lbits.C1PWR = 0; // Dedicated ADC Core 1 Power Enable: ADC core is off
  
    // ADCON5H: ADC CONTROL REGISTER 5 HIGH
    ADCON5Hbits.WARMTIME = 0b1111; // ADC Dedicated Core x Power-up Delay: 32768 Source Clock Periods
    ADCON5Hbits.SHRCIE = 0; // Shared ADC Core Ready Common Interrupt Enable: Common interrupt is disabled for an ADC core ready event
    ADCON5Hbits.C0CIE = 0; // C1CIE: Dedicated ADC Core 0 Ready Common Interrupt Enable: Common interrupt is disabled
    ADCON5Hbits.C1CIE = 0; // C1CIE: Dedicated ADC Core 1 Ready Common Interrupt Enable: Common interrupt is disabled
    
    // ADCORExL: DEDICATED ADC CORE x CONTROL REGISTER LOW
    ADCORE1Lbits.SAMC = 0b0000000000;   // Dedicated ADC Core 1 Conversion Delay Selection: 2 TADCORE (minimum)
    ADCORE0Lbits.SAMC = 0b0000000000;   // Dedicated ADC Core 0 Conversion Delay Selection: 2 TADCORE (minimum)

    // ADCORExH: DEDICATED ADC CORE x CONTROL REGISTER HIGH
    ADCORE0Hbits.RES = 0b11; // ADC Core x Resolution Selection: 12 bit
    ADCORE0Hbits.ADCS = 0b0000000; // ADC Core x Input Clock Divider: 2 Source Clock Periods
    ADCORE0Hbits.EISEL = 0b111; // Early interrupt is set and an interrupt is generated 8 TADCORE clocks prior

    ADCORE1Hbits.RES = 0b11; // ADC Core x Resolution Selection: 12 bit
    ADCORE1Hbits.ADCS = 0b0000000; // ADC Core x Input Clock Divider: 2 Source Clock Periods
    ADCORE1Hbits.EISEL = 0b111; // Early interrupt is set and an interrupt is generated 8 TADCORE clocks prior
    
    return(retval);    
}

/* @@<function_name>
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckADC_ChannelInitialize(volatile BUCK_ADC_INPUT_SETTINGS_t* adc_Instance) 
{
    volatile uint16_t retval=1;
    volatile uint8_t* ptrADCRegister;
    volatile uint8_t bit_offset;
    
    // Initialize ADC input registers
    if (adc_Instance->enabled) {

        // Write level trigger setting
        if (adc_Instance->adc_input < 16) {
            ADLVLTRGL |= ((uint16_t)(adc_Instance->level_trigger) << adc_Instance->adc_input);
            ADEIEL |= ((uint16_t)(adc_Instance->early_interrupt_enable) << adc_Instance->adc_input);
            ADIEL |= ((uint16_t)(adc_Instance->interrupt_enable) << adc_Instance->adc_input);
        }
        else if (adc_Instance->adc_input < 32) {
            ADLVLTRGH |= ((uint16_t)(adc_Instance->level_trigger) << (adc_Instance->adc_input - 16));
            ADEIEH |= ((uint16_t)(adc_Instance->early_interrupt_enable) << (adc_Instance->adc_input - 16));
            ADIEH |= ((uint16_t)(adc_Instance->interrupt_enable) << (adc_Instance->adc_input - 16));
        }
        else {
            return(0); // ADC input number out of range
        }

        // write input mode setting
        if (adc_Instance->adc_input < 8)
            bit_offset = (2 * adc_Instance->adc_input);
        else if (adc_Instance->adc_input < 16)
            bit_offset = (2 * (adc_Instance->adc_input-8));
        else if (adc_Instance->adc_input < 24)
            bit_offset = (2 * (adc_Instance->adc_input-16));
        else if (adc_Instance->adc_input < 32)
            bit_offset = (2 * (adc_Instance->adc_input-24));
        else
            return(0); // ADC input number out of range

        ptrADCRegister = (volatile uint8_t *)
            ((volatile uint8_t *)&ADMOD0L + (volatile uint8_t)(adc_Instance->adc_input >> 8));
        
        *ptrADCRegister |= ((unsigned int)adc_Instance->signed_result << bit_offset);
        *ptrADCRegister |= ((unsigned int)adc_Instance->differential_input << (bit_offset + 1));
       
        // Write ADC trigger source setting
        ptrADCRegister = (volatile uint8_t *)
            ((volatile uint8_t *)&ADTRIG0L + (volatile uint8_t)adc_Instance->adc_input);
        
        *ptrADCRegister = (volatile uint8_t)adc_Instance->trigger_source;
        
        // Register ADC core to be active
        switch (adc_Instance->adc_core) {
            case 0:
                adcore_mask |= ADC_CORE0_MASK_INDEX;
                if (adc_Instance->differential_input)
                    adcore_diff_mask |= ADC_CORE0_MASK_INDEX;
                break;
            case 1:
                adcore_mask |= ADC_CORE1_MASK_INDEX;
                if (adc_Instance->differential_input)
                    adcore_diff_mask |= ADC_CORE1_MASK_INDEX;
                break;
            case 2:
                adcore_mask |= ADC_CORE2_MASK_INDEX;
                if (adc_Instance->differential_input)
                    adcore_diff_mask |= ADC_CORE2_MASK_INDEX;
                break;
            case 3:
                adcore_mask |= ADC_CORE3_MASK_INDEX;
                if (adc_Instance->differential_input)
                    adcore_diff_mask |= ADC_CORE3_MASK_INDEX;
                break;
            default:
                adcore_mask |= ADC_SHRCORE_MASK_INDEX;
                if (adc_Instance->differential_input)
                    adcore_diff_mask |= ADC_SHRCORE_MASK_INDEX;
                break;
        }
        
    }
    
    return(retval);
}

/* @@buckADC_Start
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckADC_Start(void) 
{
    volatile uint16_t retval=1;
    volatile uint16_t timeout=0;
    volatile uint16_t adcore_mask_compare=0;
    
    // Turn on ADC module
    ADCON1Lbits.ADON = 1;

    ADCON5L = adcore_mask;    // Enable power to all used ADC cores
    adcore_mask_compare = ((adcore_mask << 8) | adcore_mask); // Set ADC Core Ready Bit Mask
    
    while ((ADCON5L != adcore_mask_compare) & (timeout++ < ADC_POWERUP_TIMEOUT)); // Wait until ADC cores are ready
    if (timeout >= ADC_POWERUP_TIMEOUT) return(0); // Skip if powering up ADC cores was unsuccessful
    ADCON3H = adcore_mask; // Enable ADC cores


    return(retval);    
}

/* @@buckGPIO_Set
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckGPIO_Set(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance)
{
    volatile uint16_t retval=1;
    volatile struct P33C_GPIO_INSTANCE_s* gpio;

    // Capture register of GPIO port
    gpio = (volatile struct P33C_GPIO_INSTANCE_s*) 
        ((volatile uint8_t*)&ANSELA + (buckGPIOInstance->port * P33C_GPIO_SFR_OFFSET));
    
    // Set pin to ACTIVE state
    if (buckGPIOInstance->polarity == 0)
        gpio->LATx.value |= (0x0001 << buckGPIOInstance->pin); // Set pin bit in register
    else
        gpio->LATx.value &= ~(0x0001 << buckGPIOInstance->pin); // Clear pin bit in register            
    
    return(retval);
}

/* @@buckGPIO_Clear
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckGPIO_Clear(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance)
{
    volatile uint16_t retval=1;
    volatile struct P33C_GPIO_INSTANCE_s* gpio;

    // Capture register of GPIO port
    gpio = (volatile struct P33C_GPIO_INSTANCE_s*) 
        ((volatile uint8_t*)&ANSELA + (buckGPIOInstance->port * P33C_GPIO_SFR_OFFSET));
    
    // Set pin to INACTIVE state
    if (buckGPIOInstance->polarity == 0)
        gpio->LATx.value &= ~(0x0001 << buckGPIOInstance->pin); // Clear pin bit in register            
    else
        gpio->LATx.value |= (0x0001 << buckGPIOInstance->pin); // Set pin bit in register
    
    return(retval);
}


/* @@buckGPIO_GetPinState
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile bool buckGPIO_GetPinState(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance)
{
    volatile bool retval=1;
    volatile P33C_GPIO_INSTANCE_t* gpio;

    // Capture register of GPIO port
    gpio = (volatile P33C_GPIO_INSTANCE_t*) 
        ((volatile uint8_t*)&ANSELA + (buckGPIOInstance->port * P33C_GPIO_SFR_OFFSET));
    
    // Read pin 
    retval = (bool)(gpio->PORTx.value & (0x0001 << buckGPIOInstance->pin));
    
    // If polarity is inverted (ACTIVE LOW), invert result
    if(buckGPIOInstance->polarity == 1)
        retval = (1-retval);
    
    return(retval);
}

/* @@buckGPIO_PrivateInitialize
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckGPIO_PrivateInitialize(volatile struct BUCK_GPIO_INSTANCE_s* buckGPIOInstance)
{
    volatile uint16_t retval=1;
    volatile struct P33C_GPIO_INSTANCE_s* gpio;

    // Capture register of GPIO port
    gpio = p33c_GpioInstance_GetHandle(buckGPIOInstance->port);
//    gpio = (volatile struct P33C_GPIO_INSTANCE_s*) 
//        ((volatile uint8_t*)&ANSELA + (buckGPIOInstance->port * P33C_GPIO_SFR_OFFSET));
    
    // Set pin to INACTIVE state
    if (buckGPIOInstance->polarity == 0)
        gpio->LATx.value &= ~(0x0001 << buckGPIOInstance->pin); // Clear pin bit in register            
    else
        gpio->LATx.value |= (0x0001 << buckGPIOInstance->pin); // Set pin bit in register

    // Set INPUT or OUTPUT in TRIS register
    if(buckGPIOInstance->io_type == 0)
        gpio->TRISx.value &= ~(0x0001 << buckGPIOInstance->pin); // Clear pin bit in register
    else
        gpio->TRISx.value |= (0x0001 << buckGPIOInstance->pin); // Set pin bit in register
    
    // Set pin as DIGITAL IO
    gpio->ANSELx.value &= ~(0x0001 << buckGPIOInstance->pin); // Clear pin bit in register

    // ToDo: Enable register value testing to validate function result
    retval = 1;

    return(retval);
}


/* @@buckGPIO_Initialize
 * ********************************************************************************
 * Summary:
 * 
 * Parameters:
 * 
 * Returns:
 * 
 * Description:
 * 
 * ********************************************************************************/

volatile uint16_t buckGPIO_Initialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance)
{
    volatile uint16_t retval=1;

    // Initialize ENABLE input pin
    if(buckInstance->gpio.Enable.enabled)
        retval = buckGPIO_PrivateInitialize(&buckInstance->gpio.Enable);
    
    // Initialize POWER GOOD output pin
    if(buckInstance->gpio.PowerGood.enabled)
        retval = buckGPIO_PrivateInitialize(&buckInstance->gpio.PowerGood);


    return(retval);
    
}

// end of file
