/* 
 * File:   hal_ccp1.h
 * Author: Mohamed
 *
 * Created on September 27, 2023, 10:26 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H
/*------------------- Includes -------------------*/
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "pic18f4620.h"
#include "hal_ccp1_cfg.h"

/*------------------- Macro Declarations -------------------*/
/* CCP1 mode select */
#define CCP_MODULE_DISABLED                          0
#define CCP_CAPTURE_MODE_1TH_FALLING_EDGE            4
#define CCP_CAPTURE_MODE_1TH_RISING_EDGE             5
#define CCP_CAPTURE_MODE_4TH_FALLING_EDGE            6
#define CCP_CAPTURE_MODE_4TH_RISING_EDGE             7
#define CCP_COMPARE_MODE_SET_PIN                     8
#define CCP_COMPARE_MODE_CLEAR_PIN                   9
#define CCP_COMPARE_MODE_TOGGLE_PIN                  2
#define CCP_COMPARE_MODE_GENERATE_INTERRUPT          10
#define CCP_COMPARE_MODE_SPECIAL_EVENT               11
#define CCP_PWM_MODE                                 12

/* CCP Capture state */
#define CCP_CAPTURE_OCCUR                       1
#define CCP_CAPTURE_NOT_OCCUR                   0
/* CCP Compare state */
#define CCP_COMPARE_OCCUR                       1
#define CCP_COMPARE_NOT_OCCUR                   0

/* : CCP Input Clock Prescaler Select bits */
#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        4
#define CCP_TIMER2_PRESCALER_DIV_BY_16       16
/* : CCP Input Clock Postscaler Select bits */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1        1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2        2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3        3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4        4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5        5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6        6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7        7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8        8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9        9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10       10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11       11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12       12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13       13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14       14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15       15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16       16

#define CCP1_CCP2_TIMER3          0
#define CCP1_TIMER1_CCP2_TIMER3   1
#define CCP1_CCP2_TIMER1          2
/*------------------- Macro Functions Declarations -------------------*/
#define CCP1_MODE_SELECT(_CFG)                (CCP1CONbits.CCP1M = _CFG)
#define CCP2_MODE_SELECT(_CFG)                (CCP2CONbits.CCP2M = _CFG)


/*------------------- Data Type Declarations -------------------*/
typedef enum{
    CCP1_MODULE = 0,
    CCP2_MODULE
}CCP_select_module;

typedef union{
    struct{
        uint8 ccp_low;
        uint8 ccp_high;
    };
    struct{
        uint16 ccp_16Bit;
    };
}CCP_reg_t;

typedef struct{
    CCP_select_module select_module;
    uint8 ccp_mode : 4;
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* CCP1_InterruptHandler)(void);
    interrupt_priority CCP1_priority;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* CCP2_InterruptHandler)(void);
    interrupt_priority CCP2_priority;
#endif
#if (CCP1_CFG_MODE_SELECTED==CCP_CFG_PWM_MODE) || (CCP2_CFG_MODE_SELECTED==CCP_CFG_PWM_MODE)
    uint8 postscaler_value: 4;
    uint8 prescaler_value : 2;
    uint32 PWM_frequancy ;
#endif
    uint8 capture_timer : 2;

}ccp_t;

/*------------------- Software Interfaces Declarations -------------------*/
#if (CCP1_CFG_MODE_SELECTED==CCP_CFG_PWM_MODE) || (CCP2_CFG_MODE_SELECTED==CCP_CFG_PWM_MODE)
Std_ReturnType CCP_PWM_Initialize(const ccp_t *_obj);
Std_ReturnType CCP_PWM_Deinitialize(const ccp_t *_obj);
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_obj, const uint8 _duty);
Std_ReturnType CCP_PWM_Start(const ccp_t *_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_t *_obj);
#endif

#if (CCP1_CFG_MODE_SELECTED==CCP_CFG_COMPARE_MODE) || (CCP2_CFG_MODE_SELECTED==CCP_CFG_COMPARE_MODE)
Std_ReturnType CCP_CompareMode_Initialize(const ccp_t *_obj);
Std_ReturnType CCP_CompareMode_Deinitialize(const ccp_t *_obj);
Std_ReturnType CCP_IsCompare_Complete(const ccp_t *_obj, uint8 *_compare);
Std_ReturnType CCP_CompareMode_Set_Value(const ccp_t *_obj, uint16 _compare);
#endif

#if (CCP1_CFG_MODE_SELECTED==CCP_CFG_CAPTURE_MODE) || (CCP2_CFG_MODE_SELECTED==CCP_CFG_CAPTURE_MODE)
Std_ReturnType CCP_CaptureMode_Initialize(const ccp_t *_obj);
Std_ReturnType CCP_CaptureMode_Deinitialize(const ccp_t *_obj);
Std_ReturnType CCP_IsCaptureOccur(const ccp_t *_obj, uint8 *_capture);
Std_ReturnType CCP_CaptureMode_Read_Value(const ccp_t *_obj, uint16 *_capture);
#endif


#endif	/* HAL_CCP1_H */

