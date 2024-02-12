/* 
 * File:   ecu_led.c
 * Author: Mohamed Elghzaly
 *
 * Created on September 3, 2023, 12:32 AM
 */

#include "ecu_led.h"


Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == led){
        status = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj={.direction = GPIO_OUTPUT, 
                              .logic = led->led_status, 
                              .pin = led->pin, 
                              .port = led->port_name};
        status = gpio_pin_intialize(&pin_obj);
    }
    return status;
}

Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == led){
        status = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj={.direction = GPIO_OUTPUT, 
                              .logic = led->led_status, 
                              .pin = led->pin, 
                              .port = led->port_name};
        status = gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return status;
}

Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == led){
        status = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj={.direction = GPIO_OUTPUT, 
                              .logic = led->led_status, 
                              .pin = led->pin, 
                              .port = led->port_name};
        status = gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return status;
}

Std_ReturnType led_turn_toggle(const led_t *led){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == led){
        status = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj={.direction = GPIO_OUTPUT, 
                              .logic = led->led_status, 
                              .pin = led->pin, 
                              .port = led->port_name};
        status = gpio_pin_toggle_logic(&pin_obj);
    }
    return status;
}
