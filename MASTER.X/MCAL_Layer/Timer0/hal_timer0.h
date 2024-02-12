/* 
 * File:   hal_timer0.h
 * Author: Mohamed
 *
 * Created on September 23, 2023, 5:09 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/*------------------- Includes -------------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include <pic18f4620.h>

/*------------------- Macro Declarations -------------------*/
#define TIMER0_PRESCALER_DIV_BY_2        0
#define TIMER0_PRESCALER_DIV_BY_4        1
#define TIMER0_PRESCALER_DIV_BY_8        2
#define TIMER0_PRESCALER_DIV_BY_16       3
#define TIMER0_PRESCALER_DIV_BY_32       4
#define TIMER0_PRESCALER_DIV_BY_64       5
#define TIMER0_PRESCALER_DIV_BY_128      6
#define TIMER0_PRESCALER_DIV_BY_265      7

#define TIMER0_PRESCALER_ENABLE      0
#define TIMER0_PRESCALER_DISABLE     1  

#define TIMER0_TIMER_MODE_CFG       0
#define TIMER0_COUNTER_MODE_CFG     1 

#define TIMER0_RISING_MODE       0
#define TIMER0_FALLING_MODE      1 

#define TIMER0_8BIT_REG       0
#define TIMER0_16BIT_REG      1 

/*------------------- Macro Functions Declarations -------------------*/
#define TIMER0_MODULE_ENABLE()                     (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()                    (T0CONbits.TMR0ON = 0)

#define TIMER0_CONFIGURED_8_BIT()                   (T0CONbits.T08BIT = 1)
#define TIMER0_CONFIGURED_16_BIT()                  (T0CONbits.T08BIT = 0)

#define TIMER0_FALLING_EDGE()                       (T0CONbits.T0SE = 1)
#define TIMER0_RISING_EDGE()                        (T0CONbits.T0SE = 0)

#define TIMER0_TIMER_MODE()                         (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE()                       (T0CONbits.T0CS = 1)

#define TIMER0_PRESCALER_ASSIGNMENT_ENABLE()        (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_ASSIGNMENT_DISABLE()       (T0CONbits.PSA = 1)

/*------------------- Data Type Declarations -------------------*/
typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* TIMER0_InterruptHandler)(void);
    interrupt_priority priority;
#endif
    uint16 preload_value;
    uint8 prescaler_value : 3 ;
    uint8 prescaler_mode  : 1 ;
    uint8 counter_edge     : 1 ;
    uint8 timer0_mode      : 1 ;
    uint8 register_size   : 1 ;
}timer0_t;

/*------------------- Software Interfaces Declarations -------------------*/
Std_ReturnType Timer0_Initialize(const timer0_t *_timer);
Std_ReturnType Timer0_Deinitialize(const timer0_t *_timer);
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint16 _value);
Std_ReturnType Timer0_Read_Value(const timer0_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER0_H */

