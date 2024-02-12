/* 
 * File:   ecu_layer_init.h
 * Author: Mohamed
 *
 * Created on September 12, 2023, 10:50 AM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section : Includes */
#include "Keypad/keypad.h"
#include "LED/ecu_led.h"
#include "Keypad/keypad.h"
#include "LCD/ecu_lcd.h"

/* Section : Function Declaration */
void ecu_layer_intialize(void);
void delay_ms(uint32 val);

#endif	/* ECU_LAYER_INIT_H */

