/* 
 * File:   hal_usart.c
 * Author: Mohamed
 *
 * Created on October 2, 2023, 9:52 PM
 */

#include "hal_usart.h"

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* EUSART_TX_InterruptHandler)(void) = NULL;
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* EUSART_RX_InterruptHandler)(void) = NULL;
static void(* EUSART_OverrunErr_InterruptHandler)(void) = NULL;
static void(* EUSART_FramingErr_InterruptHandler)(void) = NULL;
#endif


static void eusart_BaudRate_Calculation(const usart_t *_usart);
static void eusart_Async_TX_Init(const usart_t *_usart);
static void eusart_Async_RX_Init(const usart_t *_usart);

Std_ReturnType eusart_Async_Initialize(const usart_t *_usart){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _usart){
        status = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = USART_MODULE_DISABLE;
        eusart_BaudRate_Calculation(_usart);
        eusart_Async_TX_Init(_usart);
        eusart_Async_RX_Init(_usart);
        RCSTAbits.SPEN = USART_MODULE_ENABLE;
        status = E_OK;
    }
    return status;
}

Std_ReturnType eusart_Async_Deinitialize(const usart_t *_usart){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _usart){
        status = E_NOT_OK;
    }
    else{
        RCSTAbits.SPEN = USART_MODULE_DISABLE;
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EUSART_TX_INTERRUPT_DISABLE();
#endif
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EUSART_RX_INTERRUPT_DISABLE();
#endif
        status = E_OK;
    }
    return status;
}

Std_ReturnType eusart_Async_Read_Byte_Blocking(uint8 *_data){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _data){
        status = E_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
        *_data = RCREG;
        status = E_OK;
    }
    return status;
}

Std_ReturnType eusart_Async_Read_Byte_Flag(uint8 *_data){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _data){
        status = E_NOT_OK;
    }
    else{
        if(1 == PIR1bits.RCIF){
            *_data = RCREG;
            status = E_OK;
        }
        else{status = E_NOT_OK;}
    }
    return status;
}

Std_ReturnType eusart_RX_Restart(void){
    Std_ReturnType status = E_NOT_OK;
    RCSTAbits.CREN = USART_ASYNC_RX_DISABLE;
    RCSTAbits.CREN = USART_ASYNC_RX_ENABLE;
    status = E_OK;
    return status;
}

Std_ReturnType eusart_Async_Write_Byte_Flag(uint8 _data){
    Std_ReturnType status = E_NOT_OK;
    if(1 == PIR1bits.TXIF){
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EUSART_TX_INTERRUPT_ENABLE();
#endif
            TXREG = _data;
            status = E_OK;
        }
        else{status = E_NOT_OK;}
    return status;
}

Std_ReturnType eusart_Async_Write_String_Flag(uint8 *_data, uint32 str_length){
    Std_ReturnType status = E_NOT_OK;
    uint32 iterator = 0;
    if(NULL == _data){
        status = E_NOT_OK;
    }
    else{
        for(iterator = 0; iterator<str_length; iterator++){
            status = eusart_Async_Write_Byte_Flag(_data[iterator]);
        }
        status = E_OK;
    }
    return status;
}

Std_ReturnType eusart_Async_Write_Byte_Blocking(uint8 _data){
    Std_ReturnType status = E_OK;
    while(!TXSTAbits.TRMT);
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EUSART_TX_INTERRUPT_ENABLE();
#endif
    TXREG = _data;
    return status;
}

Std_ReturnType eusart_Async_Write_String_Blocking(uint8 *_data, uint32 str_length){
    Std_ReturnType status = E_NOT_OK;
    uint32 iterator = 0;
    if(NULL == _data){
        status = E_NOT_OK;
    }
    else{
        for(iterator = 0; iterator<str_length; iterator++){
            status = eusart_Async_Write_Byte_Blocking(_data[iterator]);
        }
        status = E_OK;
    }
    return status;
}


