/* 
 * File:   hal_adc.h
 * Author: Mohamed
 *
 * Created on September 21, 2023, 2:15 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H


/*------------------- Includes -------------------*/
#include <pic18f4620.h>
#include "hal_adc_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/*------------------- Macro Declarations -------------------*/
#define ADC_PORT_CFG_AN0_ANALOG            0x0E
#define ADC_PORT_CFG_AN1_ANALOG            0x0D
#define ADC_PORT_CFG_AN2_ANALOG            0x0C
#define ADC_PORT_CFG_AN3_ANALOG            0x0B
#define ADC_PORT_CFG_AN4_ANALOG            0x0A
#define ADC_PORT_CFG_AN5_ANALOG            0x09
#define ADC_PORT_CFG_AN6_ANALOG            0x08
#define ADC_PORT_CFG_AN7_ANALOG            0x07
#define ADC_PORT_CFG_AN8_ANALOG            0x06
#define ADC_PORT_CFG_AN9_ANALOG            0x05
#define ADC_PORT_CFG_AN10_ANALOG           0x04
#define ADC_PORT_CFG_AN11_ANALOG           0x03
#define ADC_PORT_CFG_AN12_ANALOG           0x02
#define ADC_PORT_CFG_ALL_ANALOG            0x00
#define ADC_PORT_CFG_ALL_DIGITAL           0x0F

#define ADC_ENABLE_VOLTAGE    0x01
#define ADC_DISABLE_VOLTAGE   0x00

/*------------------- Macro Functions Declarations -------------------*/
/* A/D Conversion Status bit => A/D conversion in progress // A/D Idle */
#define ADC_CONVERTION_STATUS()              (ADCON0bits.GO_nDONE)
/* ADC Start Convertion */
#define ADC_START_CONVERTION()               (ADCON0bits.GO_nDONE = 1) 
/* Enable and Disable ADC*/
#define ADC_ON()                              (ADCON0bits.ADON = 1)
#define ADC_OFF()                             (ADCON0bits.ADON = 0)

#define ADC_SELECT_CHANNEL_ANALOG(_CFG)            (ADCON0bits.CHS = _CFG)
/* : Voltage Reference Configuration Select : (1 = VREF && 1 = VREF+)  ||  (0 = VSS &&0 = VDD) */
#define ADC_ENABLE_VOLTAGE_REFERENCE()          do{ADCON1bits.VCFG0 = 1;\
                                                    ADCON1bits.VCFG1 = 1;\
                                                }while(0)
#define ADC_DISABLE_VOLTAGE_REFERENCE()         do{ADCON1bits.VCFG0 = 0;\
                                                    ADCON1bits.VCFG1= 1;\
                                                }while(0)
/*  A/D Port Configuration Control bits: when _CFG = ADC_PORT_CFG_AN5_ANALOG
 * so AN0, AN1, AN2, AN3, AN4, AN5 is ANALOG FUNCTIONALITY
 */
#define ADC_ANALOG_DIGITAL_CONTROL(_CFG)      (ADCON1bits.PCFG = _CFG)
/*  Result Format is a  Right justified always */
#define ADC_RESULT_FORMAT()                   (ADCON2bits.ADFM = 1)
/*  Acquisition Time Select bits */
#define ADC_SELECT_AQUISITION_TIME(_CFG)             (ADCON2bits.ACQT = _CFG)
/*  Conversion Clock Select bits */
#define SELECT_CONVERSION_CLOCK(_CFG)                (ADCON2bits.ADCS = _CFG)

/*------------------- Data Type Declarations -------------------*/
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}adc_Channel_Select_t;

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
}adc_aquisition_time_t;

typedef enum{
    ADC_FOSC_DIV_2 = 0,
    ADC_FOSC_DIV_8,
    ADC_FOSC_DIV_32,
    ADC_FRC,
    ADC_FOSC_DIV_4,
    ADC_FOSC_DIV_16,
    ADC_FOSC_DIV_64,
}adc_convertion_clock_t;

typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* ADC_InterruptHandler)(void);
    interrupt_priority priority;
#endif
    adc_aquisition_time_t aquisition_time;    /* @ref adc_aquisition_time_t */
    adc_convertion_clock_t convertion_clock;  /* @ref adc_convertion_clock_t */
    adc_Channel_Select_t Channel_Select;      /* @ref  adc_Channel_Select_t */
    uint8 voltage_reference : 1;
}adc_cfg_t;

/*------------------- Software Interfaces -------------------*/
Std_ReturnType ADC_Initilize(const adc_cfg_t *_adc);
Std_ReturnType ADC_Deinitilize(const adc_cfg_t *_adc);
Std_ReturnType ADC_Select_Channel(const adc_cfg_t *_adc, adc_Channel_Select_t channel);
Std_ReturnType ADC_Start_Conversion(const adc_cfg_t *_adc);
Std_ReturnType ADC_IsConversionDone(const adc_cfg_t *_adc, uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_cfg_t *_adc, uint16 *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const adc_cfg_t *_adc, adc_Channel_Select_t channel, uint16 *conversion_result);
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
Std_ReturnType ADC_StartConversion_Interrupt(const adc_cfg_t *_adc, adc_Channel_Select_t channel);
#endif

#endif	/* HAL_ADC_H */

