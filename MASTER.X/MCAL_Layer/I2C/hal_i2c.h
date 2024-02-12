/* 
 * File:   hal_i2c.h
 * Author: Mohamed
 *
 * Created on October 6, 2023, 6:43 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H
/*------------------- Includes -------------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include <pic18f4620.h>

/*------------------- Macro Declarations -------------------*/
/* Slew Rate Control BIT */
#define I2C_SLEW_RATE_CONTROL_ENABLE              1
#define I2C_SLEW_RATE_CONTROL_DISABLE             0
/* SMBus Select bit*/
#define I2C_SMBUS_ENABLE     1
#define I2C_SMBUS_DISABLE    0
/* Master Or Slave Mode */
#define I2C_MASTER_MODE   1
#define I2C_SLAVE_MODE    0
/* Master Synchronous Serial Port Enable bit*/
#define I2C_MODULE_ENABLE     1
#define I2C_MODULE_DISABLE     0
/* Master Synchronous Serial Port Mode Select bits */
#define I2C_MASTER_MODE_WITH_CLOCK                                 0X08
#define I2C_MASTER_MODE_FIRMWARE_CONTROL                           0X0B
#define I2C_SLAVE_MODE_7BIT_ADDRESS                                0X06
#define I2C_SLAVE_MODE_10BIT_ADDRESS                               0X07
#define I2C_SLAVE_MODE_7BIT_ADDRESS_START_STOP_INTERRUPT           0X0E
#define I2C_SLAVE_MODE_10BIT_ADDRESS_START_STOP_INTERRUPT          0X0F
/* General Call Enable bit (Slave mode only) */
#define I2C_GENERAL_CALL_ENABLE         1
#define I2C_GENERAL_CALL_DISABLE        0
/*  Start bit(1) */
#define I2C_START_BIT_DETECTED       1
#define I2C_START_BIT_NOT_DETECTED   0
/*  STOP bit(1) */
#define I2C_STOP_BIT_DETECTED       1
#define I2C_STOP_BIT_NOT_DETECTED   0
/*T: Acknowledge Status bit (Master Transmit mode only)*/
#define I2C_ACK_RECEIVED_FROM_SLAVE       0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE   1
/* : Acknowledge Data bit (Master Receive mode only) */
#define I2C_MASTER_SEND_ACK      0
#define I2C_MASTER_SEND_NOT_ACK  1
/*------------------- Macro Functions Declarations -------------------*/
/* Master Synchronous Serial Port Enable bit*/
#define I2C_MODULE_CFG_ENABLE()              (SSPCON1bits.SSPEN = 1)
#define I2C_MODULE_CFG_DISABLE()             (SSPCON1bits.SSPEN = 0)
/* Slew Rate Control BIT */
#define I2C_SLEW_RATE_CFG_ENABLE()           (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_CFG_DISABLE()          (SSPSTATbits.SMP = 0)
/* SMBus Select bit*/
#define I2C_SM_BUS_CFG_ENABLE()              (SSPSTATbits.CKE = 1)
#define I2C_SM_BUS_CFG_DISABLE()             (SSPSTATbits.CKE = 0)
/* : General Call Enable bit (Slave mode only) */
#define I2C_GENERAL_CALL_CFG_ENABLE()        (SSPCON2bits.GCEN = 1)
#define I2C_GENERAL_CALL_CFG_DISABLE()       (SSPCON2bits.GCEN = 0)
/* : Receive Enable bit (Master mode only) */
#define I2C_MASTER_RECEIVE_CFG_ENABLE()      (SSPCON2bits.RCEN = 1)
#define I2C_MASTER_RECEIVE_CFG_DISABLE()     (SSPCON2bits.RCEN = 0)
/*------------------- Data Type Declarations -------------------*/
typedef struct{
    uint8 i2c_Mode_cfg; /* Master Synchronous Serial Port Mode Select bits */
    uint8 i2c_slave_address; /* i2c slave address */
    uint8 i2c_Mode : 1;  /* : Master Synchronous Serial Port Enable bit */
    uint8 SMBus : 1; /* SMBus Enable/Disable */
    uint8 slew_rate : 1; /* Slew Rate Enable/Disable */
    uint8 general_call : 1; /* : General Call Enable bit (Slave mode only) */
    uint8 master_receive_enable : 1;  /* Receive Enable bit (Master mode only) */
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority BUS_Collision_priority;
    interrupt_priority MSSP_I2C_priority;
#endif
}i2c_cfg_t;
typedef struct{
    uint32 i2c_clock;
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* I2C_DeaultIntrruptHandler)(void);
    void (* I2C_Report_Write_Collosion)(void);
    void (* I2C_Report_Receive_Overflow)(void);
#endif
    i2c_cfg_t i2c_cfg;
}MSSP_I2C_t;

/*------------------- Software Interfaces Declarations -------------------*/
Std_ReturnType I2C_Initialize(const MSSP_I2C_t *_i2c_);
Std_ReturnType I2C_Deinitialize(const MSSP_I2C_t *_i2c_);

Std_ReturnType I2C_Master_Start(const MSSP_I2C_t *_i2c_);
Std_ReturnType I2C_Master_Repeated_Start(const MSSP_I2C_t *_i2c_);
Std_ReturnType I2C_Master_Stop(const MSSP_I2C_t *_i2c_);

Std_ReturnType I2C_Master_Write_Blocking(const MSSP_I2C_t *_i2c_, uint8 _data_, uint8 *_ack);
Std_ReturnType I2C_Master_Read_Blocking(const MSSP_I2C_t *_i2c_, uint8 *_data_, uint8 _ack);

Std_ReturnType I2C_Master_Write_Flag(const MSSP_I2C_t *_i2c_, uint8 _data_, uint8 *_ack);
Std_ReturnType I2C_Master_Read_Flag(const MSSP_I2C_t *_i2c_, uint8 *_data_, uint8 *_ack);

#endif	/* HAL_I2C_H */

