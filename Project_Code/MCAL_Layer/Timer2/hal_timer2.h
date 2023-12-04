/* 
 * File:   hal_timer2.h
 * Author: AyaAli
 *
 * Created on December 1, 2023, 5:52 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H
/*Section : Includes*/
#include "../../../../Embeded-Compiler/pic/include/proc/pic18f4620.h"
#include  "../mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*Section : Macro Declaration*/
#define TIMER2_Module_ENABLE_CFG        1
#define TIMER2_Module_DISABLE_CFG       0

#define TIMER2_POSTSCALLER_DIV_BY_1     0
#define TIMER2_POSTSCALLER_DIV_BY_2     1
#define TIMER2_POSTSCALLER_DIV_BY_3     2
#define TIMER2_POSTSCALLER_DIV_BY_4     3
#define TIMER2_POSTSCALLER_DIV_BY_5     4
#define TIMER2_POSTSCALLER_DIV_BY_6     5
#define TIMER2_POSTSCALLER_DIV_BY_7     6
#define TIMER2_POSTSCALLER_DIV_BY_8     7
#define TIMER2_POSTSCALLER_DIV_BY_9     8
#define TIMER2_POSTSCALLER_DIV_BY_10    9
#define TIMER2_POSTSCALLER_DIV_BY_11    10
#define TIMER2_POSTSCALLER_DIV_BY_12    11
#define TIMER2_POSTSCALLER_DIV_BY_13    12
#define TIMER2_POSTSCALLER_DIV_BY_14    13
#define TIMER2_POSTSCALLER_DIV_BY_15    14
#define TIMER2_POSTSCALLER_DIV_BY_16    15

#define TIMER2_PRESCALLER_DIV_BY_1      0
#define TIMER2_PRESCALLER_DIV_BY_4      1
#define TIMER2_PRESCALLER_DIV_BY_16     2
/*Section : Macro Function Declaration*/
#define TIMER2_Module_ENABLE()  (T2CONbits.TMR2ON = 1)
#define TIMER2_Module_DISABLE() (T2CONbits.TMR2ON = 0)

#define TIMER2_POSTCALLER_SELECT(_POSTCALLER)   (T2CONbits.TOUTPS = _POSTCALLER)
#define TIMER2_PRESCALLER_SELECT(_PRESCALLER)   (T2CONbits.T2CKPS = _PRESCALLER)

/*Section : Data Type Declaration*/

typedef struct{
   #ifdef TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void(*TMR2_Interrupt_Hundeler)(void);
    Interrupt_Periority_cfg Timer_priority;
#endif      
    uint_8 timer2_preloaded_value;
    uint_8 timer2_prescaller_value:2;
    uint_8 timer2_post_scaller_value:4;
    uint_8 timer2_reserved:2;
}timer2_config_t; 

/*Section : Function Declaration*/
Std_ReturnType Timer2_Init(const timer2_config_t *timer2);
Std_ReturnType Timer2_Deinit(const timer2_config_t *timer2);
Std_ReturnType Timer2_Write_Value(const timer2_config_t *timer2, uint_8 value);
Std_ReturnType Timer2_Read_Value(const timer2_config_t *timer2, uint_8 *value);


#endif	/* HAL_TIMER2_H */