static void eusart_BaudRate_Calculation(const usart_t *_usart){
    float32 l_BaudRate = 0;
    switch(_usart->baudrate_formula){
        case BAUDRATE_ASYNC_8BIT_LOW_SPEED:
            TXSTAbits.SYNC = USART_ASYNC_MODE;
            TXSTAbits.BRGH = USART_ASYNC_LOW_SPEED;
            BAUDCONbits.BRG16 = USART_8BIT_BAUD_RATE_GEN;
            l_BaudRate = ((_XTAL_FREQ / (float32)_usart->baudrate) / 64) - 1;
            break;
        case BAUDRATE_ASYNC_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = USART_ASYNC_MODE;
            TXSTAbits.BRGH = USART_ASYNC_HIGH_SPEED;
            BAUDCONbits.BRG16 = USART_8BIT_BAUD_RATE_GEN;
            l_BaudRate = ((_XTAL_FREQ / (float32)_usart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYNC_16BIT_LOW_SPEED:
            TXSTAbits.SYNC = USART_ASYNC_MODE;
            TXSTAbits.BRGH = USART_ASYNC_LOW_SPEED;
            BAUDCONbits.BRG16 = USART_16BIT_BAUD_RATE_GEN;
            l_BaudRate = ((_XTAL_FREQ / (float32)_usart->baudrate) / 16) - 1;
            break;
        case BAUDRATE_ASYNC_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = USART_ASYNC_MODE;
            TXSTAbits.BRGH = USART_ASYNC_HIGH_SPEED;
            BAUDCONbits.BRG16 = USART_16BIT_BAUD_RATE_GEN;
            l_BaudRate = ((_XTAL_FREQ / (float32)_usart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYNC_8BIT:
            TXSTAbits.SYNC = USART_SYNC_MODE;
            BAUDCONbits.BRG16 = USART_8BIT_BAUD_RATE_GEN;
            l_BaudRate = ((_XTAL_FREQ / (float32)_usart->baudrate) / 4) - 1;
            break;
        case BAUDRATE_SYNC_16BIT:
            TXSTAbits.SYNC = USART_SYNC_MODE;
            BAUDCONbits.BRG16 = USART_16BIT_BAUD_RATE_GEN;
            l_BaudRate = ((_XTAL_FREQ / (float32)_usart->baudrate) / 4) - 1;
            break;
        default : ;
    }
    SPBRG = (uint8)((uint32)l_BaudRate);
    SPBRGH = (uint8)(((uint32)l_BaudRate) >> 8);
}

static void eusart_Async_TX_Init(const usart_t *_usart){
        TRISCbits.RC6 = 1;
    /* Transmit Enable bit CFG*/
    if(USART_ASYNC_TX_ENABLE == _usart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = USART_ASYNC_TX_ENABLE;
        /* EUSART Transmit Interrupt CFG*/
        if(USART_ASYNC_TX_INTERRUPT_ENABLE == _usart->usart_tx_cfg.usart_tx_interrupt_enable){
            PIE1bits.TXIE = USART_ASYNC_TX_INTERRUPT_ENABLE;
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            EUSART_TX_INTERRUPT_ENABLE();
            EUSART_TX_InterruptHandler = _usart->EUSART_TXInterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_ENABLE();
            if(LOW_PRIORITY_INTERRUPT == _usart->usart_tx_cfg.tx_priority){
                INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
                EUSART_TX_INTERRUPT_PRIORITY_LOW();
            }
            else if(HIGH_PRIORITY_INTERRUPT == _usart->usart_tx_cfg.tx_priority){
                INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
                EUSART_TX_INTERRUPT_PRIORITY_HIGH();
            }
#else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
        }
        else if(USART_ASYNC_TX_INTERRUPT_DISABLE == _usart->usart_tx_cfg.usart_tx_interrupt_enable){
                    PIE1bits.TXIE = USART_ASYNC_TX_INTERRUPT_DISABLE;
        }else{/* Nothing */}
        /*  9-Bit Transmit Enable bit CFG*/
        if(USART_ASYNC_TX_9BIT_ENABLE == _usart->usart_tx_cfg.usart_tx_9Bit_enable){
           TXSTAbits.TX9 = USART_ASYNC_TX_9BIT_ENABLE;
        }
        else if(USART_ASYNC_TX_9BIT_DISABLE == _usart->usart_tx_cfg.usart_tx_9Bit_enable){
            TXSTAbits.TX9 = USART_ASYNC_TX_9BIT_DISABLE;
        }else{/* Nothing */}
    }
    else if(USART_ASYNC_TX_DISABLE == _usart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = USART_ASYNC_TX_DISABLE;
    }else{/* Nothing */}
}

static void eusart_Async_RX_Init(const usart_t *_usart){
        TRISCbits.RC7 = 1;
    /* receiver Enable bit CFG*/
    if(USART_ASYNC_RX_ENABLE == _usart->usart_rx_cfg.usart_rx_enable){ 
        RCSTAbits.CREN = USART_ASYNC_RX_ENABLE;
        /* EUSART receiver Interrupt CFG*/
        if(USART_ASYNC_RX_INTERRUPT_ENABLE == _usart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = USART_ASYNC_RX_INTERRUPT_ENABLE;
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            EUSART_RX_INTERRUPT_ENABLE();
            EUSART_RX_InterruptHandler = _usart->EUSART_RXInterruptHandler;
            EUSART_OverrunErr_InterruptHandler = _usart->EUSART_OverrunErrorHandler;
            EUSART_FramingErr_InterruptHandler = _usart->EUSART_FramingErrorHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_ENABLE();
            if(LOW_PRIORITY_INTERRUPT == _usart->usart_rx_cfg.rx_priority){
                INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
                EUSART_RX_INTERRUPT_PRIORITY_LOW();
            }
            else if(HIGH_PRIORITY_INTERRUPT == _usart->usart_rx_cfg.rx_priority){
                INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
                EUSART_RX_INTERRUPT_PRIORITY_HIGH();
            }
#else
            INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
            INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
        }
        else if(USART_ASYNC_RX_INTERRUPT_DISABLE == _usart->usart_rx_cfg.usart_rx_interrupt_enable){
            PIE1bits.RCIE = USART_ASYNC_RX_INTERRUPT_DISABLE;
        }else{/* Nothing */}
        /*  9-Bit receiver Enable bit CFG*/
        if(USART_ASYNC_RX_9BIT_ENABLE == _usart->usart_rx_cfg.usart_rx_9Bit_enable){
           RCSTAbits.RC9 = USART_ASYNC_RX_9BIT_ENABLE;
        }
        else if(USART_ASYNC_RX_9BIT_DISABLE == _usart->usart_rx_cfg.usart_rx_9Bit_enable){
           RCSTAbits.RC9 = USART_ASYNC_RX_9BIT_DISABLE;
        }else{/* Nothing */}
    }
    else if(USART_ASYNC_RX_DISABLE == _usart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN = USART_ASYNC_RX_DISABLE;
    }else{/* Nothing */}
}


#if EUSART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void EUSART_RX_ISR(void){
    if(EUSART_RX_InterruptHandler){
        EUSART_RX_InterruptHandler();
    }else{/* Nothing */}
    if(EUSART_FramingErr_InterruptHandler){
        EUSART_FramingErr_InterruptHandler();
    }else{/* Nothing */}
    if(EUSART_OverrunErr_InterruptHandler){
        EUSART_OverrunErr_InterruptHandler();
    }else{/* Nothing */}
}
#endif

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
void EUSART_TX_ISR(void){
    EUSART_TX_INTERRUPT_DISABLE();
    if(EUSART_TX_InterruptHandler){
        EUSART_TX_InterruptHandler();
    }else{/* Nothing */}
}
#endif