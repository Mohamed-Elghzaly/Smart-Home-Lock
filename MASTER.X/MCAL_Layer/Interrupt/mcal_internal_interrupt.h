/* 
 * File:   mcal_internal_interrupt.h
 * Author: Mohamed
 *
 * Created on September 17, 2023, 3:00 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/*------------------- Includes -------------------*/
#include "mcal_interrupt_conifg.h"

/*------------------- Macro Declarations -------------------*/
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for ADC module */
#define ADC_INTERRUPT_ENABLE()              (PIE1bits.ADIE = 1)
/* Disable Interrupt for ADC module */
#define ADC_INTERRUPT_DISABLE()             (PIE1bits.ADIE = 0)
/* Clear Interrupt Flag for ADC module */
#define ADC_INTERRUPT_CLEAR_FLAG()          (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority ADC Interrupt HIGH */
#define ADC_INTERRUPT_PRIORITY_HIGH()      (IPR1bits.ADIP == 1)
/*  priority ADC Interrupt LOW */
#define ADC_INTERRUPT_PRIORITY_LOW()       (IPR1bits.ADIP == 0)
#endif
#endif

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for TIMER0 module */
#define TIMER0_INTERRUPT_ENABLE()              (INTCONbits.TMR0IE = 1)
/* Disable Interrupt for TIMER0 module */
#define TIMER0_INTERRUPT_DISABLE()             (INTCONbits.TMR0IE = 0)
/* Clear Interrupt Flag for TIMER0 module */
#define TIMER0_INTERRUPT_CLEAR_FLAG()          (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority TIMER0 Interrupt HIGH */
#define TIMER0_INTERRUPT_PRIORITY_HIGH()      (INTCON2bits.TMR0IP = 1)
/*  priority TIMER0 Interrupt LOW */
#define TIMER0_INTERRUPT_PRIORITY_LOW()       (INTCON2bits.TMR0IP = 0)
#endif
#endif

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for TIMER1 module */
#define TIMER1_INTERRUPT_ENABLE()              (PIE1bits.TMR1IE = 1)
/* Disable Interrupt for TIMER1 module */
#define TIMER1_INTERRUPT_DISABLE()             (PIE1bits.TMR1IE = 0)
/* Clear Interrupt Flag for TIMER1 module */
#define TIMER1_INTERRUPT_CLEAR_FLAG()          (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority TIMER1 Interrupt HIGH */
#define TIMER1_INTERRUPT_PRIORITY_HIGH()      (IPR1bits.TMR1IP = 1)
/*  priority TIMER1 Interrupt LOW */
#define TIMER1_INTERRUPT_PRIORITY_LOW()       (IPR1bits.TMR1IP = 0)
#endif
#endif

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for TIMER2 module */
#define TIMER2_INTERRUPT_ENABLE()              (PIE1bits.TMR2IE = 1)
/* Disable Interrupt for TIMER2 module */
#define TIMER2_INTERRUPT_DISABLE()             (PIE1bits.TMR2IE = 0)
/* Clear Interrupt Flag for TIMER2 module */
#define TIMER2_INTERRUPT_CLEAR_FLAG()          (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority TIMER2 Interrupt HIGH */
#define TIMER2_INTERRUPT_PRIORITY_HIGH()      (IPR1bits.TMR2IP = 1)
/*  priority TIMER2 Interrupt LOW */
#define TIMER2_INTERRUPT_PRIORITY_LOW()       (IPR1bits.TMR2IP = 0)
#endif
#endif

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for TIMER3 module */
#define TIMER3_INTERRUPT_ENABLE()              (PIE2bits.TMR3IE = 1)
/* Disable Interrupt for TIMER3 module */
#define TIMER3_INTERRUPT_DISABLE()             (PIE2bits.TMR3IE = 0)
/* Clear Interrupt Flag for TIMER3 module */
#define TIMER3_INTERRUPT_CLEAR_FLAG()          (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority TIMER3 Interrupt HIGH */
#define TIMER3_INTERRUPT_PRIORITY_HIGH()      (IPR2bits.TMR3IP = 1)
/*  priority TIMER3 Interrupt LOW */
#define TIMER3_INTERRUPT_PRIORITY_LOW()       (IPR2bits.TMR3IP = 0)
#endif
#endif

