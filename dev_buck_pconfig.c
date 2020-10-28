/*
 * File:   drv_cuck_pconfig.c
 * Author: M91406
 *
 * Created on March 12, 2020, 4:31 PM
 */

// Include MCC peripheral driver files
#include "p33c_pwm.h"

// Include buck converter driver files
#include "pwr_control/devices/dev_buck_pconfig.h"
#include "pwr_control/devices/dev_buck_typedef.h"

/* PRIVATE VARIABLES */
volatile uint16_t adcore_mask=0;
volatile uint16_t adcore_diff_mask=0;



volatile uint16_t buckPWM_ModuleInitialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance)
{
    volatile uint16_t retval=1;
    volatile struct P33C_PWM_MODULE_SFRSET_s* pwm;
    
    // Make sure power to the peripheral is enabled
    PMD1bits.PWMMD = 0; // PWM Module Disable: PWM module is enabled
    
    // Initialize PWM module in default mode with Aux PLL = 500 MHz input frequency
    retval = p33c_PwmModule_Initialize();
    pwm = p33c_PwmModule_GetHandle();
    
    // If buck converter has been configured in MASTER PERIOD mode
    if (buckInstance->sw_node.master_period)
        pwm->vMPER.value = buckInstance->sw_node.period; // Set Period
    
    // Return success of PWM module configuration
    return(retval);    

}

volatile uint16_t buckPWM_VMC_Initialize(volatile struct BUCK_POWER_CONTROLLER_s* buckInstance)
{
    volatile uint16_t retval=1;

    volatile struct P33C_PWM_GENERATOR_s* pg;
    volatile struct P33C_GPIO_INSTANCE_s* gpio;
    volatile uint16_t gpio_Instance;

    // LOAD PERIPHERAL INSTANCES FROM BUCK CONVERTER OBJECT
    gpio_Instance = buckInstance->sw_node.gpio_instance;
    
    // CAPTURE MEMORY ADDRESS OF GIVEN PWM GENERATOR INSTANCE
    gpio = (volatile struct P33C_GPIO_INSTANCE_s*)((volatile struct P33C_GPIO_INSTANCE_s*) 
        ((volatile uint8_t*) &ANSELA + ((gpio_Instance - 1) * P33C_GPIO_SFR_OFFSET)));
    
    // Capture PWM generator instance used to drive buck converter
    pg = p33c_PwmGenerator_GetHandle(buckInstance->sw_node.pwm_instance);
    
    // WRITE GPIO CONFIGURATION OF PWM OUTPUT(S)
    gpio->LATx.value  &= ~(0x0001 << buckInstance->sw_node.gpio_high);  // Clear PWMxH output LOW
    gpio->LATx.value  &= ~(0x0001 << buckInstance->sw_node.gpio_low);   // Clear PWMxL output LOW
    gpio->TRISx.value &= ~(0x0001 << buckInstance->sw_node.gpio_high);  // Clear PWMxH output to OUTPUT
    gpio->TRISx.value &= ~(0x0001 << buckInstance->sw_node.gpio_low);   // Clear PWMxL output to OUTPUT
    gpio->CNPDx.value |= (0x0001 << buckInstance->sw_node.gpio_high); // Enable intern pull down register (PWM1H)
    gpio->CNPDx.value |= (0x0001 << buckInstance->sw_node.gpio_low); // Enable intern pull down register (PWM1L)
    
    // COPY CONFIGURATION FROM TEMPLATE TO PWM GENERATOR x CONTROL REGISTERS
    retval = p33c_PwmGenerator_ConfigWrite(buckInstance->sw_node.pwm_instance, pgConfigBuckPWM);

    // LOAD USER PWM GENERATOR CONFIGURATION FROM BUCK CONVERTER OBJECT
    pg->PGxPHASE.value = buckInstance->sw_node.phase; // PGxPHASE: PWM GENERATOR x PHASE REGISTER
    pg->PGxDC.value = buckInstance->sw_node.duty_ratio_min; // PGxDC: PWM GENERATOR x DUTY CYCLE REGISTER
    pg->PGxDCA.value = REG_PGxDCA; // PGxDCA: PWM GENERATOR x DUTY CYCLE ADJUSTMENT REGISTER (not used)
    pg->PGxPER.value = buckInstance->sw_node.period; // PGxPER: PWM GENERATOR x PERIOD REGISTER
    pg->PGxTRIGA.value = 0; // PGxTRIGA: PWM GENERATOR x TRIGGER A REGISTER
    pg->PGxTRIGB.value = 0; // PGxTRIGB: PWM GENERATOR x TRIGGER B REGISTER
    pg->PGxTRIGC.value = 0; // PGxTRIGC: PWM GENERATOR x TRIGGER C REGISTER
    pg->PGxDTL.value = buckInstance->sw_node.dead_time_falling; // PGxDTL: PWM GENERATOR x DEAD-TIME REGISTER LOW
    pg->PGxDTH.value = buckInstance->sw_node.dead_time_rising; // PGxDTH: PWM GENERATOR x DEAD-TIME REGISTER HIGH
    pg->PGxLEBL.value = buckInstance->sw_node.leb_period; // PWM GENERATOR x LEADING-EDGE BLANKING REGISTER LOW 

    pg->PGxCONL.bits.HREN = buckInstance->sw_node.hres_enable; // Enable/Disable High Resolution Mode
    
    return(retval);    
}

