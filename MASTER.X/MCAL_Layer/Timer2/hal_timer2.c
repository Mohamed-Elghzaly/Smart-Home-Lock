
/* 
 * File:   hal_timer2.c
 * Author: Mohamed
 *
 * Created on September 26, 2023, 5:44 PM
 */

#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* TMR2_InterruptHandler)(void) = NULL;
#endif

static uint8 Timer2_Preload = 0;

Std_ReturnType Timer2_Initialize(const timer2_t *_timer){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TIMER2_OFF();
        TIMER2_PRESCALER_SELECT(_timer->prescaler_value);
        TIMER2_POSTSCALER_SELECT(_timer->postscaler_value);
        TMR2 = _timer->preload_value;
        Timer2_Preload = _timer->preload_value;
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_CLEAR_FLAG();
        TMR2_InterruptHandler = _timer->TIMER2_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        if(LOW_PRIORITY_INTERRUPT == _timer->priority){
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            TIMER2_INTERRUPT_PRIORITY_LOW();
        }
        else if(HIGH_PRIORITY_INTERRUPT == _timer->priority){
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            TIMER2_INTERRUPT_PRIORITY_HIGH();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
        TIMER2_ON();
        status = E_OK;
    }
    return status;
}

Std_ReturnType Timer2_Deinitialize(const timer2_t *_timer){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TIMER2_OFF();
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DISABLE();
#endif
        status = E_OK;
    }
    return status;
}

Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TMR2 = _value;
        status = E_OK;
    }
    return status;
}

Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value){
    Std_ReturnType status = E_NOT_OK;
    if((NULL == _timer) || (NULL == _value)){
        status = E_NOT_OK;
    }
    else{
        *_value = TMR2;
        status = E_OK;
    }
    return status;
}

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void TIMER2_ISR(void){
    TIMER2_INTERRUPT_CLEAR_FLAG();
    TMR2 = Timer2_Preload;
    if(TMR2_InterruptHandler){TMR2_InterruptHandler();}
}
#endif