/* 
 * File:   mcal_external_interrupt.h
 * Author: Mohamed
 *
 * Created on September 17, 2023, 3:01 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*------------------- Includes -------------------*/
#include "mcal_interrupt_conifg.h"

/*------------------- Macro Declarations -------------------*/

/*------------------- Macro Functions Declarations -------------------*/
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE

#define EXT_INT0_INTERRUPT_ENABLE()                     (INTCONbits.INT0E = 1)
#define EXT_INT0_INTERRUPT_DISABLE()                    (INTCONbits.INT0E = 0)
#define EXT_INT0_INTERRUPT_FLAG_CLEAR()                 (INTCONbits.INT0F = 0)
#define EXT_INT0_INTERRUPT_RISING_EDGE()                (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_INTERRUPT_FALLING_EDGE()               (INTCON2bits.INTEDG0 = 0)

#define EXT_INT1_INTERRUPT_ENABLE()                     (INTCON3bits.INT1E = 1)
#define EXT_INT1_INTERRUPT_DISABLE()                    (INTCON3bits.INT1E = 0)
#define EXT_INT1_INTERRUPT_FLAG_CLEAR()                 (INTCON3bits.INT1F = 0)
#define EXT_INT1_INTERRUPT_RISING_EDGE()                (INTCON2bits.INTEDG1 = 1)
#define EXT_INT1_INTERRUPT_FALLING_EDGE()               (INTCON2bits.INTEDG1 = 0)

#define EXT_INT2_INTERRUPT_ENABLE()                     (INTCON3bits.INT2E = 1)
#define EXT_INT2_INTERRUPT_DISABLE()                    (INTCON3bits.INT2E = 0)
#define EXT_INT2_INTERRUPT_FLAG_CLEAR()                 (INTCON3bits.INT2F = 0)
#define EXT_INT2_INTERRUPT_RISING_EDGE()                (INTCON2bits.INTEDG2 = 1)
#define EXT_INT2_INTERRUPT_FALLING_EDGE()               (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

#define EXT_INT1_INTERRUPT_HIGH_PRIORITY()              (INTCON3bits.INT1P = 1)
#define EXT_INT1_INTERRUPT_LOW_PRIORITY()               (INTCON3bits.INT1P = 0)
#define EXT_INT2_INTERRUPT_HIGH_PRIORITY()              (INTCON3bits.INT2P = 1)
#define EXT_INT2_INTERRUPT_LOW_PRIORITY()               (INTCON3bits.INT2P = 0)

#endif

#endif

#if EXT_INTERRUPT_ON_CHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
#define EXT_RBx_INTERRUPT_ENABLE()                     (INTCONbits.RBIE = 1)
#define EXT_RBx_INTERRUPT_DISABLE()                    (INTCONbits.RBIE = 0)
#define EXT_RBx_INTERRUPT_FLAG_CLEAR()                 (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
#define EXT_RBx_INTERRUPT_HIGH_PRIORITY()               (INTCON2bits.RBIP = 1)
#define EXT_RBx_INTERRUPT_LOW_PRIORITY()                (INTCON2bits.RBIP = 0)

#endif

#endif

/*------------------- Data Type Declarations -------------------*/
typedef enum{
    FALLING_EDGE_INTERRUPT = 0,
    RISING_EDGE_INTERRUPT,
}interrupt_INTx_edge;

typedef enum{
    EXETERNAL_INT0 = 0,
    EXETERNAL_INT1,
    EXETERNAL_INT2
}interrupt_INTx_NUMBER;

typedef struct{
    pin_config_t pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_NUMBER number;
    interrupt_priority priority;
    void (* call_back)(void);
}interrupt_INTx_t;

typedef struct{
    pin_config_t pin;
    interrupt_priority priority;
    void (* HIGH_call_back)(void);
    void (* LOW_call_back)(void);
}interrupt_RBx_t;

/*------------------- Software Interfaces Declarations -------------------*/
Std_ReturnType Interrupt_INTx_Intialize(const interrupt_INTx_t *obj);
Std_ReturnType Interrupt_INTx_DeIntialize(const interrupt_INTx_t *obj);
Std_ReturnType Interrupt_RBx_Intialize(const interrupt_RBx_t *obj);
Std_ReturnType Interrupt_RBx_DeIntialize(const interrupt_RBx_t *obj);


#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