volatile uint16_t buckPWM_Start(volatile uint16_t pwmInstance) 
{
    volatile uint16_t retval=1;
    volatile uint16_t timeout=0;
    volatile struct P33C_PWM_GENERATOR_s* pg;
    

    pg = p33c_PwmGenerator_GetHandle(pwmInstance);
    
    pg->PGxIOCONL.value |= P33C_PGxIOCONL_OVREN; // PWMxH/L Output Override Enable: PWM generator controls the PWMxH output pin
    pg->PGxIOCONH.value &= ~(P33C_PGxIOCONH_PEN); // PWMxH/L Output Port Disable: PWM generator controls the PWMxH output pin
    
    pg->PGxCONL.value |= P33C_PGxCONL_PWM_ON; // PWM Generator Enable: PWM Generator is enabled
    pg->PGxSTAT.value |= P33C_PGxSTAT_UPDREQ; // Update all PWM registers

    if(pg->PGxCONL.value & P33C_PGxCONL_HRES_EN) { // If high resolution is enabled
        while((!PCLKCONbits.HRRDY) && (timeout++ < 5000));  // wait for high resolution to get ready
        if ((timeout >= 5000) || (PCLKCONbits.HRERR))       // if there is an error
            return(0);  // return ERROR
    }
    
    pg->PGxIOCONH.value |= P33C_PGxIOCONH_PEN; // PWMxH/L Output Port Enable: PWM generator controls the PWMxH output pin

    return(retval);    
}

volatile uint16_t buckPWM_Stop(volatile uint16_t pwmInstance) 
{
    volatile uint16_t retval=1;
    volatile struct P33C_PWM_GENERATOR_s* pg;

    pg = p33c_PwmGenerator_GetHandle(pwmInstance);
    
    pg->PGxIOCONL.value |= P33C_PGxIOCONL_OVREN;  // PWMxH/L Output Override Enable
    pg->PGxIOCONH.value &= ~(P33C_PGxIOCONH_PEN); // PWMxH/L Output Pint Control Disable
    pg->PGxCONL.value &= ~(P33C_PGxCONL_PWM_ON);  // PWM Generator Disable
    pg->PGxDC.value = 0; // Reset Duty Cycle
    pg->PGxSTAT.value |= P33C_PGxSTAT_UPDREQ;     // Set the Update Request bit to update PWM timing

    return(retval);    
}

volatile uint16_t buckPWM_Suspend(volatile uint16_t pwmInstance) 
{
    volatile uint16_t retval=1;
    volatile struct P33C_PWM_GENERATOR_s* pg;

    pg = p33c_PwmGenerator_GetHandle(pwmInstance);

    pg->PGxIOCONL.value |= P33C_PGxIOCONL_OVREN; // PWMxH/L Output Override Enable
    pg->PGxDC.value = 0;  // Reset Duty Cycle
    pg->PGxSTAT.value |= P33C_PGxSTAT_UPDREQ; // Set the Update Request bit to update PWM timing

    retval &= (bool)(pg->PGxIOCONL.value & P33C_PGxIOCONL_OVREN);

    return(retval);    
}


volatile uint16_t buckPWM_Resume(volatile uint16_t pwmInstance) 
{
    volatile uint16_t retval=1;
    volatile struct P33C_PWM_GENERATOR_s* pg;
    
    pg = p33c_PwmGenerator_GetHandle(pwmInstance);
    
    pg->PGxSTAT.value |= P33C_PGxSTAT_UPDREQ; // Set the Update Request bit to update PWM timing
    pg->PGxIOCONL.value &= ~(P33C_PGxIOCONL_OVREN); // PWMxH/L Output Override Disable

    retval = (bool)(pg->PGxIOCONL.value & P33C_PGxIOCONL_OVREN);

    return(retval);    
}


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
    ADCON2Lbits.PTGEN = 0; // External Conversion Request Interface: Disabled
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

