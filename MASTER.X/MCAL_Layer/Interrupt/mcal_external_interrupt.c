/* 
 * File:   mcal_external_interrupt.c
 * Author: Mohamed
 *
 * Created on September 17, 2023, 3:01 PM
 */

/*------------------- Includes -------------------*/
#include "mcal_external_interrupt.h"

/*------------------- Software Interfaces Declarations -------------------*/
static void (* INT0_Call_Back_fun)(void) = NULL;
static void (* INT1_Call_Back_fun)(void) = NULL;
static void (* INT2_Call_Back_fun)(void) = NULL;

static void (* RB4_Call_Back_fun_HIGH)(void) = NULL;
static void (* RB4_Call_Back_fun_LOW)(void) = NULL;
static void (* RB5_Call_Back_fun_HIGH)(void) = NULL;
static void (* RB5_Call_Back_fun_LOW)(void) = NULL;
static void (* RB6_Call_Back_fun_HIGH)(void) = NULL;
static void (* RB6_Call_Back_fun_LOW)(void) = NULL;
static void (* RB7_Call_Back_fun_HIGH)(void) = NULL;
static void (* RB7_Call_Back_fun_LOW)(void) = NULL;

static Std_ReturnType (INT0_Set_Call_Back_fun)(void (* Call_Back_fun)(void));
static Std_ReturnType (INT1_Set_Call_Back_fun)(void (* Call_Back_fun)(void));
static Std_ReturnType (INT2_Set_Call_Back_fun)(void (* Call_Back_fun)(void));

static Std_ReturnType INTx_Set_Call_Back_fun(const interrupt_INTx_t *obj);

