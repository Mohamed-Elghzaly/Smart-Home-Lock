/* 
 * File:   keypad.h
 * Author: Mohamed
 *
 * Created on September 11, 2023, 10:50 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* Section : Macro Declaration */
#define KEYPAD_ROWS    4
#define KEYPAD_COLUMNS 4

/* Section : Data Type Declaration */
typedef struct{
    pin_config_t keypad_rows_pin[KEYPAD_ROWS];
    pin_config_t keypad_columns_pin[KEYPAD_COLUMNS];
}keypad_t;

/* Section : Function Declaration */
Std_ReturnType keypad_intialize(const keypad_t *_keypad);
Std_ReturnType keypad_get_value(const keypad_t *_keypad, uint8 *value);


#endif	/* KEYPAD_H */

