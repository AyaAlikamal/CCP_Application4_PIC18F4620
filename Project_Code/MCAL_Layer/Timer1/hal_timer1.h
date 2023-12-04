/* 
 * File:   hal_timer1.h
 * Author: AyaAli
 *
 * Created on December 1, 2023, 1:14 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H
/*Section : Includes*/
#include "../../../../Embeded-Compiler/pic/include/proc/pic18f4620.h"
#include  "../mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*Section : Macro Declaration*/
#define TIMER1_COUNTER_MODE_CFG                1
#define TIMER1_TIMER_MODE_CFG                  0
#define TIMER1_SYNC_Counter_CFG                0
#define TIMER1_ASYNC_Counter_CFG               1
#define TIMER1_OSC_ENABLE                      1
#define TIMER1_OSC_DISABLE                     0
#define TIMER1_REG_8BIT_MODE_CFG               0
#define TIMER1_REG_16BIT_MODE_CFG              1

/*Section : Macro Function Declaration*/
#define TIMER1_ENABLE()                         (T1CONbits.TMR1ON = 1)
#define TIMER1_DISABLE()                        (T1CONbits.TMR1ON = 0)
#define TIMER1_COUNTER_MODE()                   (T1CONbits.TMR1CS = 1)
#define TIMER1_TIMER_MODE()                     (T1CONbits.TMR1CS = 0)
#define TIMER1_ASYNC_Counter_CFG_Enable()       (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_Counter_CFG_Enable()        (T1CONbits.T1SYNC = 0)
#define TIMER1_OSC_DISABLE_CFG()                (T1CONbits.T1OSCEN =0)
#define TIMER1_OSC_ENABLE_CFG()                 (T1CONbits.T1OSCEN =1)
#define TIMER1_PRESCALLER_SELECT(_PRESCALLER)   (T1CONbits.T1CKPS = _PRESCALLER)
#define TIMER1_SYSTEM_CLK_STATUS()              (T1CONbits.T1RUN = 0)
#define TIMER1_REG_8BIT_MODE()                  (T1CONbits.RD16 = 0)
#define TIMER1_REG_16BIT_MODE()                 (T1CONbits.RD16 = 1)
/*Section : Data Type Declaration*/

typedef enum{
TIMER1_PRESACLER_VALUE_1 = 0,
TIMER1_PRESACLER_VALUE_2,
TIMER1_PRESACLER_VALUE_4,
TIMER1_PRESACLER_VALUE_8        
}timer1_prescaler_value_t;

typedef struct{
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void(*TMR1_Interrupt_Hundeler)(void);
    Interrupt_Periority_cfg Timer_priority;
#endif      
uint_8 timer1_mode:1;
uint_8 timer1_counter_mode:1;
uint_8 timer1_osc_mode:1;
uint_8 timer1_register_size:1;
uint_16 timer1_preload_value;
uint_8 timer1_reserved:2; 
timer1_prescaler_value_t timer1_prescaller;
}timer1_config_t; 


/*Section : Function Declaration*/
Std_ReturnType Timer1_Init(const timer1_config_t *timer1);
Std_ReturnType Timer1_Deinit(const timer1_config_t *timer1);
Std_ReturnType Timer1_Write_Value(const timer1_config_t *timer1, uint_16 value);
Std_ReturnType Timer1_Read_Value(const timer1_config_t *timer1, uint_16 *value);

#endif	/* HAL_TIMER1_H */