volatile uint16_t buckADC_Channel_Initialize(volatile struct BUCK_ADC_INPUT_SETTINGS_s* adcInstance) 
{
    volatile uint16_t retval=1;
    volatile uint8_t* ptrADCRegister;
    volatile uint8_t bit_offset;
    
    // Initialize ADC input registers
    if (adcInstance->enabled) {

        // Write level trigger setting
        if (adcInstance->adc_input < 16) {
            ADLVLTRGL |= ((uint16_t)(adcInstance->level_trigger) << adcInstance->adc_input);
            ADEIEL |= ((uint16_t)(adcInstance->early_interrupt_enable) << adcInstance->adc_input);
            ADIEL |= ((uint16_t)(adcInstance->interrupt_enable) << adcInstance->adc_input);
        }
        else if (adcInstance->adc_input < 32) {
            ADLVLTRGH |= ((uint16_t)(adcInstance->level_trigger) << (adcInstance->adc_input - 16));
            ADEIEH |= ((uint16_t)(adcInstance->early_interrupt_enable) << (adcInstance->adc_input - 16));
            ADIEH |= ((uint16_t)(adcInstance->interrupt_enable) << (adcInstance->adc_input - 16));
        }
        else {
            return(0); // ADC input number out of range
        }

        // write input mode setting
        ptrADCRegister = (volatile uint8_t *)((volatile uint8_t *)&ADMOD0L + (volatile uint8_t)(adcInstance->adc_input >> 8));
        if (adcInstance->adc_input < 8)
            bit_offset = (2 * adcInstance->adc_input);
        else if (adcInstance->adc_input < 16)
            bit_offset = (2 * (adcInstance->adc_input-8));
        else if (adcInstance->adc_input < 24)
            bit_offset = (2 * (adcInstance->adc_input-16));
        else if (adcInstance->adc_input < 32)
            bit_offset = (2 * (adcInstance->adc_input-24));
        else
            return(0); // ADC input number out of range
        
        *ptrADCRegister |= ((unsigned int)adcInstance->signed_result << bit_offset);
        *ptrADCRegister |= ((unsigned int)adcInstance->differential_input << (bit_offset + 1));
       
        // Write ADC trigger source setting
        ptrADCRegister = (volatile uint8_t *)((volatile uint8_t *)&ADTRIG0L + adcInstance->adc_input);
        *ptrADCRegister = adcInstance->trigger_source;
        
        // Register ADC core to be active
        switch (adcInstance->adc_core) {
            case 0:
                adcore_mask |= ADC_CORE0_MASK_INDEX;
                if (adcInstance->differential_input)
                    adcore_diff_mask |= ADC_CORE0_MASK_INDEX;
                break;
            case 1:
                adcore_mask |= ADC_CORE1_MASK_INDEX;
                if (adcInstance->differential_input)
                    adcore_diff_mask |= ADC_CORE1_MASK_INDEX;
                break;
            case 2:
                adcore_mask |= ADC_CORE2_MASK_INDEX;
                if (adcInstance->differential_input)
                    adcore_diff_mask |= ADC_CORE2_MASK_INDEX;
                break;
            case 3:
                adcore_mask |= ADC_CORE3_MASK_INDEX;
                if (adcInstance->differential_input)
                    adcore_diff_mask |= ADC_CORE3_MASK_INDEX;
                break;
            default:
                adcore_mask |= ADC_SHRCORE_MASK_INDEX;
                if (adcInstance->differential_input)
                    adcore_diff_mask |= ADC_SHRCORE_MASK_INDEX;
                break;
        }
        
    }
    
    return(retval);
}

volatile uint16_t buckADC_Start(void) 
{
    volatile uint16_t retval=1;
    volatile uint16_t timeout=0;
    volatile uint16_t adcore_mask_compare=0;
    
    // Turn on ADC module
    ADCON1Lbits.ADON = 1;

    ADCON5L = adcore_mask;    // Enable power to all used ADC cores
    adcore_mask_compare = ((adcore_mask << 8) | adcore_mask); // Set ADC Core Ready Bit Mask
    
    while ((ADCON5L != adcore_mask_compare) & (timeout++ < ADC_POWRUP_TIMEOUT)); // Wait until ADC cores are ready
    if (timeout >= ADC_POWRUP_TIMEOUT) return(0); // Skip if powering up ADC cores was unsuccessful
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
    volatile struct P33C_GPIO_INSTANCE_s* gpio;

    // Capture register of GPIO port
    gpio = (volatile struct P33C_GPIO_INSTANCE_s*) 
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
    gpio = (volatile struct P33C_GPIO_INSTANCE_s*) 
        ((volatile uint8_t*)&ANSELA + (buckGPIOInstance->port * P33C_GPIO_SFR_OFFSET));
    
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
