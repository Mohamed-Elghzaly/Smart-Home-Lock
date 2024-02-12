/* 
 * File:   ecu_layer_init.c
 * Author: Mohamed
 *
 * Created on September 12, 2023, 10:50 AM
 */

#include "ecu_layer_init.h"

lcd_4bit_t LCD_1 = {
    .lcd_en.pin = GPIO_PIN5,
    .lcd_en.port = PORTA_INDEX,
    .lcd_en.direction = GPIO_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_rs.pin = GPIO_PIN4,
    .lcd_rs.port = PORTA_INDEX,
    .lcd_rs.direction = GPIO_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_data[0].pin = GPIO_PIN0,
    .lcd_data[0].port = PORTA_INDEX,
    .lcd_data[0].direction = GPIO_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].pin = GPIO_PIN1,
    .lcd_data[1].port = PORTA_INDEX,
    .lcd_data[1].direction = GPIO_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].pin = GPIO_PIN2,
    .lcd_data[2].port = PORTA_INDEX,
    .lcd_data[2].direction = GPIO_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].pin = GPIO_PIN3,
    .lcd_data[3].port = PORTA_INDEX,
    .lcd_data[3].direction = GPIO_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
};
keypad_t keypad_1 = {
    .keypad_rows_pin[0].pin = GPIO_PIN0,
    .keypad_rows_pin[0].port = PORTB_INDEX,
    .keypad_rows_pin[0].direction = GPIO_OUTPUT,
    .keypad_rows_pin[0].logic = GPIO_LOW,
    .keypad_rows_pin[1].pin = GPIO_PIN1,
    .keypad_rows_pin[1].port = PORTB_INDEX,
    .keypad_rows_pin[1].direction = GPIO_OUTPUT,
    .keypad_rows_pin[1].logic = GPIO_LOW,
    .keypad_rows_pin[2].pin = GPIO_PIN2,
    .keypad_rows_pin[2].port = PORTB_INDEX,
    .keypad_rows_pin[2].direction = GPIO_OUTPUT,
    .keypad_rows_pin[2].logic = GPIO_LOW,
    .keypad_rows_pin[3].pin = GPIO_PIN3,
    .keypad_rows_pin[3].port = PORTB_INDEX,
    .keypad_rows_pin[3].direction = GPIO_OUTPUT,
    .keypad_rows_pin[3].logic = GPIO_LOW,
    .keypad_columns_pin[0].pin = GPIO_PIN4,
    .keypad_columns_pin[0].port = PORTB_INDEX,
    .keypad_columns_pin[0].direction = GPIO_INPUT,
    .keypad_columns_pin[0].logic = GPIO_LOW,
    .keypad_columns_pin[1].pin = GPIO_PIN5,
    .keypad_columns_pin[1].port = PORTB_INDEX,
    .keypad_columns_pin[1].direction = GPIO_INPUT,
    .keypad_columns_pin[1].logic = GPIO_LOW,
    .keypad_columns_pin[2].pin = GPIO_PIN6,
    .keypad_columns_pin[2].port = PORTB_INDEX,
    .keypad_columns_pin[2].direction = GPIO_INPUT,
    .keypad_columns_pin[2].logic = GPIO_LOW,
    .keypad_columns_pin[3].pin = GPIO_PIN7,
    .keypad_columns_pin[3].port = PORTB_INDEX,
    .keypad_columns_pin[3].direction = GPIO_INPUT,
    .keypad_columns_pin[3].logic = GPIO_LOW,
};

led_t AdminLed = {
    .led_status = LED_OFF,
    .pin = GPIO_PIN0,
    .port_name = PORTD_INDEX,
};
led_t GuestLed = {
    .led_status = LED_OFF,
    .pin = GPIO_PIN1,
    .port_name = PORTD_INDEX,
};
led_t Alarm = {
    .led_status = LED_OFF,
    .pin = GPIO_PIN2,
    .port_name = PORTD_INDEX,
};

void ecu_layer_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    lcd_4bit_intialize(&LCD_1);
    keypad_intialize(&keypad_1);
    led_initialize(&AdminLed);
    led_initialize(&GuestLed);
    led_initialize(&Alarm);
}

void delay_ms(uint32 val){
 unsigned int i,j;
 for(i=0;i<val;i++)
     for(j=0;j<135;j++);  /* 135 This count Provide delay of 1 ms for 8MHz Frequency */
 }