static Std_ReturnType Interrupt_INTx_pin(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_priority(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_edge(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_enable(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_disable(const interrupt_INTx_t *obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *obj);

static Std_ReturnType Interrupt_RBx_enable(const interrupt_RBx_t *obj);
static Std_ReturnType Interrupt_RBx_disable(const interrupt_RBx_t *obj);
static Std_ReturnType Interrupt_RBx_priority(const interrupt_RBx_t *obj);
static Std_ReturnType Interrupt_RBx_pin(const interrupt_RBx_t *obj);
static Std_ReturnType Interrupt_RBx_Call_Back(const interrupt_RBx_t *obj);


/**
 * 
 * @param obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Intialize(const interrupt_INTx_t *obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        status = Interrupt_INTx_disable(obj);
        status = Interrupt_INTx_Clear_Flag(obj);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        status = Interrupt_INTx_priority(obj);
        #endif
        status = Interrupt_INTx_edge(obj);
        status = Interrupt_INTx_pin(obj);
        status = INTx_Set_Call_Back_fun(obj);
        status = Interrupt_INTx_enable(obj);
        
    }
    return status;
}

void INT0_ISR(void){
    /* clear flag */
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EXT_INT0_INTERRUPT_FLAG_CLEAR();
#endif
    /* code */
    /* callback function */
    if(INT0_Call_Back_fun){INT0_Call_Back_fun();}
}
void INT1_ISR(void){
    /* clear flag */
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EXT_INT1_INTERRUPT_FLAG_CLEAR();
#endif
    /* code */
    /* callback function */
    if(INT1_Call_Back_fun){INT1_Call_Back_fun();}
}
void INT2_ISR(void){
    /* clear flag */
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EXT_INT2_INTERRUPT_FLAG_CLEAR();
#endif
    /* code */
    /* callback function */
    if(INT2_Call_Back_fun){INT2_Call_Back_fun();}
}

void RB4_ISR(uint8 RB4_src){
    /* clear flag */
#if EXT_INTERRUPT_ON_CHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
#endif
    /* code */
    /* callback function */
    if(1 == RB4_src){
        if(RB4_Call_Back_fun_LOW){RB4_Call_Back_fun_LOW();}
        else{/* Nothing*/}
    }else if(0 == RB4_src){
        if(RB4_Call_Back_fun_HIGH){RB4_Call_Back_fun_HIGH();}
        else{/* Nothing*/}
    }else{/* Nothing*/}
}
void RB5_ISR(uint8 RB5_src){
    /* clear flag */
#if EXT_INTERRUPT_ON_CHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
#endif
    /* code */
    /* callback function */
    if(1 == RB5_src){
        if(RB5_Call_Back_fun_LOW){RB5_Call_Back_fun_LOW();}
        else{/* Nothing*/}
    }else if(0 == RB5_src){
        if(RB5_Call_Back_fun_HIGH){RB5_Call_Back_fun_HIGH();}
        else{/* Nothing*/}
    }else{/* Nothing*/}
}
void RB6_ISR(uint8 RB6_src){
    /* clear flag */
#if EXT_INTERRUPT_ON_CHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
#endif
    /* code */
    /* callback function */
    if(1 == RB6_src){
        if(RB6_Call_Back_fun_LOW){RB6_Call_Back_fun_LOW();}
        else{/* Nothing*/}
    }else if(0 == RB6_src){
        if(RB6_Call_Back_fun_HIGH){RB6_Call_Back_fun_HIGH();}
        else{/* Nothing*/}
    }else{/* Nothing*/}
}
void RB7_ISR(uint8 RB7_src){
    /* clear flag */
#if EXT_INTERRUPT_ON_CHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    EXT_RBx_INTERRUPT_FLAG_CLEAR();
#endif
    /* code */
    /* callback function */
    if(1 == RB7_src){
        if(RB7_Call_Back_fun_LOW){RB7_Call_Back_fun_LOW();}
        else{/* Nothing*/}
    }else if(0 == RB7_src){
        if(RB7_Call_Back_fun_HIGH){RB7_Call_Back_fun_HIGH();}
        else{/* Nothing*/}
    }else{/* Nothing*/}
}

/**
 * 
 * @param obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeIntialize(const interrupt_INTx_t *obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        status = Interrupt_INTx_disable(obj);
    }
    return status;
}
/**
 * 
 * @param obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Intialize(const interrupt_RBx_t *obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        status = Interrupt_RBx_disable(obj);
#if EXT_INTERRUPT_ON_CHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EXT_RBx_INTERRUPT_FLAG_CLEAR();
#endif
        status = Interrupt_RBx_priority(obj);
        status = Interrupt_RBx_pin(obj);
        status = Interrupt_RBx_Call_Back(obj);
        status = Interrupt_RBx_enable(obj);
    }
    return status;
}
/**
 * 
 * @param obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeIntialize(const interrupt_RBx_t *obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        
    }
    return status;
}
/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_pin(const interrupt_INTx_t *obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        status = gpio_pin_direction_intialize(&(obj->pin));
    }
    return status;
}
/**
 * 
 * @param obj
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_priority(const interrupt_INTx_t *obj){
    Std_ReturnType status = E_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        switch(obj->number){
            case EXETERNAL_INT1 :
                if(obj->priority == LOW_PRIORITY_INTERRUPT){EXT_INT1_INTERRUPT_LOW_PRIORITY();}
                else if(obj->priority == HIGH_PRIORITY_INTERRUPT){EXT_INT1_INTERRUPT_HIGH_PRIORITY();}
                else{ /* Nothing */}
                ;break;
            case EXETERNAL_INT2 :
                if(obj->priority == LOW_PRIORITY_INTERRUPT){EXT_INT2_INTERRUPT_LOW_PRIORITY();}
                else if(obj->priority == HIGH_PRIORITY_INTERRUPT){EXT_INT2_INTERRUPT_HIGH_PRIORITY();}
                else{ /* Nothing */}
                ;break;
            default :status = E_NOT_OK; ;
        }
    }
    return status;
}
#endif
/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_edge(const interrupt_INTx_t *obj){
    Std_ReturnType status = E_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        switch(obj->number){
            case EXETERNAL_INT0 :
                if(obj->edge == FALLING_EDGE_INTERRUPT){
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                    EXT_INT0_INTERRUPT_FALLING_EDGE();
#endif
                }
                else if(obj->edge == RISING_EDGE_INTERRUPT){
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                    EXT_INT0_INTERRUPT_RISING_EDGE();
#endif
                }
                else{ /* Nothing */}
                break;
            case EXETERNAL_INT1 :
                if(obj->edge == FALLING_EDGE_INTERRUPT){
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                    EXT_INT1_INTERRUPT_FALLING_EDGE();
#endif
                }
                else if(obj->edge == RISING_EDGE_INTERRUPT){
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                    EXT_INT1_INTERRUPT_RISING_EDGE();
#endif
                }
                else{ /* Nothing */}
                break;
            case  EXETERNAL_INT2:
                if(obj->edge == FALLING_EDGE_INTERRUPT){
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                    EXT_INT2_INTERRUPT_FALLING_EDGE();
#endif
                }
                else if(obj->edge == RISING_EDGE_INTERRUPT){
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                    EXT_INT2_INTERRUPT_RISING_EDGE();
#endif
                }
                else{ /* Nothing */}
                break;
            default :status = E_NOT_OK; ;
        }
    }
    return status;
}
/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_enable(const interrupt_INTx_t *obj){
    Std_ReturnType status = E_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        switch(obj->number){
            case EXETERNAL_INT0 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
#else
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#endif
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                EXT_INT0_INTERRUPT_ENABLE();
#endif
                break;
            case EXETERNAL_INT1 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_ENABLE();
                if(obj->priority == LOW_PRIORITY_INTERRUPT){
                    INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
                }
                else if(obj->priority == HIGH_PRIORITY_INTERRUPT){
                    INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
                }
                else{ /* Nothing */}
#else
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#endif
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                EXT_INT1_INTERRUPT_ENABLE();
#endif
            break;
            case EXETERNAL_INT2 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                INTERRUPT_PRIORITY_ENABLE();
                if(obj->priority == LOW_PRIORITY_INTERRUPT){
                    INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
                }
                else if(obj->priority == HIGH_PRIORITY_INTERRUPT){
                    INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
                }
                else{ /* Nothing */}
#else
                INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
                INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#endif
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                EXT_INT2_INTERRUPT_ENABLE();
#endif
            break;
            default :status = E_NOT_OK; ;
        }
    }
    return status;
}
/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_disable(const interrupt_INTx_t *obj){
    Std_ReturnType status = E_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        switch(obj->number){
            case EXETERNAL_INT0 :
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                EXT_INT0_INTERRUPT_DISABLE();
#endif
                break;
            case EXETERNAL_INT1 :
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                EXT_INT1_INTERRUPT_DISABLE();
#endif
                break;
            case EXETERNAL_INT2 :
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                EXT_INT2_INTERRUPT_DISABLE();
#endif
                break;
            default :status = E_NOT_OK; ;
        }
    }
    return status;
}
/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *obj){
    Std_ReturnType status = E_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        switch(obj->number){
            case EXETERNAL_INT0 : 
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                EXT_INT0_INTERRUPT_FLAG_CLEAR();
#endif
                        break;
            case EXETERNAL_INT1 : 
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                EXT_INT1_INTERRUPT_FLAG_CLEAR();
#endif
                break;
            case EXETERNAL_INT2 : 
#if EXT_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                EXT_INT2_INTERRUPT_FLAG_CLEAR();
#endif
                break;
            default :status = E_NOT_OK; ;
        }
    }
    return status;
}

