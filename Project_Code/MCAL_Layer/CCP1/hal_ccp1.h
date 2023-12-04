/* 
 * File:   hal_ccp1.h
 * Author: Aya Ali
 *
 * Created on December 2, 2023, 9:18 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H
/*Section : Includes*/
#include "hal_ccp1_cfg.h"
#include "../../../../Embeded-Compiler/pic/include/proc/pic18f4620.h"
#include  "../mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"

/*Section : Macro Declaration*/
#define CCP_MODULE_DISABLE                  ((uint_8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE     ((uint_8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE      ((uint_8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE      ((uint_8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE     ((uint_8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW        ((uint_8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH       ((uint_8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH    ((uint_8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT   ((uint_8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT          ((uint_8)0x0B)
#define CCP_PWM_MODE                        ((uint_8)0x0C)

#define CCP_CAPTURE_NOT_READY               0x00
#define CCP_CAPTURE_READY                   0x01

#define CCP_COMPARE_NOT_READY               0x00
#define CCP_COMPARE_READY                   0x01

#define TIMER2_POSTSCALLER_DIV_BY_1     1
#define TIMER2_POSTSCALLER_DIV_BY_2     2
#define TIMER2_POSTSCALLER_DIV_BY_3     3
#define TIMER2_POSTSCALLER_DIV_BY_4     4
#define TIMER2_POSTSCALLER_DIV_BY_5     5
#define TIMER2_POSTSCALLER_DIV_BY_6     6
#define TIMER2_POSTSCALLER_DIV_BY_7     7
#define TIMER2_POSTSCALLER_DIV_BY_8     8
#define TIMER2_POSTSCALLER_DIV_BY_9     9
#define TIMER2_POSTSCALLER_DIV_BY_10    10
#define TIMER2_POSTSCALLER_DIV_BY_11    11
#define TIMER2_POSTSCALLER_DIV_BY_12    12
#define TIMER2_POSTSCALLER_DIV_BY_13    13
#define TIMER2_POSTSCALLER_DIV_BY_14    14
#define TIMER2_POSTSCALLER_DIV_BY_15    15
#define TIMER2_POSTSCALLER_DIV_BY_16    16

#define TIMER2_PRESCALLER_DIV_BY_1      1
#define TIMER2_PRESCALLER_DIV_BY_4      2
#define TIMER2_PRESCALLER_DIV_BY_16     3

/*Section : Macro Function Declaration*/
#define CCP1_SET_MODE(_CONFIG)  (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)  (CCP2CONbits.CCP2M = _CONFIG)
/*Section : Data Type Declaration*/
typedef enum{
    CCP1_Module = 0,
    CCP2_Module
}ccp_cfg_t;

typedef enum{
    CCP_CAPTURE_MODE_SELECTED = 0,
    CCP_COMPARE_MODE_SELECTED,
    CCP_PWM_MODE_SELECTED        
}ccp_mode_t;

typedef enum{

CCP1_CCP2_TIMER3 = 0,
CCP1_TIMER1_CCP2_TIMER3,
CCP1_CC2_TIMER1
}ccp_capeure_timer_t;

typedef union{
    struct{
        uint_8 ccp_low;
        uint_8 ccp_high;
    };
    struct{
        uint_16 ccp_16bit;
    };
}CCP_PERIOD_REG_T;

typedef struct{
ccp_cfg_t ccp_module_type;    
ccp_mode_t ccp_mode;
uint_8 ccp_mode_variant;
pin_config_t ccp_pin;
ccp_capeure_timer_t ccp_ct;
//#if(CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED) 
uint_8 timer2_prescaler_value:2;
uint_8 timer2_postscaler_value:2;
uint_32 PWM_Freq;
//#endif
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void(*CCP1_Interrupt_Hundeler)(void);
    Interrupt_Periority_cfg CCP1_priority;
#endif  
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void(*CCP2_Interrupt_Hundeler)(void);
    Interrupt_Periority_cfg CCP2_priority;
#endif      
}ccp_t;

/*Section : Function Declaration*/
//#if(CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED) 
Std_ReturnType CCP_CAPTURE_Init(const ccp_t *ccp_obj);
Std_ReturnType CCP_CAPTURE_Deinit(const ccp_t *ccp_obj);
Std_ReturnType CCP_IsCapturedData_Ready(uint_8 *captured_status);
Std_ReturnType CCP_Captured_Mode_Read_Value(uint_16 *captured_value);
//#endif 

//#if(CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED) 
Std_ReturnType CCP_COMPARE_Init(const ccp_t *ccp_obj);
Std_ReturnType CCP_COMPARE_Deinit(const ccp_t *ccp_obj);
Std_ReturnType CCP_IsCompare_Completed(uint_8 *compare_status);
Std_ReturnType CCP1_Compare_Mode_Set_Value(const ccp_t *ccp_obj ,uint_16 compare_value);
//#endif

//#if(CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED) 
Std_ReturnType CCP_PWM_Init(const ccp_t *ccp_obj);
Std_ReturnType CCP_PWM_Deinit(const ccp_t *ccp_obj);
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *ccp_obj, const uint_8 duty);
Std_ReturnType CCP_PWM_Start(const ccp_t *ccp_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_t *ccp_obj);
//#endif

#endif	/* HAL_CCP1_H */