#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for CCP1 module */
#define CCP1_INTERRUPT_ENABLE()              (PIE1bits.CCP1IE = 1)
/* Disable Interrupt for CCP1 module */
#define CCP1_INTERRUPT_DISABLE()             (PIE1bits.CCP1IE = 0)
/* Clear Interrupt Flag for CCP1 module */
#define CCP1_INTERRUPT_CLEAR_FLAG()          (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority CCP1 Interrupt HIGH */
#define CCP1_INTERRUPT_PRIORITY_HIGH()      (IPR1bits.CCP1IP = 1)
/*  priority CCP1 Interrupt LOW */
#define CCP1_INTERRUPT_PRIORITY_LOW()       (IPR1bits.CCP1IP = 0)
#endif
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for CCP2 module */
#define CCP2_INTERRUPT_ENABLE()              (PIE2bits.CCP2IE = 1)
/* Disable Interrupt for CCP2 module */
#define CCP2_INTERRUPT_DISABLE()             (PIE2bits.CCP2IE = 0)
/* Clear Interrupt Flag for CCP2 module */
#define CCP2_INTERRUPT_CLEAR_FLAG()          (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority CCP2 Interrupt HIGH */
#define CCP2_INTERRUPT_PRIORITY_HIGH()      (IPR2bits.CCP2IP = 1)
/*  priority CCP2 Interrupt LOW */
#define CCP2_INTERRUPT_PRIORITY_LOW()       (IPR2bits.CCP2IP = 0)
#endif
#endif

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for EUSART module */
#define EUSART_TX_INTERRUPT_ENABLE()              (PIE1bits.TXIE = 1)
/* Disable Interrupt for EUSART module */
#define EUSART_TX_INTERRUPT_DISABLE()             (PIE1bits.TXIE = 0)
/* Clear Interrupt Flag for EUSART module */
#define EUSART_TX_INTERRUPT_CLEAR_FLAG()          (PIR1bits.TXIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority EUSART Interrupt HIGH */
#define EUSART_TX_INTERRUPT_PRIORITY_HIGH()      (IPR1bits.TXIP = 1)
/*  priority EUSART Interrupt LOW */
#define EUSART_TX_INTERRUPT_PRIORITY_LOW()       (IPR1bits.TXIP = 0)
#endif
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for EUSART module */
#define EUSART_RX_INTERRUPT_ENABLE()              (PIE1bits.RCIE = 1)
/* Disable Interrupt for EUSART module */
#define EUSART_RX_INTERRUPT_DISABLE()             (PIE1bits.RCIE = 0)
/* Clear Interrupt Flag for EUSART module */
#define EUSART_RX_INTERRUPT_CLEAR_FLAG()          (PIR1bits.RCIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority EUSART Interrupt HIGH */
#define EUSART_RX_INTERRUPT_PRIORITY_HIGH()      (IPR1bits.RCIP = 1)
/*  priority EUSART Interrupt LOW */
#define EUSART_RX_INTERRUPT_PRIORITY_LOW()       (IPR1bits.RCIP = 0)
#endif
#endif

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* Enable Interrupt for MSSP I2C module */
#define MSSP_I2C_INTERRUPT_ENABLE()              (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COLLISION_ENABLE()          (PIE2bits.BCLIE = 1)
/* Disable Interrupt for MSSP I2C module */
#define MSSP_I2C_INTERRUPT_DISABLE()             (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COLLISION_DISABLE()         (PIE2bits.BCLIE = 0)
/* Clear Interrupt Flag for MSSP I2C module */
#define MSSP_I2C_INTERRUPT_CLEAR_FLAG()          (PIR1bits.SSPIF = 0)
#define MSSP_I2C_BUS_COLLISION_CLEAR_FLAG()      (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*  priority MSSP I2C Interrupt HIGH */
#define MSSP_I2C_INTERRUPT_PRIORITY_HIGH()       (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COLLISION_PRIORITY_HIGH()   (IPR2bits.BCLIP = 1)
/*  priority MSSP I2C Interrupt LOW */
#define MSSP_I2C_INTERRUPT_PRIORITY_LOW()        (IPR1bits.SSPIP = 0)
#define MSSP_I2C_BUS_COLLISION_PRIORITY_LOW()    (IPR2bits.BCLIP = 0)
#endif
#endif
/*------------------- Macro Functions Declarations -------------------*/

/*------------------- Data Type Declarations -------------------*/


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

