/* 
 * File:   hal_timer3.c
 * Author: Mohamed
 *
 * Created on September 26, 2023, 7:59 PM
 */
#include "hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* TMR3_InterruptHandler)(void) = NULL;
#endif

static void Timer3_Mode_Select(const timer3_t *_timer);
static void Timer3_16Bit_RW_Select(const timer3_t *_timer);

static uint16 Timer3_Preload = 0;


Std_ReturnType Timer3_Initialize(const timer3_t *_timer){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TIMER3_OFF();
        Timer3_Mode_Select(_timer);
        TIMER3_PRESCALER_SELECT(_timer->prescaler_value);
        Timer3_16Bit_RW_Select(_timer);
        TMR3H = (_timer->preload_value) >> 8 ;
        TMR3L = (uint8)(_timer->preload_value);
        Timer3_Preload = _timer->preload_value;
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
        TMR3_InterruptHandler = _timer->TIMER3_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        if(LOW_PRIORITY_INTERRUPT == _timer->priority){
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            TIMER3_INTERRUPT_PRIORITY_LOW();
        }
        else if(HIGH_PRIORITY_INTERRUPT == _timer->priority){
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            TIMER3_INTERRUPT_PRIORITY_HIGH();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
        TIMER3_ON();
        status = E_OK;
    }
    return status;
}

Std_ReturnType Timer3_Deinitialize(const timer3_t *_timer){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TIMER3_OFF();
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_DISABLE();
#endif
        status = E_OK;
    }
    return status;
}

Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TMR3H = ((_value) >> 8);
        TMR3L = (uint8)(_value);
        status = E_OK;
    }
    return status;
}

Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value){
    Std_ReturnType status = E_NOT_OK;
    uint8 l_tmr3l = 0 , l_tmr3h = 0;
    if((NULL == _timer) || (NULL == _value)){
        status = E_NOT_OK;
    }
    else{
        /* coz latch */
        l_tmr3l = TMR3L;
        l_tmr3h = TMR3H;
        *_value = (uint16)((l_tmr3h << 8) + l_tmr3l);
        status = E_OK;
    }
    return status;
}


static void Timer3_Mode_Select(const timer3_t *_timer){
    if(TIMER3_TIMER_MODE == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_SYNC_MODE == _timer->timer3_synchronization){
            TIMER3_SYNCHRONIZE_EXTERNAL_CLOCK();
        }
        else if(TIMER3_ASYNC_MODE == _timer->timer3_synchronization){
            TIMER3_ASYNCHRONIZE_EXTERNAL_CLOCK();
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

static void Timer3_16Bit_RW_Select(const timer3_t *_timer){
    if(TIMER3_RW_REG_8BIT_MODE == _timer->timer3_16Bit_RW_mode){
        TIMER3_RW_REG_8BIT_MODE_ENABLE();
    }
    else if(TIMER3_RW_REG_16BIT_MODE == _timer->timer3_16Bit_RW_mode){
        TIMER3_RW_REG_16BIT_MODE_ENABLE();
    }
    else{ /* Nothing */ }
}

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void TIMER3_ISR(void){
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TMR3H = ((Timer3_Preload) >> 8);
    TMR3L = (uint8)(Timer3_Preload);
    if(TMR3_InterruptHandler){TMR3_InterruptHandler();}
}
#endif