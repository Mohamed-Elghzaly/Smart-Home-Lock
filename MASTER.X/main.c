/* 
 * File:   application.c
 * Author: Mohamed AbdAllah
 *
 * Created on September 3, 2023, 12:00 AM
 */
#include"main.h"

int main() {
    application_initialize();
    
    Welcome();
    SetPassword();
    while(1){
        SelectAdminOrGuest();
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    //Interrupt_RBx_Intialize();
    ecu_layer_intialize();
}

/** First Screen */
/*********** Welcome to Smart Home ************/
void Welcome(void){
    lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
    lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Welcome to Smart");
    lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Home");
     delay_ms(500);
}

/* Second Screen if it used for the first time */
/* Set Password for the first use */
void SetPassword(void){
    uint8 value = 0;
    /* check EEPROM if empty or not */
    EEPROM_Data_Read(0x18 , &value);
    if(value == 0xFF){
        lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
        lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Login for first");
        lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"time");
         delay_ms(500);
        AdminPassword();
        GuestPassword();
    }else{/* Nothing */}
}

/* Set Admin Password  */
void AdminPassword(void){
    uint8 value = 0;
    lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
    lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Set Admin Pass");
    lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Admin Pass:");
    /* Write Data in EEPROM */
    for(uint8 i=0; i<4; i++){
            value = 0xFF;
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 12+i,'_');
            while(value == 0xFF){
                keypad_get_value(&keypad_1, &value);
            }
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 12+i, value);
            delay_ms(350);
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 12+i, '*');
            EEPROM_Data_Write((0x18 + i), value);
        }
         lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
        lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Admin Pass");
        lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Created :)");
        delay_ms(500);
}

/* Set Guest Password  */
void GuestPassword(void){
    uint8 value = 0;
    lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
    lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Set Guest Pass");
    lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Guest Pass:");
    /* Write Data in EEPROM */
    for(uint8 i=0; i<4; i++){
            value = 0xFF;
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 12+i,'_');
            /* always get number until write Number & write Data in EEPROM */
            while(value == 0xFF){
                keypad_get_value(&keypad_1, &value);
            }
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 12+i, value);
            delay_ms(350);
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 12+i, '*');
            EEPROM_Data_Write((0x1C + i), value);
        }
        lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
        lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Guest Pass");
        lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Created :)");
        delay_ms(500);
}
/* Second Screen if you set pass already 
 * third Screen if it used for the first time 
 */
void SelectAdminOrGuest(void){
    uint8 value = 0xFF;
        lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
        lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Login as");
        lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"1.Admin  2.Guest");
        delay_ms(250);
        /* always get number until write choose 1 or 2 */
    while((value != '1') && (value != '2')){
        keypad_get_value(&keypad_1, &value);
    }
    switch(value){
        case('1'): AdminLogin();break;
        case('2'): GuestLogin();break;
        default : ;
    };
}

/* 
 * if Select admin forth Screen Admin Login 
 */
void AdminLogin(void){
    uint8 value = 0xFF;
    uint8 ShutDownValue = 0;
    uint8 tryAgain = 3;
    uint8 password[4];
    uint8 LoginPass[4];
    /* Get Admin Password From EEPROM and save in array password*/
    for(uint8 i=0; i<4; i++){
        EEPROM_Data_Read(0x18+i, password+i);
    }
    lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
    lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Admin Login");
    lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Pass:");
    while(tryAgain){
        /* Get Data from keypad and save in array LoginPass*/
        for(uint8 i=0; i<4; i++){
            lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Admin Login");
            lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Pass:");
            lcd_4bit_send_string_pos(&LCD_1 ,2 ,16 ,"H");
            value = 0xFF;
            delay_ms(250);
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 6+i,'_');
            while(value == 0xFF){
                keypad_get_value(&keypad_1, &value);
            }
            /* Return home Screen */
            if(value == '#'){
                return;
            }else{}
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 6+i, value);
            delay_ms(250);
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 6+i, '*');
            LoginPass[i] = value;
        }
        /* Compare two array*/
        value = StringCompare(LoginPass, password, 4);
        /* check if true or not */
        if(value){
            lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
            lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Login Success");
            delay_ms(1000);
            break;
        }
        else{
            lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
            lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Wrong Pass");
            lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Try Again");
            lcd_4bit_send_char_data_pos(&LCD_1 ,2 ,11 ,tryAgain+0x2F);
            delay_ms(500);
            lcd_4bit_send_string_pos(&LCD_1 ,2 ,6 ,"      ");
            tryAgain--;
            if(tryAgain == 0){
                tryAgain = 3;
                ShutDownValue++;
                /* shutdown system when writing password wrong */
                if(ShutDownValue == 3){
                    SystemShutDown();
                }else{}
                lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
                lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Waiting 5 Sec");
                delay_ms(5000);
                lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
            }else{}
        }
    }
    AdminControl();
}
/* 
 * if Select Guest forth Screen Guest Login 
 */
