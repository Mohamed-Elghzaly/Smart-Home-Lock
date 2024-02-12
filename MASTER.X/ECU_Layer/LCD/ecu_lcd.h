/* 
 * File:   ecu_lcd.h
 * Author: Mohamed
 *
 * Created on September 13, 2023, 2:48 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/*------------------- Includes -------------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/*------------------- Macro Declarations -------------------*/
#define _LCD_CLEAR                      0x01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE_SET             0x06
#define _LCD_DISPLAY_ON_CURSOR_OFF      0x0C
#define _LCD_DISPLAY_OFF_CURSOR_OFF     0x08    
#define _LCD_8BIT_DISPLAY_2_LINE        0x38
#define _LCD_4BIT_DISPLAY_2_LINE        0x28
#define _LCD_DDRAM_START                0x80
#define _LCD_CGRAM_START                0x40

#define ROW1    1
#define ROW2    2
/*------------------- Macro Functions Declarations -------------------*/

/*------------------- Data Type Declarations -------------------*/
typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}lcd_8bit_t;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4]; // last 4 pin
}lcd_4bit_t;

/*------------------- Software Interfaces Declarations -------------------*/
Std_ReturnType lcd_8bit_intialize(const lcd_8bit_t *_lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *_lcd, uint8 command);
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *_lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *_lcd,uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *_lcd, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *_lcd,uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *_lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos);

Std_ReturnType lcd_4bit_intialize(const lcd_4bit_t *_lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *_lcd, uint8 command);
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *_lcd, uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *_lcd,uint8 row, uint8 column, uint8 data);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *_lcd, uint8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *_lcd,uint8 row, uint8 column, uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *_lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos);

Std_ReturnType convert_uint8_to_string(uint8 byte, uint8 *str);
Std_ReturnType convert_uint16_to_string(uint16 byte, uint8 *str);
Std_ReturnType convert_uint32_to_string(uint32 byte, uint8 *str);

#endif	/* ECU_LCD_H */

