/* 
 * File:   application.h
 * Author: Mohamed Elghzaly
 *
 * Created on September 3, 2023, 12:40 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"

/* Section : Macro Functions Declaration */

/* Section : Data Type Declaration */
extern lcd_4bit_t LCD_1;
extern keypad_t keypad_1;
extern led_t AdminLed;
extern led_t GuestLed;
extern led_t Alarm;

/* Section : Function Declaration */
void application_initialize(void);
void Welcome(void);
void SetPassword(void);
void AdminPassword(void);
void GuestPassword(void);
void SelectAdminOrGuest(void);
void AdminLogin(void);
void GuestLogin(void);
uint8 StringCompare(uint8 str1[], uint8 str2[], uint8 Length);
void AdminControl(void);
void GuestControl(void);
void SystemShutDown(void);
void ReturnHome(void);


#endif	/* APPLICATION_H */

