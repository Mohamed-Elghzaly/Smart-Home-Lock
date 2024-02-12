/* 
 * File:   mcal_interrupt_conifg.h
 * Author: Mohamed
 *
 * Created on September 17, 2023, 2:59 PM
 */

#ifndef MCAL_INTERRUPT_CONIFG_H
#define	MCAL_INTERRUPT_CONIFG_H

/*------------------- Includes -------------------*/
#include <pic18f4620.h>
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"

/*------------------- Macro Declarations -------------------*/
#define INTERRUPT_ENABLE                     1
#define INTERRUPT_DISABLE                    0
#define INTERRUPT_FLAG_OCCUR                 1
#define INTERRUPT_FLAG_NOT_OCCUR             0
#define INTERRUPT_PRIORITY_ENABLE            1
#define INTERRUPT_PRIORITY_DISABLE           0


/*------------------- Macro Functions Declarations -------------------*/

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Priority Level On Interrupt */
#define INTERRUPT_PRIORITY_ENABLE()      (RCONbits.IPEN = 1)
/* Disable Priority Level On Interrupt */
#define INTERRUPT_PRIORITY_DISABLE()     (RCONbits.IPEN = 0)

/* Enable High Priority Global Interrupt */
#define INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE()      (INTCONbits.GIEH = 1)
/* Disable High Priority Global Interrupt */
#define INTERRUPT_GLOBAL_INTERRUPT_HIGH_DISABLE()     (INTCONbits.GIEH = 0)

/* Enable Low Priority Global Interrupt */
#define INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE()      (INTCONbits.GIEL = 1)
/* Disable Low Priority Global Interrupt */
#define INTERRUPT_GLOBAL_INTERRUPT_LOW_DISABLE()     (INTCONbits.GIEL = 0)

#else
/* Enable Global Interrupt */
#define INTERRUPT_GLOBAL_INTERRUPT_ENABLE()      (INTCONbits.GIE = 1)
/* Disable Global Interrupt */
#define INTERRUPT_GLOBAL_INTERRUPT_DISABLE()     (INTCONbits.GIE = 0)
/* Enable Peripheral Interrupt*/
#define INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE()      (INTCONbits.PEIE = 1)
/* Disable Peripheral Interrupt*/
#define INTERRUPT_PERIPHERAL_INTERRUPT_DISABLE()     (INTCONbits.PEIE = 0)

#endif

/*------------------- Data Type Declarations -------------------*/
typedef enum{
    LOW_PRIORITY_INTERRUPT = 0,
    HIGH_PRIORITY_INTERRUPT,
}interrupt_priority;
/*------------------- Software Interfaces Declarations -------------------*/

#endif	/* MCAL_INTERRUPT_CONIFG_H */

