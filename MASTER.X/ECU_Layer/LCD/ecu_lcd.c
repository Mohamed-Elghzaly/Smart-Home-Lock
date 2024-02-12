/* 
 * File:   ecu_lcd.h
 * Author: Mohamed
 *
 * Created on September 13, 2023, 2:48 PM
 */

/*------------------- Includes -------------------*/
#include "ecu_lcd.h"

/*------------------- Software Interfaces Declarations -------------------*/
static Std_ReturnType lcd_send_4bit(const lcd_4bit_t *_lcd, uint8 data_command);
static Std_ReturnType lcd_send_enable(const lcd_4bit_t *_lcd);
static Std_ReturnType lcd_8bit_set_pos(const lcd_4bit_t *_lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_4bit_set_pos(const lcd_4bit_t *_lcd, uint8 row, uint8 column);

Std_ReturnType lcd_8bit_intialize(const lcd_8bit_t *_lcd){
    Std_ReturnType status = E_NOT_OK;
    uint8 data_counter = 0;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = gpio_pin_intialize(&(_lcd->lcd_rs));
        status = gpio_pin_intialize(&(_lcd->lcd_en));
        for(data_counter = 0; data_counter<8; data_counter++){
            status = gpio_pin_intialize(&(_lcd->lcd_data[data_counter]));
        }
        __delay_ms(20);
        status = lcd_8bit_send_command(_lcd, _LCD_8BIT_DISPLAY_2_LINE);
        __delay_ms(5);
        status = lcd_8bit_send_command(_lcd, _LCD_8BIT_DISPLAY_2_LINE);
        __delay_us(150);
        status = lcd_8bit_send_command(_lcd, _LCD_8BIT_DISPLAY_2_LINE);
        status = lcd_8bit_send_command(_lcd, _LCD_CLEAR);
        status = lcd_8bit_send_command(_lcd, _LCD_RETURN_HOME);
        status = lcd_8bit_send_command(_lcd, _LCD_ENTRY_MODE_SET);
        status = lcd_8bit_send_command(_lcd, _LCD_DISPLAY_ON_CURSOR_OFF);
        status = lcd_8bit_send_command(_lcd, _LCD_8BIT_DISPLAY_2_LINE);
        status = lcd_8bit_send_command(_lcd, _LCD_DDRAM_START);
    }
    return status;
}

Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *_lcd, uint8 command){
    Std_ReturnType status = E_NOT_OK;
    uint8 data_counter = 0;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = gpio_pin_write_logic(&(_lcd->lcd_rs), GPIO_LOW);
        for(data_counter = 0; data_counter<8; data_counter++){
            status = gpio_pin_write_logic(&(_lcd->lcd_data[data_counter]), (command >> data_counter) & 0x01);
        }
        status = lcd_send_enable(_lcd);
    }
    return status;
}

Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *_lcd, uint8 data){
    Std_ReturnType status = E_NOT_OK;
    uint8 data_counter = 0;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = gpio_pin_write_logic(&(_lcd->lcd_rs), GPIO_HIGH);
        for(data_counter = 0; data_counter<8; data_counter++){
            status = gpio_pin_write_logic(&(_lcd->lcd_data[data_counter]), (data >> data_counter) & 0x01);
        }
        status = lcd_send_enable(_lcd);
    }
    return status;
}

Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t *_lcd,uint8 row, uint8 column, uint8 data){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = lcd_8bit_set_pos(_lcd, row, column);
        status = lcd_8bit_send_char_data(_lcd, data);
    }
    return status;
}

Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *_lcd, uint8 *str){
    Std_ReturnType status = E_NOT_OK;
    uint8 *temp_str = str;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        while(*temp_str){
            lcd_8bit_send_char_data(_lcd, *temp_str);
            temp_str++;
        }
    }
    return status;
}

Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *_lcd,uint8 row, uint8 column, uint8 *str){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = lcd_8bit_set_pos(_lcd, row, column);
        status = lcd_8bit_send_string(_lcd, str);
    }
    return status;
}

Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *_lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos){
    Std_ReturnType status = E_NOT_OK;
    uint8 l_counter = 0;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = lcd_8bit_send_command(_lcd, _LCD_CGRAM_START + (mem_pos*8));
        for(l_counter = 0; l_counter<8; l_counter++){
            status = lcd_8bit_send_char_data(_lcd, chr[l_counter]);
        }
        status = lcd_8bit_send_char_data_pos(_lcd, row, column, mem_pos);
    }
    return status;
}


