/* 
 * File:   hal_timer1.c
 * Author: Mohamed
 *
 * Created on September 26, 2023, 11:51 AM
 */

#include "hal_timer1.h"

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* TMR1_InterruptHandler)(void) = NULL;
#endif

static void Timer1_Mode_Select(const timer1_t *_timer);

static uint16 Timer1_Preload = 0;

Std_ReturnType Timer1_Initialize(const timer1_t *_timer){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TIMER1_OFF();
        TIMER1_PRESCALER_SELECT(_timer->prescaler_value);
        Timer1_Mode_Select(_timer);
        TMR1H = (_timer->preload_value) >> 8 ;
        TMR1L = (uint8)(_timer->preload_value);
        Timer1_Preload = _timer->preload_value;
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        TMR1_InterruptHandler = _timer->TIMER1_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        if(LOW_PRIORITY_INTERRUPT == _timer->priority){
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            TIMER1_INTERRUPT_PRIORITY_LOW();
        }
        else if(HIGH_PRIORITY_INTERRUPT == _timer->priority){
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            TIMER1_INTERRUPT_PRIORITY_HIGH();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
        TIMER1_ON();
        status = E_OK;
    }
    return status;
}

Std_ReturnType Timer1_Deinitialize(const timer1_t *_timer){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TIMER1_OFF();
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_DISABLE();
#endif
        status = E_OK;
    }
    return status;
}

Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TMR1H = ((_value) >> 8);
        TMR1L = (uint8)(_value);
        status = E_OK;
    }
    return status;
}

Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value){
    Std_ReturnType status = E_NOT_OK;
    uint8 l_tmr1l = 0 , l_tmr1h = 0;
    if((NULL == _timer) || (NULL == _value)){
        status = E_NOT_OK;
    }
    else{
        /* coz latch */
        l_tmr1l = TMR1L;
        l_tmr1h = TMR1H;
        *_value = (uint16)((l_tmr1h << 8) + l_tmr1l);
        status = E_OK;
    }
    return status;
}

static void Timer1_Mode_Select(const timer1_t *_timer){
    if(TIMER1_TIMER_MODE == _timer->timer1_mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode){
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_SYNC_MODE == _timer->timer1_synchronization){
            TIMER1_SYNCHRONIZE_EXTERNAL_CLOCK();
        }
        else if(TIMER1_ASYNC_MODE == _timer->timer1_synchronization){
            TIMER1_ASYNCHRONIZE_EXTERNAL_CLOCK();
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}


#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void TIMER1_ISR(void){
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1H = ((Timer1_Preload) >> 8);
    TMR1L = (uint8)(Timer1_Preload);
    if(TMR1_InterruptHandler){TMR1_InterruptHandler();}
}
#endif