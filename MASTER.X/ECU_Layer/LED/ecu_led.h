/* 
 * File:   ecu_led.h
 * Author: Mohamed Elghzaly
 *
 * Created on September 3, 2023, 12:32 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

 
/* Section : Macro Declaration */

/* Section : Macro Functions Declaration */

/* Section : Data Type Declaration */
typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port_name : 4;
    uint8 pin : 3;
    uint8 led_status : 1;
}led_t;
/* Section : Function Declaration */
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_toggle(const led_t *led);


#endif	/* ECU_LED_H */

