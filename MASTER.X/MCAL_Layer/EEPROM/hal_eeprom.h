/* 
 * File:   hal_eeprom.h
 * Author: Mohamed
 *
 * Created on September 20, 2023, 10:21 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*------------------- Includes -------------------*/
#include <pic18f4620.h>
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_external_interrupt.h"


/*------------------- Macro Declarations -------------------*/
#define ACCESS_FLASH_PROGRAM_MEMORY        1
#define ACCESS_EEPROM_PROGRAM_MEMORY       0
#define ACCESS_CONFIGRATION_BITS           1
#define ACCESS_FLASH_EEPROM_MEMORY         0
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM    1
#define INHIBITS_WRITE_CYCLES_FLASH_EEPROM 0
#define INITIATES_DATA_EEPROM_ERASE        1
#define WRITE_CYCLE_EEPROM_COMPLETED       0
#define INITIATES_EEPROM_READ              1
#define DOES_NOT_INITIATES_EEPROM_READ     0

/*------------------- Macro Functions Declarations -------------------*/

/*------------------- Data Type Declarations -------------------*/

/*------------------- Software Interfaces -------------------*/
Std_ReturnType EEPROM_Data_Write(uint16 Add, uint8 Data);
Std_ReturnType EEPROM_Data_Read(uint16 Add, uint8 *Data);


#endif	/* HAL_EEPROM_H */

