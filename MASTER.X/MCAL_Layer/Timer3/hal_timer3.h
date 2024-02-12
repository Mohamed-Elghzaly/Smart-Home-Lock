/* 
 * File:   hal_timer3.h
 * Author: Mohamed
 *
 * Created on September 26, 2023, 7:59 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H
/*------------------- Includes -------------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"

/*------------------- Macro Declarations -------------------*/
/* Timer3 Clock Source Select bit */
#define TIMER3_TIMER_MODE        0
#define TIMER3_COUNTER_MODE      1
/*  Timer3 External Clock Input Synchronization Select bit */
#define TIMER3_ASYNC_MODE        1
#define TIMER3_SYNC_MODE         0
/* : Timer3 Input Clock Prescale Select bits */
#define TIMER3_PRESCALER_DIV_BY_1        0
#define TIMER3_PRESCALER_DIV_BY_2        1
#define TIMER3_PRESCALER_DIV_BY_4        2
#define TIMER3_PRESCALER_DIV_BY_8        3
/* 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8BIT_MODE          0
#define TIMER3_RW_REG_16BIT_MODE         1


/*------------------- Macro Functions Declarations -------------------*/
/* Timer3 On OR Off bit */
#define TIMER3_ON()                                     (T3CONbits.TMR3ON = 1)
#define TIMER3_OFF()                                    (T3CONbits.TMR3ON = 0)
/* Timer3 Clock Source Select bit */
#define TIMER3_COUNTER_MODE_ENABLE()                    (T3CONbits.TMR3CS = 1)
#define TIMER3_TIMER_MODE_ENABLE()                      (T3CONbits.TMR3CS = 0)
/*  Timer3 External Clock Input Synchronization Select bit */
#define TIMER3_SYNCHRONIZE_EXTERNAL_CLOCK()             (T3CONbits.T3SYNC = 0)
#define TIMER3_ASYNCHRONIZE_EXTERNAL_CLOCK()            (T3CONbits.T3SYNC = 1)
/* : Timer3 Input Clock Prescale Select bits */
#define TIMER3_PRESCALER_SELECT(_CFG)                   (T3CONbits.T3CKPS = _CFG)
/* 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8BIT_MODE_ENABLE()                   (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()                  (T3CONbits.RD16 = 1)

/*------------------- Data Type Declarations -------------------*/
typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* TIMER3_InterruptHandler)(void);
    interrupt_priority priority;
#endif
    uint16 preload_value;
    uint8 prescaler_value : 2 ;
    uint8 timer3_mode : 1 ;
    uint8 timer3_synchronization : 1;
    uint8 timer3_16Bit_RW_mode : 1;
}timer3_t;
/*------------------- Software Interfaces Declarations -------------------*/
Std_ReturnType Timer3_Initialize(const timer3_t *_timer);
Std_ReturnType Timer3_Deinitialize(const timer3_t *_timer);
Std_ReturnType Timer3_Write_Value(const timer3_t *_timer, uint16 _value);
Std_ReturnType Timer3_Read_Value(const timer3_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER3_H */

