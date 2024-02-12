/* 
 * File:   hal_spi.c
 * Author: Mohamed
 *
 * Created on November 24, 2023, 9:18 AM
 */

#include "hal_spi.h"


Std_ReturnType SPI_Initialize(const MSSP_SPI_t *_spi){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _spi){
        status = E_NOT_OK;
    }
    else{
        /* disable spi module */
        SPI_MODULE_CFG_DISABLE();
        /* configure i/o pins */
        TRISCbits.RC5 = 0;
        TRISCbits.RC3 = 0;
        TRISAbits.RA5 = 0;
        /* spi mode CFG */
        SPI_MODULE_CFG_SELECT(_spi->spi_mode);
        /* clk polarity */
        if(SPI_CLK_HIGH_AT_IDLE_STATE == _spi->spi_clock_polarity){
            SPI_POLARITY_CFG_HIGH_LEVEL();
        }
        else if(SPI_CLK_LOW_AT_IDLE_STATE == _spi->spi_clock_polarity){
            SPI_POLARITY_CFG_LOW_LEVEL();
        }
        else{/* Nothing */}
        /* SPI Clock Select bit */
        if(SPI_TRANSMIT_FROM_IDLE_TO_ACTIVE == _spi->spi_transmit_clk_select){
            SPI_TRANSMISSION_CFG_FROM_IDLE_TO_ACTIVE();
        }
        else if(SPI_TRANSMIT_FROM_ACTIVE_TO_IDLE == _spi->spi_transmit_clk_select){
            SPI_TRANSMISSION_CFG_FROM_ACTIVE_TO_IDLE();
        }
        else{/* Nothing */}
        /* enable spi module */
        SPI_MODULE_CFG_ENABLE();
        status = E_OK;
    }
    return status;
}

Std_ReturnType SPI_Deinitialize(){
    Std_ReturnType status = E_NOT_OK;
        SPI_MODULE_CFG_DISABLE();
        status = E_OK;
    return status;
}

Std_ReturnType SPI_Master_Send_Byte_polling(uint8 data){
    Std_ReturnType status = E_NOT_OK;
        SSPBUF = data;
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF = 0;
        data = SSPBUF;
        status = E_OK;
    return status;
}

Std_ReturnType SPI_Master_Receive_Byte_polling(uint8 *data){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == data){
        status = E_NOT_OK;
    }
    else{
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF = 0;
        *data = SSPBUF;
        status = E_OK;
    }
    return status;
}
