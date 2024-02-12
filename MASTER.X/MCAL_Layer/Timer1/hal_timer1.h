/* 
 * File:   hal_timer1.h
 * Author: Mohamed
 *
 * Created on September 26, 2023, 11:51 AM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H
/*------------------- Includes -------------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include <pic18f4620.h>

/*------------------- Macro Declarations -------------------*/
/* Timer1 Clock Source Select bit */
#define TIMER1_TIMER_MODE        0
#define TIMER1_COUNTER_MODE      1
/*  Timer1 External Clock Input Synchronization Select bit */
#define TIMER1_ASYNC_MODE        1
#define TIMER1_SYNC_MODE         0
/* Timer1 Oscillator Enable bit */
#define TIMER1_OSC_ENABLE        1
#define TIMER1_OSC_DISABLE       0
/* : Timer1 Input Clock Prescale Select bits */
#define TIMER1_PRESCALER_DIV_BY_1        0
#define TIMER1_PRESCALER_DIV_BY_2        1
#define TIMER1_PRESCALER_DIV_BY_4        2
#define TIMER1_PRESCALER_DIV_BY_8        3
/* 16-Bit Read/Write Mode */
#define TIMER1_RW_REG_8BIT_MODE          0
#define TIMER1_RW_REG_16BIT_MODE         1

/*------------------- Macro Functions Declarations -------------------*/
/* Timer1 On OR Off bit */
#define TIMER1_ON()                                     (T1CONbits.TMR1ON = 1)
#define TIMER1_OFF()                                    (T1CONbits.TMR1ON = 0)
/* Timer1 Clock Source Select bit */
#define TIMER1_COUNTER_MODE_ENABLE()                    (T1CONbits.TMR1CS = 1)
#define TIMER1_TIMER_MODE_ENABLE()                      (T1CONbits.TMR1CS = 0)
/*  Timer1 External Clock Input Synchronization Select bit */
#define TIMER1_SYNCHRONIZE_EXTERNAL_CLOCK()             (T1CONbits.T1SYNC = 0)
#define TIMER1_ASYNCHRONIZE_EXTERNAL_CLOCK()            (T1CONbits.T1SYNC = 1)
/* Timer1 Oscillator Enable bit */
#define TIMER1_OSCILLATOR_ENABLE()                      (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSCILLATOR_DISABLE()                     (T1CONbits.T1OSCEN = 0)
/* : Timer1 Input Clock Prescale Select bits */
#define TIMER1_PRESCALER_SELECT(_CFG)                   (T1CONbits.T1CKPS = _CFG)
/* RETURN System Clock Status */
#define TIMER1_SYS_CLK_STATUS()                         (T1CONbits.T1RUN)
/* 16-Bit Read/Write Mode */
#define TIMER1RW_REG_8BIT_MODE_ENABLE                   (T1CONbits.RD16 = 0)
#define TIMER1RW_REG_16BIT_MODE_ENABLE                  (T1CONbits.RD16 = 1)

/*------------------- Data Type Declarations -------------------*/
typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* TIMER1_InterruptHandler)(void);
    interrupt_priority priority;
#endif
    uint16 preload_value;
    uint8 prescaler_value : 2 ;
    uint8 timer1_mode : 1 ;
    uint8 timer1_synchronization : 1;
    uint8 timer1_oscillator_enable : 1;
    uint8 timer1_RW_mode : 1;
}timer1_t;
/*------------------- Software Interfaces Declarations -------------------*/
Std_ReturnType Timer1_Initialize(const timer1_t *_timer);
Std_ReturnType Timer1_Deinitialize(const timer1_t *_timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value);
Std_ReturnType Timer1_Read_Value(const timer1_t *_timer, uint16 *_value);

#endif	/* HAL_TIMER1_H */

