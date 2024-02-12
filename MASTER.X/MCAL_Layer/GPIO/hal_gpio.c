/* 
 * File:   hal_gpio.c
 * Author: Mohamed Elghzaly
 *
 * Created on September 3, 2023, 12:17 AM
 */

#include "hal_gpio.h"

volatile uint8 *tris_register[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *lat_register[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *port_register[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/**
 * 
 * @param _pin_config
 * @return status of the function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
#if GPIO_PORT_PIN_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config){
    Std_ReturnType status = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        status = E_NOT_OK;
    }
    else{
        switch(_pin_config->direction){
            case GPIO_OUTPUT :
                CLEAR_BIT(*tris_register[_pin_config->port], _pin_config->pin);
            break;
            case GPIO_INPUT:
                SET_BIT(*tris_register[_pin_config->port], _pin_config->pin);
            break;
            default : status = E_NOT_OK;
        }
    }
    return status;
}
#endif

/**
 * 
 * @param _pin_config
 * @param direction_status
 * @return status of the function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
#if GPIO_PORT_PIN_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status){
    Std_ReturnType status = E_OK;
    if((NULL == _pin_config) || (NULL == direction_status) || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        status = E_NOT_OK;
    }
    else{
        *direction_status = READ_BIT(*tris_register[_pin_config->port], _pin_config->pin);
    }
    return status;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return 
 */
#if GPIO_PORT_PIN_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic){
    Std_ReturnType status = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        status = E_NOT_OK;
    }
    else{
        switch(logic){
            case GPIO_LOW:
                CLEAR_BIT(*lat_register[_pin_config->port], _pin_config->pin);
            break;
            case GPIO_HIGH:
                SET_BIT(*lat_register[_pin_config->port], _pin_config->pin);
            break;
            default : status = E_NOT_OK;
        }
    }
    return status;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return status of the function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
#if GPIO_PORT_PIN_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic){
    Std_ReturnType status = E_OK;
    if((NULL == _pin_config) || (NULL == logic) || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        status = E_NOT_OK;
    }
    else{
        *logic = READ_BIT(*port_register[_pin_config->port], _pin_config->pin);
    }
    return status;
}
#endif

/**
 * 
 * @param _pin_config
 * @return status of the function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
#if GPIO_PORT_PIN_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
    Std_ReturnType status = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        status = E_NOT_OK;
    }
    else{
        TOGGLE_BIT(*lat_register[_pin_config->port], _pin_config->pin);
    }
    return status;
}
#endif

#if GPIO_PORT_PIN_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config){
    Std_ReturnType status = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        status = E_NOT_OK;
    }
    else{
       gpio_pin_direction_intialize(_pin_config);
       gpio_pin_write_logic(_pin_config, _pin_config->logic);
    }
    return status;
}
#endif
 
/**
 * 
 * @param port
 * @param direction
 * @return status of the function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
#if GPIO_PORT_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction){
    Std_ReturnType status = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        status = E_NOT_OK;
    }
    else{
        *tris_register[port] = direction;
    }
    return status;
}
#endif

/**
 * 
 * @param port
 * @param direction_status
 * @return status of the function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
#if GPIO_PORT_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status){
    Std_ReturnType status = E_OK;
    if(NULL == direction_status || (port > PORT_MAX_NUMBER-1)){
        status = E_NOT_OK;
    }
    else{
        *direction_status = *tris_register[port];
    }
    return status;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return status of the function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
#if GPIO_PORT_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic){
    Std_ReturnType status = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        status = E_NOT_OK;
    }
    else{
        *lat_register[port] = logic;
    }
    return status;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return status of the function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
#if GPIO_PORT_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic){
    Std_ReturnType status = E_OK;
    if(NULL == logic || (port > PORT_MAX_NUMBER-1)){
        status = E_NOT_OK;
    }
    else{
        *logic = *lat_register[port];
    }
    return status;
}
#endif

/**
 * 
 * @param port
 * @return status of the function
 *          (E_OK)     : function done successfully
 *          (E_NOT_OK) : function has issue
 */
#if GPIO_PORT_CONFEGRAION == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
    Std_ReturnType status = E_OK;
    if(port > PORT_MAX_NUMBER-1){
        status = E_NOT_OK;
    }
    else{
        *lat_register[port] ^= 0xFF;
    }
    
    return status;
}
#endif