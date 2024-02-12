/* 
 * File:   hal_spi.h
 * Author: Mohamed
 *
 * Created on November 24, 2023, 9:18 AM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/*------------------- Includes -------------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include <pic18f4620.h>

/*------------------- Macro Declarations -------------------*/
/* Master Synchronous Serial Port Enable bit */
#define SPI_MODULE_ENABLE   1
#define SPI_MODULE_DISABLE  0
/* Master Synchronous Serial Port Mode Select bits */
#define SPI_MASTER_MODE_CLK_OSC_DIV_4           0
#define SPI_MASTER_MODE_CLK_OSC_DIV_16          1
#define SPI_MASTER_MODE_CLK_OSC_DIV_64          2
#define SPI_MASTER_MODE_CLK_TMR2_DIV_2          3
#define SPI_SLAVE_MODE_SCK_PINS_SS_PIN_ENABLE   4
#define SPI_SLAVE_MODE_SCK_PINS_SS_PIN_DISABLE  5
/*  Clock Polarity Select */
#define SPI_CLK_HIGH_AT_IDLE_STATE   1
#define SPI_CLK_LOW_AT_IDLE_STATE    0
/* SPI Clock Select bit */
#define SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE     1
#define SPI_TRANSMIT_FROM_IDLE_TO_ACTIVE     0
/*  Sample bit */
#define SPI_INPUT_DATA_SAMPLED_AT_END_OF_DATA      1
#define SPI_INPUT_DATA_SAMPLED_AT_MIDDLE_OF_DATA   0
/* Write Collision Detect bit */
#define SPI_COLLOSION_OCCURED        1
#define SPI_COLLOSION_NOT_OCCURED    0
/* */

/*------------------- Macro Functions Declarations -------------------*/
/* DISABLE/ENABLE spi module */
#define SPI_MODULE_CFG_ENABLE()       (SSPCON1bits.SSPEN = 1)
#define SPI_MODULE_CFG_DISABLE()      (SSPCON1bits.SSPEN = 0)
/* Master Synchronous Serial Port Mode Select bits */
#define SPI_MODULE_CFG_SELECT(_CFG)        (SSPCON1bits.SSPM = _CFG)
/*  Clock Polarity Select bit  */
#define SPI_POLARITY_CFG_HIGH_LEVEL()      (SSPCON1bits.CKP = 1)
#define SPI_POLARITY_CFG_LOW_LEVEL()       (SSPCON1bits.CKP = 0)
/*  SPI Clock Select bit */
#define SPI_TRANSMISSION_CFG_FROM_ACTIVE_TO_IDLE()    (SSPSTATbits.CKE = 1)
#define SPI_TRANSMISSION_CFG_FROM_IDLE_TO_ACTIVE()    (SSPSTATbits.CKE = 0)
/* Sample bit */
#define SPI_DATA_SAMPLED_CFG_AT_END()            (SSPSTATbits.SMP = 1)
#define SPI_DATA_SAMPLED_CFG_AT_MIDDLE()         (SSPSTATbits.SMP = 0)

/*------------------- Data Type Declarations -------------------*/
typedef struct{
    uint8 spi_mode : 1;
    uint8 spi_clock_polarity : 1;
    uint8 spi_transmit_clk_select : 1;
}MSSP_SPI_t;

/*------------------- Software Interfaces Declarations -------------------*/
Std_ReturnType SPI_Initialize(const MSSP_SPI_t *_spi);
Std_ReturnType SPI_Deinitialize(const MSSP_SPI_t *_spi);
Std_ReturnType SPI_Master_Send_Byte_polling(uint8 data);
Std_ReturnType SPI_Master_Receive_Byte_polling(uint8 *data);

#endif	/* HAL_SPI_H */

