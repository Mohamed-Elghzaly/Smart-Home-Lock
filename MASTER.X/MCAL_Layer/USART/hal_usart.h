/* 
 * File:   hal_usart.h
 * Author: Mohamed
 *
 * Created on October 2, 2023, 9:52 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/*------------------- Includes -------------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include <pic18f4620.h>
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "hal_usart_cfg.h"

/*------------------- Macro Declarations -------------------*/
/*   (usart)Serial Port Enable bit  */
#define USART_MODULE_ENABLE          1
#define USART_MODULE_DISABLE         0
/*  EUSART Mode Select bit  */
#define USART_SYNC_MODE          1
#define USART_ASYNC_MODE         0
/*  16-Bit Baud Rate Register Enable bit */
#define USART_16BIT_BAUD_RATE_GEN       1
#define USART_8BIT_BAUD_RATE_GEN        0
/* High Baud Rate Select bit */
#define USART_ASYNC_HIGH_SPEED            1
#define USART_ASYNC_LOW_SPEED             0

/*  Transmit Enable bit */
#define USART_ASYNC_TX_ENABLE            1
#define USART_ASYNC_TX_DISABLE           0
/*  Transmit Enable bit */
#define USART_ASYNC_TX_INTERRUPT_ENABLE            1
#define USART_ASYNC_TX_INTERRUPT_DISABLE           0
/* 9-Bit Transmit Enable bit */
#define USART_ASYNC_TX_9BIT_ENABLE        1
#define USART_ASYNC_TX_9BIT_DISABLE       0

/*  receiver Enable bit */
#define USART_ASYNC_RX_ENABLE            1
#define USART_ASYNC_RX_DISABLE           0
/*  receiver Enable bit */
#define USART_ASYNC_RX_INTERRUPT_ENABLE            1
#define USART_ASYNC_RX_INTERRUPT_DISABLE           0
/* 9-Bit receiver Enable bit */
#define USART_ASYNC_RX_9BIT_ENABLE        1
#define USART_ASYNC_RX_9BIT_DISABLE       0

/*  Framing Error bit  */
#define USART_FRAMING_ERR       1
#define USART_NO_FRAMING_ERR    0
/*  Overrun Error bit  */
#define USART_OVERRUN_ERR       1
#define USART_NO_OVERRUN_ERR    0

/*  BAUD RATE FORMULAS */
#define BAUDRATE_ASYNC_8BIT_LOW_SPEED    0
#define BAUDRATE_ASYNC_8BIT_HIGH_SPEED   1
#define BAUDRATE_ASYNC_16BIT_LOW_SPEED   2
#define BAUDRATE_ASYNC_16BIT_HIGH_SPEED  3
#define BAUDRATE_SYNC_8BIT               4
#define BAUDRATE_SYNC_16BIT              5

/*------------------- Macro Functions Declarations -------------------*/

/*------------------- Data Type Declarations -------------------*/
typedef struct{
    uint8 usart_tx_enable : 1;
    uint8 usart_tx_interrupt_enable : 1;
    uint8 usart_tx_9Bit_enable : 1;
    interrupt_priority tx_priority;
}usart_tx_cfg_t;

typedef struct{
    uint8 usart_rx_enable : 1;
    uint8 usart_rx_interrupt_enable : 1;
    uint8 usart_rx_9Bit_enable : 1;
    interrupt_priority rx_priority;
}usart_rx_cfg_t;
typedef union{
    struct{
        uint8 usart_ferr : 1;
        uint8 usart_oerr : 1;
    };
    uint8 err_state;
}usart_err_status_t;
typedef struct{
    uint32 baudrate;
    uint8 baudrate_formula : 3;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_err_status_t usart_err_status;
    void(* EUSART_TXInterruptHandler)(void);
    void(* EUSART_RXInterruptHandler)(void);
    void(* EUSART_FramingErrorHandler)(void);
    void(* EUSART_OverrunErrorHandler)(void);
}usart_t;

/*------------------- Software Interfaces Declarations -------------------*/
Std_ReturnType eusart_Async_Initialize(const usart_t *_usart);
Std_ReturnType eusart_Async_Deinitialize(const usart_t *_usart);
Std_ReturnType eusart_Async_Read_Byte_Blocking(uint8 *_data);
Std_ReturnType eusart_Async_Read_Byte_Flag(uint8 *_data);
Std_ReturnType eusart_RX_Restart(void);
Std_ReturnType eusart_Async_Write_Byte_Blocking(uint8 _data);
Std_ReturnType eusart_Async_Write_String_Blocking(uint8 *_data, uint32 str_length);
Std_ReturnType eusart_Async_Write_Byte_Flag(uint8 _data);
Std_ReturnType eusart_Async_Write_String_Flag(uint8 *_data, uint32 str_length);

#endif	/* HAL_USART_H */

