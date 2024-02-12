/* 
 * File:   hal_timer2.h
 * Author: Mohamed
 *
 * Created on September 26, 2023, 5:44 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H
/*------------------- Includes -------------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"

/*------------------- Macro Declarations -------------------*/
/* Timer2 Clock Source Select bit */
#define TIMER2_TIMER_MODE        1
#define TIMER2_COUNTER_MODE      0
/* : Timer2 Input Clock Prescaler Select bits */
#define TIMER2_PRESCALER_DIV_BY_1        0
#define TIMER2_PRESCALER_DIV_BY_4        1
#define TIMER2_PRESCALER_DIV_BY_16       2
/* : Timer2 Input Clock Postscaler Select bits */
#define TIMER2_POSTSCALER_DIV_BY_1        0
#define TIMER2_POSTSCALER_DIV_BY_2        1
#define TIMER2_POSTSCALER_DIV_BY_3        2
#define TIMER2_POSTSCALER_DIV_BY_4        3
#define TIMER2_POSTSCALER_DIV_BY_5        4
#define TIMER2_POSTSCALER_DIV_BY_6        5
#define TIMER2_POSTSCALER_DIV_BY_7        6
#define TIMER2_POSTSCALER_DIV_BY_8        7
#define TIMER2_POSTSCALER_DIV_BY_9        8
#define TIMER2_POSTSCALER_DIV_BY_10       9
#define TIMER2_POSTSCALER_DIV_BY_11       10
#define TIMER2_POSTSCALER_DIV_BY_12       11
#define TIMER2_POSTSCALER_DIV_BY_13       12
#define TIMER2_POSTSCALER_DIV_BY_14       13
#define TIMER2_POSTSCALER_DIV_BY_15       14
#define TIMER2_POSTSCALER_DIV_BY_16       15
/*------------------- Macro Functions Declarations -------------------*/
/* Timer2 On OR Off bit */
#define TIMER2_ON()                                     (T2CONbits.TMR2ON = 1)
#define TIMER2_OFF()                                    (T2CONbits.TMR2ON = 0)
/* : Timer2 Input Clock Prescaler Select bits */
#define TIMER2_PRESCALER_SELECT(_CFG)                   (T2CONbits.T2CKPS = _CFG)
/* : Timer2 Input Clock Postscaler Select bits */
#define TIMER2_POSTSCALER_SELECT(_CFG)                  (T2CONbits.TOUTPS = _CFG)


/*------------------- Data Type Declarations -------------------*/
typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* TIMER2_InterruptHandler)(void);
    interrupt_priority priority;
#endif
    uint16 preload_value;
    uint8 postscaler_value: 4;
    uint8 prescaler_value : 2;
}timer2_t;
/*------------------- Software Interfaces Declarations -------------------*/
Std_ReturnType Timer2_Initialize(const timer2_t *_timer);
Std_ReturnType Timer2_Deinitialize(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value);
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer, uint8 *_value);


#endif	/* HAL_TIMER2_H */

