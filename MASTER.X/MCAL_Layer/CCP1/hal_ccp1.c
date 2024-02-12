/* 
 * File:   hal_ccp1.c
 * Author: Mohamed
 *
 * Created on September 27, 2023, 10:26 PM
 */

#include "hal_ccp1.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* CCP1_InterruptHandler)(void) = NULL;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* CCP2_InterruptHandler)(void) = NULL;
#endif

static void CCP_Interrupt_CFG(const ccp_t *_obj);
static void CCP_Capture_Compare_Time(const ccp_t *_obj);

#if (CCP1_CFG_MODE_SELECTED==CCP_CFG_PWM_MODE) || (CCP2_CFG_MODE_SELECTED==CCP_CFG_PWM_MODE)
Std_ReturnType CCP_PWM_Initialize(const ccp_t *_obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _obj){
        status = E_NOT_OK;
    }
    else{
        if(CCP1_MODULE == _obj->select_module){
            if(CCP_PWM_MODE == _obj->ccp_mode){
                CCP1_MODE_SELECT(CCP_PWM_MODE);
            }else{/* Nothing */}
            TRISCbits.RC2 = 0;
            LATCbits.LC2 = 0;
            CCP_Interrupt_CFG(_obj);
        }
        else if(CCP2_MODULE == _obj->select_module){
            CCP2_MODE_SELECT(CCP_MODULE_DISABLED);
            if(CCP_PWM_MODE == _obj->ccp_mode){
                CCP2_MODE_SELECT(CCP_PWM_MODE);
            }else{/* Nothing */}
            TRISCbits.RC1 = 0;
            LATCbits.LC1 = 0;
            CCP_Interrupt_CFG(_obj);
        }
        else{/* Nothing */}
        
        PR2 = (uint8)((_XTAL_FREQ / (_obj->PWM_frequancy * 4.0 * _obj->prescaler_value * _obj->postscaler_value))-1);

        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_PWM_Deinitialize(const ccp_t *_obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _obj){
        status = E_NOT_OK;
    }
    else{
        if(CCP1_MODULE == _obj->select_module){
        CCP1_MODE_SELECT(CCP_MODULE_DISABLED);
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_DISABLE();
#endif
        }
        else if(CCP2_MODULE == _obj->select_module){
        CCP2_MODE_SELECT(CCP_MODULE_DISABLED);
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP2_INTERRUPT_DISABLE();
#endif
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_obj, const uint8 _duty){
    Std_ReturnType status = E_NOT_OK;
    uint16 l_duty_temp = 0;
    if(NULL == _obj){
        status = E_NOT_OK;
    }else{
        l_duty_temp = (uint16)((PR2+1) * (_duty / 100.0) * 4);
        if(CCP1_MODULE == _obj->select_module){
            CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
            CCPR1L =(uint8)(l_duty_temp >> 2);
        }
        else if(CCP2_MODULE == _obj->select_module){
            CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
            CCPR2L =(uint8)(l_duty_temp >> 2);
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_PWM_Start(const ccp_t *_obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _obj){
        status = E_NOT_OK;
    }else{
        if(CCP1_MODULE == _obj->select_module){
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else if(CCP2_MODULE == _obj->select_module){
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_PWM_Stop(const ccp_t *_obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _obj){
        status = E_NOT_OK;
    }else{
        if(CCP1_MODULE == _obj->select_module){
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLED;
        }
        else if(CCP2_MODULE == _obj->select_module){
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLED;
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}
#endif

#if (CCP1_CFG_MODE_SELECTED==CCP_CFG_COMPARE_MODE) || (CCP2_CFG_MODE_SELECTED==CCP_CFG_COMPARE_MODE)
Std_ReturnType CCP_CompareMode_Initialize(const ccp_t *_obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _obj){
        status = E_NOT_OK;
    }
    else{ 
        if(CCP1_MODULE == _obj->select_module){
            CCP1_MODE_SELECT(CCP_MODULE_DISABLED);
            switch(_obj->ccp_mode){
                case CCP_COMPARE_MODE_SET_PIN: 
                CCP1_MODE_SELECT(CCP_COMPARE_MODE_SET_PIN); 
                break;
                case CCP_COMPARE_MODE_CLEAR_PIN: 
                CCP1_MODE_SELECT(CCP_COMPARE_MODE_CLEAR_PIN); 
                break;
                case CCP_COMPARE_MODE_TOGGLE_PIN: 
                CCP1_MODE_SELECT(CCP_COMPARE_MODE_TOGGLE_PIN); 
                break;
                case CCP_COMPARE_MODE_GENERATE_INTERRUPT: 
                CCP1_MODE_SELECT(CCP_COMPARE_MODE_GENERATE_INTERRUPT); 
                break;
                case CCP_COMPARE_MODE_SPECIAL_EVENT: 
                CCP1_MODE_SELECT(CCP_COMPARE_MODE_SPECIAL_EVENT); 
                break;
                default :status = E_NOT_OK;
            }
            TRISCbits.RC2 = 0;
            LATCbits.LC2 = 0;
            CCP_Capture_Compare_Time(_obj);
            CCP_Interrupt_CFG(_obj);
        }
        else if(CCP2_MODULE == _obj->select_module){
            CCP2_MODE_SELECT(CCP_MODULE_DISABLED);
            switch(_obj->ccp_mode){
                case CCP_COMPARE_MODE_SET_PIN: 
                CCP2_MODE_SELECT(CCP_COMPARE_MODE_SET_PIN); 
                break;
                case CCP_COMPARE_MODE_CLEAR_PIN: 
                CCP2_MODE_SELECT(CCP_COMPARE_MODE_CLEAR_PIN); 
                break;
                case CCP_COMPARE_MODE_TOGGLE_PIN: 
                CCP2_MODE_SELECT(CCP_COMPARE_MODE_TOGGLE_PIN); 
                break;
                case CCP_COMPARE_MODE_GENERATE_INTERRUPT: 
                CCP2_MODE_SELECT(CCP_COMPARE_MODE_GENERATE_INTERRUPT); 
                break;
                case CCP_COMPARE_MODE_SPECIAL_EVENT: 
                CCP2_MODE_SELECT(CCP_COMPARE_MODE_SPECIAL_EVENT); 
                break;
                default :status = E_NOT_OK;
            }
            TRISCbits.RC1 = 0;
            LATCbits.LC1 = 0;
            CCP_Capture_Compare_Time(_obj);
            CCP_Interrupt_CFG(_obj);
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_CompareMode_Deinitialize(const ccp_t *_obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _obj){
        status = E_NOT_OK;
    }
    else{
        if(CCP1_MODULE == _obj->select_module){
        CCP1_MODE_SELECT(CCP_MODULE_DISABLED);
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_DISABLE();
#endif
        }
        else if(CCP2_MODULE == _obj->select_module){
        CCP2_MODE_SELECT(CCP_MODULE_DISABLED);
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP2_INTERRUPT_DISABLE();
#endif
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_IsCompare_Complete(const ccp_t *_obj, uint8 *_compare){
    Std_ReturnType status = E_NOT_OK;
    if((NULL == _obj) || (NULL == _compare)){
        status = E_NOT_OK;
    }
    else{
        if(CCP1_MODULE == _obj->select_module){
            if(CCP_COMPARE_OCCUR == PIR1bits.CCP1IF){
                *_compare = CCP_COMPARE_OCCUR;
                CCP1_INTERRUPT_CLEAR_FLAG();
            }
            else{
                *_compare = CCP_COMPARE_NOT_OCCUR;
            }
        }
        else if(CCP2_MODULE == _obj->select_module){
            if(CCP_COMPARE_OCCUR == PIR2bits.CCP2IF){
                *_compare = CCP_COMPARE_OCCUR;
                CCP2_INTERRUPT_CLEAR_FLAG();
            }
            else{
                *_compare = CCP_COMPARE_NOT_OCCUR;
            }
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_CompareMode_Set_Value(const ccp_t *_obj, uint16 _compare){
    Std_ReturnType status = E_NOT_OK;
    CCP_reg_t l_value = {.ccp_16Bit = 0};
    if(NULL == _obj){
        status = E_NOT_OK;
    }
    else{
        l_value.ccp_16Bit = _compare;
        if(CCP1_MODULE == _obj->select_module){
            CCPR1L = l_value.ccp_low;
            CCPR1H = l_value.ccp_high;
        }
        else if(CCP2_MODULE == _obj->select_module){
            CCPR2L = l_value.ccp_low;
            CCPR2H = l_value.ccp_high;
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}

#endif

#if (CCP1_CFG_MODE_SELECTED==CCP_CFG_CAPTURE_MODE) || (CCP2_CFG_MODE_SELECTED==CCP_CFG_CAPTURE_MODE)
Std_ReturnType CCP_CaptureMode_Initialize(const ccp_t *_obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _obj){
        status = E_NOT_OK;
    }
    else{
        if(CCP1_MODULE == _obj->select_module){
            CCP1_MODE_SELECT(CCP_MODULE_DISABLED);
            switch(_obj->ccp_mode){
                case CCP_CAPTURE_MODE_1TH_FALLING_EDGE: 
                CCP1_MODE_SELECT(CCP_CAPTURE_MODE_1TH_FALLING_EDGE); 
                break;
                case CCP_CAPTURE_MODE_1TH_RISING_EDGE: 
                CCP1_MODE_SELECT(CCP_CAPTURE_MODE_1TH_RISING_EDGE); 
                break;
                case CCP_CAPTURE_MODE_4TH_FALLING_EDGE: 
                CCP1_MODE_SELECT(CCP_CAPTURE_MODE_4TH_FALLING_EDGE); 
                break;
                case CCP_CAPTURE_MODE_4TH_RISING_EDGE: 
                CCP1_MODE_SELECT(CCP_CAPTURE_MODE_4TH_RISING_EDGE); 
                break;
                default :status = E_NOT_OK;
            }
            TRISCbits.RC2 = 1;
            LATCbits.LC2 = 0;
            CCP_Capture_Compare_Time(_obj);
        }
        else if(CCP2_MODULE == _obj->select_module){
            CCP2_MODE_SELECT(CCP_MODULE_DISABLED);
            switch(_obj->ccp_mode){
                case CCP_CAPTURE_MODE_1TH_FALLING_EDGE: 
                CCP2_MODE_SELECT(CCP_CAPTURE_MODE_1TH_FALLING_EDGE); 
                break;
                case CCP_CAPTURE_MODE_1TH_RISING_EDGE: 
                CCP2_MODE_SELECT(CCP_CAPTURE_MODE_1TH_RISING_EDGE); 
                break;
                case CCP_CAPTURE_MODE_4TH_FALLING_EDGE: 
                CCP2_MODE_SELECT(CCP_CAPTURE_MODE_4TH_FALLING_EDGE); 
                break;
                case CCP_CAPTURE_MODE_4TH_RISING_EDGE: 
                CCP2_MODE_SELECT(CCP_CAPTURE_MODE_4TH_RISING_EDGE); 
                break;
                default :status = E_NOT_OK;
            }
            TRISCbits.RC1 = 1;
            LATCbits.LC1 = 0;
            CCP_Capture_Compare_Time(_obj);
        }
        else{/* Nothing */}
        CCP_Interrupt_CFG(_obj);
        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_CaptureMode_Deinitialize(const ccp_t *_obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _obj){
        status = E_NOT_OK;
    }
    else{
        if(CCP1_MODULE == _obj->select_module){
        CCP1_MODE_SELECT(CCP_MODULE_DISABLED);
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_DISABLE();
#endif
        }
        else if(CCP2_MODULE == _obj->select_module){
        CCP2_MODE_SELECT(CCP_MODULE_DISABLED);
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            CCP2_INTERRUPT_DISABLE();
#endif
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_IsCaptureOccur(const ccp_t *_obj, uint8 *_capture){
    Std_ReturnType status = E_NOT_OK;
    if((NULL == _capture) || (NULL == _obj)){
        status = E_NOT_OK;
    }
    else{
        if(CCP1_MODULE == _obj->select_module){
            if(CCP_CAPTURE_OCCUR == PIR1bits.CCP1IF){
                *_capture = CCP_CAPTURE_OCCUR;
                CCP1_INTERRUPT_CLEAR_FLAG();
            }
            else{
                *_capture = CCP_CAPTURE_NOT_OCCUR;
            }
        }
        else if(CCP2_MODULE == _obj->select_module){
            if(CCP_CAPTURE_OCCUR == PIR2bits.CCP2IF){
                *_capture = CCP_CAPTURE_OCCUR;
                CCP2_INTERRUPT_CLEAR_FLAG();
            }
            else{
                *_capture = CCP_CAPTURE_NOT_OCCUR;
            }
        }
        else{/* Nothing */}
        
        status = E_OK;
    }
    return status;
}

Std_ReturnType CCP_CaptureMode_Read_Value(const ccp_t *_obj, uint16 *_capture){
    Std_ReturnType status = E_NOT_OK;
    CCP_reg_t l_value = {.ccp_16Bit = 0};
    if((NULL == _capture) || (NULL == _obj)){
        status = E_NOT_OK;
    }
    else{
        if(CCP1_MODULE == _obj->select_module){
            l_value.ccp_low =  CCPR1L;
            l_value.ccp_high = CCPR1H;
            *_capture = l_value.ccp_16Bit;
        }
        else if(CCP2_MODULE == _obj->select_module){
            l_value.ccp_low =  CCPR2L;
            l_value.ccp_high = CCPR2H;
            *_capture = l_value.ccp_16Bit;
        }
        else{/* Nothing */}
        status = E_OK;
    }
    return status;
}

#endif


#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void CCP1_ISR(void){
    CCP1_INTERRUPT_CLEAR_FLAG();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
}
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void CCP2_ISR(void){
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
}
#endif

static void CCP_Interrupt_CFG(const ccp_t *_obj){
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    CCP1_INTERRUPT_ENABLE();
    CCP1_INTERRUPT_CLEAR_FLAG();
    CCP1_InterruptHandler = _obj->CCP1_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_ENABLE();
    if(LOW_PRIORITY_INTERRUPT == _obj->CCP1_priority){
        INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        CCP1_INTERRUPT_PRIORITY_LOW();
    }
    else if(HIGH_PRIORITY_INTERRUPT == _obj->CCP1_priority){
        INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        CCP1_INTERRUPT_PRIORITY_HIGH();
    }
#else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
    INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    CCP2_INTERRUPT_ENABLE();
    CCP2_INTERRUPT_CLEAR_FLAG();
    CCP2_InterruptHandler = _obj->CCP2_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_ENABLE();
    if(LOW_PRIORITY_INTERRUPT == _obj->CCP2_priority){
        INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        CCP2_INTERRUPT_PRIORITY_LOW();
    }
    else if(HIGH_PRIORITY_INTERRUPT == _obj->CCP2_priority){
        INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        CCP2_INTERRUPT_PRIORITY_HIGH();
    }
#else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
    INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
}

static void CCP_Capture_Compare_Time(const ccp_t *_obj){
    if(CCP1_CCP2_TIMER3 == _obj->capture_timer){
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 1;
            }
            else if(CCP1_TIMER1_CCP2_TIMER3 == _obj->capture_timer){
                T3CONbits.T3CCP1 = 1;
                T3CONbits.T3CCP2 = 0;
            }
            else if(CCP1_CCP2_TIMER1 == _obj->capture_timer){
                T3CONbits.T3CCP1 = 0;
                T3CONbits.T3CCP2 = 0;
            }else{/* Nothing */}
}