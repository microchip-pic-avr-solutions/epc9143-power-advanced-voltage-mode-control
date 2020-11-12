;LICENSE / DISCLAIMER
; **********************************************************************************
; Microchip Technology Inc. and its subsidiaries.  You may use this software 
;  and any derivatives exclusively with Microchip products. 
;  
;  THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
;  EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
;  WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
;  PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
;  WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
;  
;  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
;  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
;  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
;  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
;  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
;  IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
;  ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE. 
;  
;  MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
;  TERMS.
; **********************************************************************************
; **********************************************************************************
;  SDK Version: z-Domain Control Loop Designer v0.9.12.642
;  CGS Version: Code Generator Script v3.0.0 (09/07/2020)
;  Author:      M91406
;  Date/Time:   11/11/2020 13:58:58
; **********************************************************************************
    
;------------------------------------------------------------------------------
; Define status flags bit positions
    .equ NPNZ16_STATUS_ENABLED,      15     ; bit position of the ENABLE control bit
    .equ NPNZ16_STATUS_INVERT_INPUT, 14     ; bit position of the INVERT_INPUT control bit
    .equ NPNZ16_STATUS_SWAP_SOURCE,  13     ; bit position of the SWAP_SOURCE control bit
    .equ NPNZ16_STATUS_SWAP_TARGET,  12     ; bit position of the SWAP_TARGET control bit
    .equ NPNZ16_STATUS_AGC_ENABLED,  11     ; bit position of the AGC_ENABLED control bit
    .equ NPNZ16_STATUS_USAT,         1      ; bit position of the UPPER_SATURATION_FLAG status bit
    .equ NPNZ16_STATUS_LSAT,         0      ; bit position of the LOWER_SATURATION_FLAG status bit
    
