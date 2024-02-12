/* 
 * File:   mcal_interrupt_manager.h
 * Author: Mohamed
 *
 * Created on September 17, 2023, 3:01 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/*------------------- Includes -------------------*/
#include "mcal_interrupt_conifg.h"

/*------------------- Macro Declarations -------------------*/

/*------------------- Macro Functions Declarations -------------------*/

/*------------------- Data Type Declarations -------------------*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void ADC_ISR(void);
void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BUS_Colision(void);
void RB4_ISR(uint8 RB4_src);
void RB5_ISR(uint8 RB4_src);
void RB6_ISR(uint8 RB4_src);
void RB7_ISR(uint8 RB4_src);


#endif	/* MCAL_INTERRUPT_MANAGER_H */

