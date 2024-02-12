/* 
 * File:   hal_i2c.c
 * Author: Mohamed
 *
 * Created on October 6, 2023, 6:43 PM
 */
#include "hal_i2c.h"

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*MSSP_I2C_InterruptHandler)(void) = NULL;
static void (*MSSP_I2C_Recieve_OverFlow_InterruptHandler)(void) = NULL;
static void (*MSSP_I2C_collision_IntrruptHandler)(void) = NULL;
#endif

void inline GPIO_Config(void);
void Master_Mode_Clock_CFG(const MSSP_I2C_t *_i2c_);
static inline void MSSP_I2C_Intrrupt_Config(const MSSP_I2C_t *_i2c_);
void Slave_Mode_Clock_CFG(const MSSP_I2C_t *_i2c_);

Std_ReturnType I2C_Initialize(const MSSP_I2C_t *_i2c){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _i2c){
        status = E_NOT_OK;
    }
    else{
        /* DISABLE module */
        I2C_MODULE_CFG_DISABLE();
        /* MSSP Select mode */
        if(I2C_MASTER_MODE == _i2c->i2c_cfg.i2c_Mode){
            /* I2C Master Mode configuration */
            Master_Mode_Clock_CFG(_i2c);
        }
        else if(I2C_SLAVE_MODE == _i2c->i2c_cfg.i2c_Mode){
            /* : General Call Enable bit (Slave mode only) */
            if(I2C_GENERAL_CALL_ENABLE == _i2c->i2c_cfg.general_call){
                I2C_GENERAL_CALL_CFG_ENABLE();
            }
            else if(I2C_GENERAL_CALL_DISABLE == _i2c->i2c_cfg.general_call){
                I2C_GENERAL_CALL_CFG_DISABLE();
            }
            else{ /* Nothing */}
            /* Clear write Colision */
            SSPCON1bits.WCOL = 0;
            /* Overflow Indicator*/
            SSPCON1bits.SSPOV = 0;
            /* Release Clock */
            SSPCON1bits.CKP = 1;
            /* assign I2C Slave Address */
            SSPADD = _i2c->i2c_cfg.i2c_slave_address;
            /* i2c slave configuration */
            Slave_Mode_Clock_CFG(_i2c);
        }
        else{ /* Nothing */}
        /* I2C GPIO Configuration */
        GPIO_Config();
        /* Slew Rate Control BIT */
        if(I2C_SLEW_RATE_CONTROL_ENABLE == _i2c->i2c_cfg.slew_rate){
                I2C_SLEW_RATE_CFG_ENABLE();
            }
            else if(I2C_SLEW_RATE_CONTROL_DISABLE == _i2c->i2c_cfg.slew_rate){
                I2C_SLEW_RATE_CFG_DISABLE();
            }
            else{ /* Nothing */}
        /* INTERRUPT FEATURE*/
        MSSP_I2C_Intrrupt_Config(_i2c);
        /* Enable module */
        I2C_MODULE_CFG_ENABLE();
        status = E_OK;
    }
    return status;
}

Std_ReturnType I2C_Deinitialize(const MSSP_I2C_t *_i2c){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _i2c){
        status = E_NOT_OK;
    }
    else{
        /* DISABLE module */
        I2C_MODULE_CFG_DISABLE();
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_INTERRUPT_DISABLE();
        MSSP_I2C_BUS_COLLISION_DISABLE();
#endif
        status = E_OK;
    }
    return status;
}

Std_ReturnType I2C_Master_Start(const MSSP_I2C_t *_i2c){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _i2c){
        status = E_NOT_OK;
    }
    else{
        /* Initiate start Condition */
        SSPCON2bits.SEN = 1;
        /* wait to complete start condition */
        while(SSPCON2bits.SEN);
        /* claer MSSP Interrupt Flag */
        PIR1bits.SSPIF = 0;
        /* report start condition detection */
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S){
            status = E_OK;
        }
        else if(I2C_START_BIT_NOT_DETECTED == SSPSTATbits.S){
            status = E_NOT_OK;
        }
        else{ /* Nothing */}
    }
    return status;
}

Std_ReturnType I2C_Master_Stop(const MSSP_I2C_t *_i2c){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _i2c){
        status = E_NOT_OK;
    }
    else{
        /* Initiate stop Condition */
        SSPCON2bits.PEN = 1;
        /* wait to complete stop condition */
        while(SSPCON2bits.PEN);
        /* claer MSSP Interrupt Flag */
        PIR1bits.SSPIF = 0;
        /* report stop condition detection */
        if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P){
            status = E_OK;
        }
        else if(I2C_STOP_BIT_NOT_DETECTED == SSPSTATbits.P){
            status = E_NOT_OK;
        }
        else{ /* Nothing */}
    }
    return status;
}

