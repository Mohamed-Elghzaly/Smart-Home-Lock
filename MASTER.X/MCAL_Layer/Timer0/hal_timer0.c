/* 
 * File:   hal_timer0.h
 * Author: Mohamed
 *
 * Created on September 23, 2023, 5:09 PM
 */

#include "hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* TMR0_InterruptHandler)(void) = NULL;
#endif

static uint16 Timer0_Preload;

static void Timer0_Prescaler(const timer0_t *_timer);
static void Timer0_Mode_Select(const timer0_t *_timer);
static void Timer0_Register_Size(const timer0_t *_timer);

Std_ReturnType Timer0_Initialize(const timer0_t *_timer){
    Std_ReturnType status = E_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
        Timer0_Prescaler(_timer);
        Timer0_Mode_Select(_timer);
        Timer0_Register_Size(_timer);
        TMR0H = (uint8)((_timer->preload_value) >> 8);
        TMR0L = (uint8)(_timer->preload_value);
        Timer0_Preload = _timer->preload_value;
        #if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
        TMR0_InterruptHandler = _timer->TIMER0_InterruptHandler;
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_ENABLE();
        if(LOW_PRIORITY_INTERRUPT == _timer->priority){
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            TIMER0_INTERRUPT_PRIORITY_LOW();
        }
        else if(HIGH_PRIORITY_INTERRUPT == _timer->priority){
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            TIMER0_INTERRUPT_PRIORITY_HIGH();
        }
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif
        #endif
        TIMER0_MODULE_ENABLE();
    }
    return status;
}

Std_ReturnType Timer0_Deinitialize(const timer0_t *_timer){
    Std_ReturnType status = E_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
        #if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_DISABLE();
        #endif
    }
    return status;
}

Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _value){
    Std_ReturnType status = E_OK;
    if(NULL == _timer){
        status = E_NOT_OK;
    }
    else{
        TMR0H = (uint8)((_value) >> 8);
        TMR0L = (uint8)(_value);
    }
    return status;
}

Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_value){
    Std_ReturnType status = E_OK;
    if((NULL == _timer) || (NULL == _value)){
        status = E_NOT_OK;
    }
    else{
        *_value = (uint16)((TMR0H << 8) + TMR0L);
    }
    return status;
}

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void TIMER0_ISR(void){
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TMR0H = (uint8)((Timer0_Preload) >> 8);
    TMR0L = (uint8)(Timer0_Preload);
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}
#endif

static void Timer0_Prescaler(const timer0_t *_timer){
    if(TIMER0_PRESCALER_ENABLE == _timer->prescaler_mode){
        TIMER0_PRESCALER_ASSIGNMENT_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    else if(TIMER0_PRESCALER_DISABLE == _timer->prescaler_mode){
        TIMER0_PRESCALER_ASSIGNMENT_DISABLE();
    }
    else{ /* Nothing */ }
}

static void Timer0_Mode_Select(const timer0_t *_timer){
    if(TIMER0_TIMER_MODE_CFG == _timer->timer0_mode){
        TIMER0_TIMER_MODE();
    }
    else if(TIMER0_COUNTER_MODE_CFG == _timer->prescaler_mode){
        TIMER0_COUNTER_MODE();
        if(TIMER0_RISING_MODE == _timer->counter_edge){
            TIMER0_RISING_EDGE();
        }
        else if(TIMER0_FALLING_MODE == _timer->counter_edge){
            TIMER0_FALLING_EDGE();
        }
        else{ /* Nothing */ }
    }
    else{ /* Nothing */ }
}

static void Timer0_Register_Size(const timer0_t *_timer){
    if(TIMER0_8BIT_REG == _timer->register_size){
        TIMER0_CONFIGURED_8_BIT();
    }
    else if(TIMER0_16BIT_REG == _timer->register_size){
        TIMER0_CONFIGURED_16_BIT();
    }
    else{ /* Nothing */ }
}