Std_ReturnType lcd_4bit_intialize(const lcd_4bit_t *_lcd){
    Std_ReturnType status = E_NOT_OK;
    uint8 data_counter = 0;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = gpio_pin_intialize(&(_lcd->lcd_rs));
        status = gpio_pin_intialize(&(_lcd->lcd_en));
        for(data_counter = 0; data_counter<4; data_counter++){
            status = gpio_pin_intialize(&(_lcd->lcd_data[data_counter]));
        }
        __delay_ms(20);
        status = lcd_4bit_send_command(_lcd, _LCD_8BIT_DISPLAY_2_LINE);
        __delay_ms(5);
        status = lcd_4bit_send_command(_lcd, _LCD_8BIT_DISPLAY_2_LINE);
        __delay_us(150);
        status = lcd_4bit_send_command(_lcd, _LCD_8BIT_DISPLAY_2_LINE);
        status = lcd_4bit_send_command(_lcd, _LCD_CLEAR);
        status = lcd_4bit_send_command(_lcd, _LCD_RETURN_HOME);
        status = lcd_4bit_send_command(_lcd, _LCD_ENTRY_MODE_SET);
        status = lcd_4bit_send_command(_lcd, _LCD_DISPLAY_ON_CURSOR_OFF);
        status = lcd_4bit_send_command(_lcd, _LCD_4BIT_DISPLAY_2_LINE);
        status = lcd_4bit_send_command(_lcd, _LCD_DDRAM_START);
    }
    return status;
}

Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *_lcd, uint8 command){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = gpio_pin_write_logic(&(_lcd->lcd_rs), GPIO_LOW);
        status = lcd_send_4bit(_lcd, command >> 4);
        lcd_send_enable(_lcd);
        status = lcd_send_4bit(_lcd, command);
        lcd_send_enable(_lcd);
    }
    return status;
}

Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *_lcd, uint8 data){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = gpio_pin_write_logic(&(_lcd->lcd_rs), GPIO_HIGH);
        status = lcd_send_4bit(_lcd, data >> 4);
        lcd_send_enable(_lcd);
        status = lcd_send_4bit(_lcd, data);
        lcd_send_enable(_lcd);
    }
    return status;
}

Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t *_lcd,uint8 row, uint8 column, uint8 data){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = lcd_4bit_set_pos(_lcd, row, column);
        status = lcd_4bit_send_char_data(_lcd, data);
    }
    return status;
}

Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *_lcd, uint8 *str){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        while(*str){
            lcd_4bit_send_char_data(_lcd, *str++);
        }
    }
    return status;
}

Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *_lcd,uint8 row, uint8 column, uint8 *str){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = lcd_4bit_set_pos(_lcd, row, column);
        while(*str){
            lcd_4bit_send_char_data(_lcd, *str++);
        }
    }
    return status;
}

Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *_lcd, uint8 row, uint8 column, uint8 chr[], uint8 mem_pos){
    Std_ReturnType status = E_NOT_OK;
    uint8 l_counter = 0;
    if(NULL == _lcd){
        status = E_NOT_OK;
    }
    else{
        status = lcd_4bit_send_command(_lcd, _LCD_CGRAM_START + (mem_pos*8));
        for(l_counter = 0; l_counter<8; l_counter++){
            status = lcd_4bit_send_char_data(_lcd, chr[l_counter]);
        }
        status = lcd_4bit_send_char_data_pos(_lcd, row, column, mem_pos);
    }
    return status;
}


Std_ReturnType convert_uint8_to_string(uint8 byte, uint8 *str){
    Std_ReturnType status = E_OK;
    if(NULL == str){
        status = E_NOT_OK;
    }
    else{
        memset(str, '\0', 4);
        sprintf(str, "%i", byte);
    }
    return status;
}

Std_ReturnType convert_uint16_to_string(uint16 byte, uint8 *str){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == str){
        status = E_NOT_OK;
    }
    else{
        memset(str, '\0', 6);
        sprintf(str, "%i", byte);
    }
    return status;
}

Std_ReturnType convert_uint32_to_string(uint32 byte, uint8 *str){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == str){
        status = E_NOT_OK;
    }
    else{
        memset(str, '\0', 11);
        sprintf(str, "%i", byte);
    }
    return status;
}


static Std_ReturnType lcd_send_4bit(const lcd_4bit_t *_lcd, uint8 data_command){
    Std_ReturnType status = E_NOT_OK;
    status = gpio_pin_write_logic(&(_lcd->lcd_data[0]), (data_command >> 0)& 0x1);
    status = gpio_pin_write_logic(&(_lcd->lcd_data[1]), (data_command >> 1)& 0x1);
    status = gpio_pin_write_logic(&(_lcd->lcd_data[2]), (data_command >> 2)& 0x1);
    status = gpio_pin_write_logic(&(_lcd->lcd_data[3]), (data_command >> 3)& 0x1);
    return status;
}

static Std_ReturnType lcd_send_enable(const lcd_4bit_t *_lcd){
    Std_ReturnType status = E_NOT_OK;
    status = gpio_pin_write_logic(&(_lcd->lcd_en), GPIO_HIGH);
    __delay_us(40);
    status = gpio_pin_write_logic(&(_lcd->lcd_en), GPIO_LOW);
    return status;
}

static Std_ReturnType lcd_8bit_set_pos(const lcd_4bit_t *_lcd, uint8 row, uint8 column){
    Std_ReturnType status = E_NOT_OK;
    column--;
    switch(row){
        case ROW1 : status = lcd_8bit_send_command(_lcd, (0x80 + column)); break;
        case ROW2 : status = lcd_8bit_send_command(_lcd, (0xC0 + column)); break;
        default : ;
    }
    return status;
}

static Std_ReturnType lcd_4bit_set_pos(const lcd_4bit_t *_lcd, uint8 row, uint8 column){
    Std_ReturnType status = E_NOT_OK;
    column--;
    switch(row){
        case ROW1 : status = lcd_4bit_send_command(_lcd, (0x80 + column)); break; /* 0x00 -> Decimal : 0  */
        case ROW2 : status = lcd_4bit_send_command(_lcd, (0xC0 + column)); break; /* 0x40 -> Decimal : 64 */
        default : ;
    }
    return status;
}