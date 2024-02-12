/* 
 * File:   keypad.c
 * Author: Mohamed
 *
 * Created on September 11, 2023, 10:50 PM
 */
#include <pic18.h>

#include "keypad.h"
 
static const uint8 btn_keypad[KEYPAD_ROWS][KEYPAD_COLUMNS] = {{'7', '8', '9', '/'},
                                                              {'4', '5', '6', '*'},
                                                              {'1', '2', '3', '-'},
                                                              {'#', '0', '=', '+'}
                                                             };

/**
 * 
 * @param _keypad
 * @return 
 */
Std_ReturnType keypad_intialize(const keypad_t *_keypad){
    Std_ReturnType status = E_NOT_OK;
    uint8 l_rows_counter = 0, l_columns_counter = 0;
    if(NULL == _keypad){
        status = E_NOT_OK;
    }
    else{
        for(l_rows_counter = 0; l_rows_counter<KEYPAD_ROWS; l_rows_counter++){
            status = gpio_pin_intialize(&(_keypad->keypad_rows_pin[l_rows_counter]));
        }
        for(l_columns_counter = 0; l_columns_counter<KEYPAD_COLUMNS; l_columns_counter++){
            status = gpio_pin_direction_intialize(&(_keypad->keypad_columns_pin[l_columns_counter]));
        }
    }
    return status;
}

/**
 * 
 * @param _keypad
 * @param value
 * @return 
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad, uint8 *value){
    Std_ReturnType status = E_NOT_OK;
    uint8 c_logic = 0;
    uint8 l_rows_counter = 0, l_columns_counter = 0, l_counter = 0;
    if((NULL == _keypad) || (NULL == value)){
        status = E_NOT_OK;
    }
    else{
        for(l_rows_counter = 0; l_rows_counter<KEYPAD_ROWS; l_rows_counter++){
            for(l_counter = 0; l_counter<KEYPAD_ROWS; l_counter++){
                status = gpio_pin_write_logic(&(_keypad->keypad_rows_pin[l_counter]), GPIO_LOW);
            }
            status = gpio_pin_write_logic(&(_keypad->keypad_rows_pin[l_rows_counter]), GPIO_HIGH);
                for(l_columns_counter = 0; l_columns_counter<KEYPAD_COLUMNS; l_columns_counter++){
                status = gpio_pin_read_logic(&(_keypad->keypad_columns_pin[l_columns_counter]), &c_logic);
                if(c_logic == GPIO_HIGH){
                    *value = btn_keypad[l_rows_counter][l_columns_counter];
                }
            }
        }
    }
    return status;
}