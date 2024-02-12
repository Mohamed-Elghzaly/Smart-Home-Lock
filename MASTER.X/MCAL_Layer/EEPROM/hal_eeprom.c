/* 
 * File:   hal_eeprom.c
 * Author: Mohamed
 *
 * Created on September 20, 2023, 10:21 AM
 */

#include "hal_eeprom.h"


Std_ReturnType EEPROM_Data_Write(uint16 Add, uint8 Data){
    Std_ReturnType status = E_OK;
    
    uint8 Interrupt_Global_Status = INTCONbits.GIE;
    EEADRH = ((Add >> 8) & 0x03);
    EEADR = (Add & 0xFF);
    EEDATA = Data;
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    INTERRUPT_GLOBAL_INTERRUPT_DISABLE();
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = INITIATES_DATA_EEPROM_ERASE;
    while(EECON1bits.WR);
    
    EECON1bits.WREN = INHIBITS_WRITE_CYCLES_FLASH_EEPROM;
    
    INTCONbits.GIE = Interrupt_Global_Status;
    
    return status;
}

Std_ReturnType EEPROM_Data_Read(uint16 Add, uint8 *Data){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == Data){
        status = E_NOT_OK;
    }
    else{
        EEADRH = ((Add >> 8) & 0x03);
        EEADR = (Add & 0xFF);
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        EECON1bits.RD = INITIATES_EEPROM_READ;
        NOP();
        NOP();
        *Data = EEDATA;
        
        status = E_OK;
    }
    return status;
}
