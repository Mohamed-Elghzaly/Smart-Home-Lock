/* 
 * File:   hal_adc.c
 * Author: Mohamed
 *
 * Created on September 21, 2023, 2:15 PM
 */
#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(*_ADC_InterruptHandler)(void) = NULL;
#endif

static inline void adc_input_channel_port_cfg(adc_Channel_Select_t channel);
static inline void adc_select_voltage_reference(const adc_cfg_t *_adc);

/**
 * @breif initialize ADC module
 * @param _adc : Pointer to ADC configuration
 * @return status of the function => E_OK     function done successfully 
 *                                   E_NOT_OK function has issues
 */
Std_ReturnType ADC_Initilize(const adc_cfg_t *_adc){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _adc){
        status = E_NOT_OK;
    }
    else{
        ADC_OFF();
        ADC_SELECT_AQUISITION_TIME(_adc->aquisition_time);
        SELECT_CONVERSION_CLOCK(_adc->convertion_clock);
        ADC_SELECT_CHANNEL_ANALOG(_adc->Channel_Select);
        adc_input_channel_port_cfg(_adc->Channel_Select);
        #if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_CLEAR_FLAG();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if(HIGH_PRIORITY_INTERRUPT == _adc->priority){
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            ADC_INTERRUPT_PRIORITY_HIGH();
            INTERRUPT_PRIORITY_ENABLE();
        }
        else if(LOW_PRIORITY_INTERRUPT == _adc->priority){
            ADC_INTERRUPT_PRIORITY_LOW();
            INTERRUPT_PRIORITY_DISABLE();
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        }
        else{/* Nothing */}
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif
        _ADC_InterruptHandler = _adc->ADC_InterruptHandler;
        #endif
        ADC_RESULT_FORMAT();
        adc_select_voltage_reference(_adc);
        ADC_ON();
        status = E_OK;
    }
    return status;
}

/**
 * @breif deinitialize ADC module
 * @param _adc : Pointer to ADC configuration
 * @return status of the function => E_OK     function done successfully 
 *                                   E_NOT_OK function has issues
 */
Std_ReturnType ADC_Deinitilize(const adc_cfg_t *_adc){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _adc){
        status = E_NOT_OK;
    }
    else{
        ADC_OFF();
        #if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_CLEAR_FLAG();
        ADC_INTERRUPT_DISABLE();
        #endif
        status = E_OK;
    }
    return status;
}

/**
 * 
 * @param _adc : Pointer to ADC configuration
 * @param channel : select channel of ADC
 * @return status of the function => E_OK     function done successfully 
 *                                   E_NOT_OK function has issues
 */
Std_ReturnType ADC_Select_Channel(const adc_cfg_t *_adc, adc_Channel_Select_t channel){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _adc){
        status = E_NOT_OK;
    }
    else{
        ADC_SELECT_CHANNEL_ANALOG(channel);
        adc_input_channel_port_cfg(channel);
        channel = _adc->Channel_Select;
        status = E_OK;
    }
    return status;
}

/**
 * 
 * @param _adc : Pointer to ADC configuration
 * @return status of the function => E_OK     function done successfully 
 *                                   E_NOT_OK function has issues
 */
Std_ReturnType ADC_Start_Conversion(const adc_cfg_t *_adc){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _adc){
        status = E_NOT_OK;
    }
    else{
        ADC_START_CONVERTION();
        status = E_OK;
    }
    return status;
}

/**
 * 
 * @param _adc : Pointer to ADC configuration
 * @param conversion_status : Pointer to status of conversion 
 * @return status of the function => E_OK     function done successfully 
 *                                   E_NOT_OK function has issues
 */
Std_ReturnType ADC_IsConversionDone(const adc_cfg_t *_adc, uint8 *conversion_status){
    Std_ReturnType status = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_status)){
        status = E_NOT_OK;
    }
    else{
        *conversion_status = !(ADCON0bits.GODONE);
    }
    return status;
}

/**
 * 
 * @param _adc : Pointer to ADC configuration
 * @param conversion_result : pointer to result of conversion
 * @return status of the function => E_OK     function done successfully 
 *                                   E_NOT_OK function has issues
 */
Std_ReturnType ADC_GetConversionResult(const adc_cfg_t *_adc, uint16 *conversion_result){
    Std_ReturnType status = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_result)){
        status = E_NOT_OK;
    }
    else{
        *conversion_result = (uint16)((ADRESH << 8) + ADRESL);
        status = E_OK;
    }
    return status;
}

/**
 * 
 * @param _adc : Pointer to ADC configuration
 * @param channel : select channel of ADC
 * @param conversion_result
 * @return status of the function => E_OK     function done successfully 
 *                                   E_NOT_OK function has issues
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_cfg_t *_adc, adc_Channel_Select_t channel, uint16 *conversion_result){
    Std_ReturnType status = E_NOT_OK;
    uint8 l_conversion_status = 0;
    if((NULL == _adc) || (NULL == conversion_result)){
        status = E_NOT_OK;
    }
    else{
        status = ADC_Select_Channel(_adc, channel);
        status = ADC_Start_Conversion(_adc);
        while(ADCON0bits.GODONE);
        status = ADC_GetConversionResult(_adc, conversion_result);

    }
    return status;
}
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
Std_ReturnType ADC_StartConversion_Interrupt(const adc_cfg_t *_adc, adc_Channel_Select_t channel){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _adc){
        status = E_NOT_OK;
    }
    else{
        status = ADC_Select_Channel(_adc, channel);
        status = ADC_Start_Conversion(_adc);
    }
    return status;
}
#endif

static inline void adc_input_channel_port_cfg(adc_Channel_Select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 :  SET_BIT(TRISA, _TRISA_TRISA0_POSN); break;
        case ADC_CHANNEL_AN1 :  SET_BIT(TRISA, _TRISA_TRISA1_POSN); break;
        case ADC_CHANNEL_AN2 :  SET_BIT(TRISA, _TRISA_TRISA2_POSN); break;
        case ADC_CHANNEL_AN3 :  SET_BIT(TRISA, _TRISA_TRISA3_POSN); break;
        case ADC_CHANNEL_AN4 :  SET_BIT(TRISA, _TRISA_TRISA5_POSN); break;
        case ADC_CHANNEL_AN5 :  SET_BIT(TRISE, _TRISE_TRISE0_POSN); break;
        case ADC_CHANNEL_AN6 :  SET_BIT(TRISE, _TRISE_TRISE1_POSN); break;
        case ADC_CHANNEL_AN7 :  SET_BIT(TRISE, _TRISE_TRISE2_POSN); break;
        case ADC_CHANNEL_AN8 :  SET_BIT(TRISB, _TRISB_TRISB2_POSN); break;
        case ADC_CHANNEL_AN9 :  SET_BIT(TRISB, _TRISB_TRISB3_POSN); break;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISB_TRISB1_POSN); break;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, _TRISB_TRISB4_POSN); break;
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, _TRISB_TRISB0_POSN); break;
        default : ;
    }
}

static inline void adc_select_voltage_reference(const adc_cfg_t *_adc){
    if(ADC_ENABLE_VOLTAGE == _adc->voltage_reference){
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if(ADC_DISABLE_VOLTAGE == _adc->voltage_reference){
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else{
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
}

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void ADC_ISR(void){
    ADC_INTERRUPT_CLEAR_FLAG();
    if(_ADC_InterruptHandler){
        _ADC_InterruptHandler();
    }
}
#endif