;------------------------------------------------------------------------------
; NPNZ16b_t data structure address offset declarations for data structure addressing
    .equ Status,                    0       ; controller object status word at address-offset = 0
    .equ ptrSourceRegister,         2       ; parameter group Ports.Source: pointer to source memory address
    .equ SourceNormShift,           4       ; parameter group Ports.Source: bit-shift scaler of normalization factor
    .equ SourceNormFactor,          6       ; parameter group Ports.Source: Q15 normalization factor
    .equ SourceOffset,              8       ; parameter group Ports.Source: value of source input signal/value offset
    .equ ptrAltSourceRegister,      10      ; parameter group Ports.AltSource: pointer to alternate source memory address
    .equ AltSourceNormShift,        12      ; parameter group Ports.AltSource: bit-shift scaler of normalization factor
    .equ AltSourceNormFactor,       14      ; parameter group Ports.AltSource: Q15 normalization factor
    .equ AltSourceOffset,           16      ; parameter group Ports.AltSource: value of alternate source input signal/value offset
    .equ ptrTargetRegister,         18      ; parameter group Ports.Target: pointer to target memory address
    .equ TargetNormShift,           20      ; parameter group Ports.Target: bit-shift scaler of normalization factor
    .equ TargetNormFactor,          22      ; parameter group Ports.Target: Q15 normalization factor
    .equ TargetOffset,              24      ; parameter group Ports.Target: value of target output signal/value offset
    .equ ptrAltTargetRegister,      26      ; parameter group Ports.AltTarget: pointer to alternate target memory address
    .equ AltTargetNormShift,        28      ; parameter group Ports.AltTarget: bit-shift scaler of normalization factor
    .equ AltTargetNormFactor,       30      ; parameter group Ports.AltTarget: Q15 normalization factor
    .equ AltTargetOffset,           32      ; parameter group Ports.AltTarget: value of alternate target output signal/value offset
    .equ ptrControlReference,       34      ; parameter group Ports.ConrolReference: pointer to control reference variable/register memory address
    .equ ptrACoefficients,          36      ; parameter group Filter: pointer to A-coefficients array start address
    .equ ptrBCoefficients,          38      ; parameter group Filter: pointer to B-coefficients array start address
    .equ ptrControlHistory,         40      ; parameter group Filter: pointer to control history array start address
    .equ ptrErrorHistory,           42      ; parameter group Filter: pointer to error history array start address
    .equ ACoefficientsArraySize,    44      ; parameter group Filter: size of the A-coefficients array
    .equ BCoefficientsArraySize,    46      ; parameter group Filter: size of the B-coefficients array
    .equ ControlHistoryArraySize,   48      ; parameter group Filter: size of the control history array
    .equ ErrorHistoryArraySize,     50      ; parameter group Filter: size of the error history array
    .equ normPreShift,              52      ; parameter group Filter: value of input value normalization bit-shift scaler
    .equ normPostShiftA,            54      ; parameter group Filter: value of A-term normalization bit-shift scaler
    .equ normPostShiftB,            56      ; parameter group Filter: value of B-term normalization bit-shift scaler
    .equ normPostScaler,            58      ; parameter group Filter: control loop output normalization factor
    .equ PTermScaler,               60      ; parameter group Filter: P-Term coefficient scaler
    .equ PTermFactor,               62      ; parameter group Filter: P-Term coefficient fractional factor
    .equ MinOutput,                 64      ; parameter group Limits: minimum clamping value of primary control output
    .equ MaxOutput,                 66      ; parameter group Limits: maximum clamping value of primary control output
    .equ AltMinOutput,              68      ; parameter group Limits: minimum clamping value of alternate control output
    .equ AltMaxOutput,              70      ; parameter group Limits: maximum clamping value of alternate control output
    .equ ptrADCTriggerARegister,    72      ; parameter group ADCTriggerControl: pointer to ADC trigger A register memory address
    .equ ADCTriggerAOffset,         74      ; parameter group ADCTriggerControl: value of ADC trigger A offset
    .equ ptrADCTriggerBRegister,    76      ; parameter group ADCTriggerControl: pointer to ADC trigger B register memory address
    .equ ADCTriggerBOffset,         78      ; parameter group ADCTriggerControl: value of ADC trigger B offset
    .equ ptrDProvControlInput,      80      ; parameter group DataProviders: pointer to external variable/register the most recent, raw control input will be pushed to
    .equ ptrDProvControlInputComp,  82      ; parameter group DataProviders: pointer to external variable/register the most recent, compensated control input will be pushed to
    .equ ptrDProvControlError,      84      ; parameter group DataProviders: pointer to external variable/register the most recent control error will be pushed to
    .equ ptrDProvControlOutput,     86      ; parameter group DataProviders: pointer to external variable/register the most recent control output will be pushed to
    .equ ptrCascadedFunction,       88      ; parameter group CascadeTrigger: pointer to external, cascaded function which will be called by this controller
    .equ CascadedFunctionParam,     90      ; parameter group CascadeTrigger: 16-bit wide function parameter or pointer to a parameter data structure of cascaded function
    .equ AgcScaler,                 92      ; parameter group GainControl: bit-shift scaler of Adaptive Gain Control Modulation factor
    .equ AgcFactor,                 94      ; parameter group GainControl: Q15 value of Adaptive Gain Control Modulation factor
    .equ AgcMedian,                 96      ; parameter group GainControl: Q15 value of Adaptive Gain Control Modulation nominal operating point
    .equ ptrAgcObserverFunction,    98      ; parameter group GainControl: function pointer to observer function updating the AGC modulation factor
    .equ usrParam1,                 100     ; parameter group Advanced: generic 16-bit wide, user-defined parameter #1 for user-defined, advanced control options
    .equ usrParam2,                 102     ; parameter group Advanced: generic 16-bit wide, user-defined parameter #2 for user-defined, advanced control options
    .equ usrParam3,                 104     ; parameter group Advanced: generic 16-bit wide, user-defined parameter #3 for user-defined, advanced control options
    .equ usrParam4,                 106     ; parameter group Advanced: generic 16-bit wide, user-defined parameter #4 for user-defined, advanced control options
    
;------------------------------------------------------------------------------
;end of include of NPNZ16B_t data structure and global constants
     
; **********************************************************************************
;  Download latest version of this tool here: https://areiter128.github.io/DCLD
; **********************************************************************************
