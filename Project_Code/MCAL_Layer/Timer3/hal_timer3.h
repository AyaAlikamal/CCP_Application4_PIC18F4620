/* 
 * File:   hal_timer3.h
 * Author: AyaAli
 *
 * Created on December 1, 2023, 5:55 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H
/*Section : Includes*/
#include "../../../../Embeded-Compiler/pic/include/proc/pic18f4620.h"
#include  "../mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*Section : Macro Declaration*/
#define TIMER3_COUNTER_MODE    1
#define TIMER3_TIMER_MODE      0

#define TIMER3_SYNC_COUNTER_MODE   0
#define TIMER3_ASYNC_COUNTER_MODE  1

#define TIMER3_PRESCALLER_DIV_BY_1  0
#define TIMER3_PRESCALLER_DIV_BY_2  1
#define TIMER3_PRESCALLER_DIV_BY_4  2
#define TIMER3_PRESCALLER_DIV_BY_8  3

#define TIMER3_RW_REG_8BIT_MODE     0
#define TIMER3_RW_REG_16BIT_MODE    1
/*Section : Macro Function Declaration*/
#define TIMER3_ENABLE_MODE()                    (T3CONbits.TMR3ON = 1)
#define TIMER3_DISABLE_MODE()                   (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE_ENABLE()              (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()            (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()      (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()       (T3CONbits.T3SYNC = 0)

#define TIMER3_PRESCALLER_SELECT(_PRESCALLER)   (T3CONbits.T3CKPS = _PRESCALLER)

#define TIMER1_REG_8BIT_MODE()                  (T3CONbits.RD16 = 0)
#define TIMER1_REG_16BIT_MODE()                 (T3CONbits.RD16 = 1)

/*Section : Data Type Declaration*/
typedef struct{
   #ifdef TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void(*TMR3_Interrupt_Hundeler)(void);
    Interrupt_Periority_cfg Timer_priority;
#endif      
uint_8 timer3_mode:1;
uint_8 timer3_counter_mode:1;
uint_8 timer3_register_wr_mode:1;
uint_16 timer3_preload_value;
uint_8 timer3_reserved:3; 
uint_8 timer3_prescaller:2;
}timer3_config_t; 
/*Section : Function Declaration*/
Std_ReturnType Timer3_Init(const timer3_config_t *timer3);
Std_ReturnType Timer3_Deinit(const timer3_config_t *timer3);
Std_ReturnType Timer3_Write_Value(const timer3_config_t *timer3, uint_16 value);
Std_ReturnType Timer3_Read_Value(const timer3_config_t *timer3, uint_16 *value);


#endif	/* HAL_TIMER3_H */