void GuestLogin(void){
    uint8 value = 0xFF;
    uint8 ShutDownValue = 0;
    uint8 tryAgain = 3;
    uint8 password[4];
    uint8 LoginPass[4];
    /* Get Admin Password From EEPROM */
    for(uint8 i=0; i<4; i++){
        EEPROM_Data_Read(0x1C+i, password+i);
    }
    lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
    lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Guest Login");
    lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Pass:");
    while(tryAgain){
        for(uint8 i=0; i<4; i++){
            lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Guest Login");
            lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Pass:");
            lcd_4bit_send_string_pos(&LCD_1 ,2 ,16 ,"H");
            value = 0xFF;
            delay_ms(250);
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 6+i,'_');
            while(value == 0xFF){
                keypad_get_value(&keypad_1, &value);
            }
            /* Return home Screen */
            if(value == '#'){
                return;
            }else{}
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 6+i, value);
            delay_ms(250);
            lcd_4bit_send_char_data_pos(&LCD_1, 2, 6+i, '*');
            LoginPass[i] = value;
        }
        value = StringCompare(LoginPass, password, 4);
        if(value){
            lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
            lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Login Success");
            delay_ms(1000);
            break;
        }
        else{
            lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
            lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Wrong Pass");
            lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Try Again");
            lcd_4bit_send_char_data_pos(&LCD_1 ,2 ,11 ,tryAgain+0x2F);
            delay_ms(500);
            lcd_4bit_send_string_pos(&LCD_1 ,2 ,6 ,"      ");
            tryAgain--;
            if(tryAgain == 0){
                tryAgain = 3;
                ShutDownValue++;
                /* shutdown system when writing password wrong */
                if(ShutDownValue == 3){
                    SystemShutDown();
                }else{}
                lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
                lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Waiting 5 Sec");
                delay_ms(5000);
                lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
            }else{}
        }
    }
    GuestControl();
}

/*
 * compare two string
 */
uint8 StringCompare(uint8 str1[], uint8 str2[], uint8 Length){
    for(uint8 i=0; i<Length; i++){
        if(str1[i] != str2[i]){
            return 0;
        }
        else{
            
        }
    }
    return 1;
}
/*
 * Admin Control thing
 */
void AdminControl(void){
    while(1){
        lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
        lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Admin Start");
        lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Control Here");
        led_turn_on(&AdminLed);
        while(1){
            
        }
    }
}
/*
 * Guest Control thing
 */
void GuestControl(void){
    while(1){
        lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
        lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"Guest Start");
        lcd_4bit_send_string_pos(&LCD_1 ,2 ,1 ,"Control Here");
        led_turn_on(&GuestLed);
        while(1){
            
        }
    }
}

void SystemShutDown(void){
    while(1){
        lcd_4bit_send_command(&LCD_1, _LCD_CLEAR);
        lcd_4bit_send_string_pos(&LCD_1 ,1 ,1 ,"System ShutDown!");
        led_turn_on(&Alarm);
        while(1){
            
        }
    }
}