/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_enable(const interrupt_RBx_t *obj){
    Std_ReturnType status = E_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
#if EXT_INTERRUPT_ON_CHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EXT_RBx_INTERRUPT_ENABLE();
#endif
    }
    return status;
}

/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_disable(const interrupt_RBx_t *obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
#if EXT_INTERRUPT_ON_CHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        EXT_RBx_INTERRUPT_DISABLE();
#endif
        status = E_OK;
    }
    return status;
}
/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_priority(const interrupt_RBx_t *obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        if(obj->priority == LOW_PRIORITY_INTERRUPT){
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            EXT_RBx_INTERRUPT_LOW_PRIORITY();
        }
        else if(obj->priority == HIGH_PRIORITY_INTERRUPT){
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            EXT_RBx_INTERRUPT_HIGH_PRIORITY();
        }
        else{ /* Nothing */}
#else
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();
#endif
    }
    return status;
}

/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_pin(const interrupt_RBx_t *obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        status = gpio_pin_direction_intialize(&(obj->pin));
    }
    return status;
}

/**
 * 
 * @param obj
 * @return 
 */
static Std_ReturnType Interrupt_RBx_Call_Back(const interrupt_RBx_t *obj){
    Std_ReturnType status = E_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        switch(obj->pin.pin){
            case GPIO_PIN4 :
                RB4_Call_Back_fun_HIGH = obj->HIGH_call_back;
                RB4_Call_Back_fun_LOW = obj->LOW_call_back;
                break;
            case GPIO_PIN5 :
                RB5_Call_Back_fun_HIGH = obj->HIGH_call_back;
                RB5_Call_Back_fun_LOW = obj->LOW_call_back;
                break;
            case GPIO_PIN6 :
                RB6_Call_Back_fun_HIGH = obj->HIGH_call_back;
                RB6_Call_Back_fun_LOW = obj->LOW_call_back;
                break;
            case GPIO_PIN7 :
                RB7_Call_Back_fun_HIGH = obj->HIGH_call_back;
                RB7_Call_Back_fun_LOW = obj->LOW_call_back;
                break;
            default :status = E_NOT_OK; ;
        }
    }
    return status;
}

static Std_ReturnType (INT0_Set_Call_Back_fun)(void (* Call_Back_fun)(void)){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == Call_Back_fun){
        status = E_NOT_OK;
    }
    else{
        INT0_Call_Back_fun = Call_Back_fun;
        status = E_OK;
    }
    return status;
}

static Std_ReturnType (INT1_Set_Call_Back_fun)(void (* Call_Back_fun)(void)){
    Std_ReturnType status = E_OK;
    if(NULL == Call_Back_fun){
        status = E_NOT_OK;
    }
    else{
        INT1_Call_Back_fun = Call_Back_fun;
    }
    return status;
}

static Std_ReturnType (INT2_Set_Call_Back_fun)(void (* Call_Back_fun)(void)){
    Std_ReturnType status = E_OK;
    if(NULL == Call_Back_fun){
        status = E_NOT_OK;
    }
    else{
        INT2_Call_Back_fun = Call_Back_fun;
    }
    return status;
}

static Std_ReturnType INTx_Set_Call_Back_fun(const interrupt_INTx_t *obj){
    Std_ReturnType status = E_NOT_OK;
    if(NULL == obj){
        status = E_NOT_OK;
    }
    else{
        switch(obj->number){
            case EXETERNAL_INT0 :
                status = INT0_Set_Call_Back_fun(obj->call_back);
                break;
            case EXETERNAL_INT1 :
                status = INT1_Set_Call_Back_fun(obj->call_back);
                break;
            case EXETERNAL_INT2 :
                status = INT2_Set_Call_Back_fun(obj->call_back);
                break;
            default :status = E_NOT_OK; ;
        }
    }
    return status;
}