Std_ReturnType I2C_Master_Repeated_Start(const MSSP_I2C_t *_i2c){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == _i2c){
        status = E_NOT_OK;
    }
    else{
        /* Initiate repeated start Condition */
        SSPCON2bits.RSEN = 1;
        /* wait to complete repeated start condition */
        while(SSPCON2bits.RSEN);
        /* claer MSSP Interrupt Flag */
        PIR1bits.SSPIF = 0;
        status = E_OK;
    }
    return status;
}

Std_ReturnType I2C_Master_Write_Blocking(const MSSP_I2C_t *_i2c, uint8 _data_, uint8 *_ack){
    Std_ReturnType status = E_NOT_OK;
    if((NULL == _i2c) || (NULL == _ack)){
        status = E_NOT_OK;
    }
    else{
        /* write data in register*/
        SSPBUF = _data_;
        /* wait transmission complete */
        while(!PIR1bits.SSPIF);
        /* claer MSSP Interrupt Flag */
        PIR1bits.SSPIF = 0;
        /* Acknowledge Status bit (Master Transmit mode only)*/
        if(SSPCON2bits.ACKSTAT == I2C_ACK_RECEIVED_FROM_SLAVE){
            *_ack = I2C_ACK_RECEIVED_FROM_SLAVE;
        }
        else{
            *_ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
        }
        status = E_OK;
    }
    return status;
}

Std_ReturnType I2C_Master_Read_Blocking(const MSSP_I2C_t *_i2c, uint8 *_data_, uint8 _ack){
    Std_ReturnType status = E_NOT_OK;
    if((NULL == _i2c) || (NULL == _ack)){
        status = E_NOT_OK;
    }
    else{
        /* Receive Enable bit (Master mode only)*/
        I2C_MASTER_RECEIVE_CFG_ENABLE();
        /* WAIT date */
        while(!SSPSTATbits.BF);
        /* copy data from buffer */
        *_data_ = SSPBUF;
        /* send ACK or not after read*/
        if(_ack == I2C_MASTER_SEND_ACK){
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_ACK;
        }
        else if(_ack == I2C_MASTER_SEND_NOT_ACK){
            SSPCON2bits.ACKDT = I2C_MASTER_SEND_NOT_ACK;
        }
        else{/* Nothing */}
        /* Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. Automatically */
        SSPCON2bits.ACKEN = 1;
        status = E_OK;
    }
    return status;
}


void inline GPIO_Config(void){
    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;
}

void Master_Mode_Clock_CFG(const MSSP_I2C_t *_i2c){
    SSPCON1bits.SSPM = I2C_MASTER_MODE_WITH_CLOCK;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / _i2c->i2c_clock) - 1);
}

static inline void MSSP_I2C_Intrrupt_Config(const MSSP_I2C_t *_i2c_){
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_INTERRUPT_ENABLE();
        MSSP_I2C_BUS_COLLISION_ENABLE();
        MSSP_I2C_INTERRUPT_CLEAR_FLAG();
        MSSP_I2C_BUS_COLLISION_CLEAR_FLAG();
        MSSP_I2C_Recieve_OverFlow_InterruptHandler = _i2c_->I2C_Report_Receive_Overflow;
        MSSP_I2C_InterruptHandler = _i2c_->I2C_DeaultIntrruptHandler;
        MSSP_I2C_collision_IntrruptHandler = _i2c_->I2C_Report_Write_Collosion;
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_ENABLE();
        if(LOW_PRIORITY_INTERRUPT == _i2c_->i2c_cfg.MSSP_I2C_priority){
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            MSSP_I2C_INTERRUPT_PRIORITY_LOW();
        }
        else if(HIGH_PRIORITY_INTERRUPT == _i2c_->i2c_cfg.MSSP_I2C_priority){
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            MSSP_I2C_INTERRUPT_PRIORITY_HIGH();
        }
        if(LOW_PRIORITY_INTERRUPT == _i2c_->i2c_cfg.BUS_Collision_priority){
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            MSSP_I2C_BUS_COLLISION_PRIORITY_LOW();
        }
        else if(HIGH_PRIORITY_INTERRUPT == _i2c_->i2c_cfg.BUS_Collision_priority){
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            MSSP_I2C_BUS_COLLISION_PRIORITY_HIGH();
        }
#else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
}

void Slave_Mode_Clock_CFG(const MSSP_I2C_t *_i2c){
    SSPCON1bits.SSPM = _i2c->i2c_cfg.i2c_Mode_cfg;
}

void MSSP_I2C_ISR(void){
    MSSP_I2C_INTERRUPT_CLEAR_FLAG();
    if(MSSP_I2C_InterruptHandler){
        MSSP_I2C_InterruptHandler();
    }else{}
}

void MSSP_I2C_BUS_Colision(void){
    MSSP_I2C_BUS_COLLISION_CLEAR_FLAG();
    if(MSSP_I2C_collision_IntrruptHandler){
        MSSP_I2C_collision_IntrruptHandler();
    }else{}
}