/* 
 * File:   hal_Time0.h
 * Author: DELL
 * Created on November 30, 2023, 4:11 PM
 */
#ifndef HAL_TIME0_H
#define	HAL_TIME0_H
/*Section : Includes*/
#include "../../../../Embeded-Compiler/pic/include/proc/pic18f4620.h"
#include  "../mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*Section : Macro Declaration*/

#define TIMER0_RAISING_EDG_COFG               0
#define TIMER0_FALLING_EDG_COFG               1
#define TIMER0_PRESCALLER_ENABLE_COUNTER_CFG  0
#define TIMER0_PRESCALLER_DISABLE_COUNTER_CFG 1
#define TIMER0_8BIT_MODE_CFG                  1
#define TIMER0_16BIT_MODE_CFG                 0
#define TIMER0_COUNTER_MODE_CFG               1
#define TIMER0_TIMER_MODE_CFG                 0


/*Section : Macro Function Declaration*/
#define TIMER0_ENABLE()   (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()  (T0CONbits.TMR0ON = 0)
#define TIMER0_SOURCE_RAISING_COUNTER_EDGE()  (T0CONbits.T0SE = 0)
#define TIMER0_SOURCE_FaLLING_COUNTER_EDGE()  (T0CONbits.T0SE = 1)
#define TIMER0_PRESCALLER_ENABLE()    (T0CONbits.PSA = 0)
#define TIMER0_PRESCALLER_DISABLE()   (T0CONbits.PSA = 1)
#define TIMER0_8BIT_MODE()            (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_MODE()           (T0CONbits.T08BIT = 0)
#define TIMER0_COUNTER_MODE()         (T0CONbits.T0CS = 1)
#define TIMER0_TIMER_MODE()           (T0CONbits.T0CS = 0)
/*Section : Data Type Declaration*/
typedef enum{
    TIMER0_PRESACLER_VALUE_2 = 0,
    TIMER0_PRESACLER_VALUE_4,
    TIMER0_PRESACLER_VALUE_8,
    TIMER0_PRESACLER_VALUE_16,
    TIMER0_PRESACLER_VALUE_32,
    TIMER0_PRESACLER_VALUE_64,
    TIMER0_PRESACLER_VALUE_128,
    TIMER0_PRESACLER_VALUE_256        
}timer0_prescaler_value_t;

typedef struct{
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void(*TMR0_Interrupt_Hundeler)(void);
    Interrupt_Periority_cfg Timer_priority;
#endif      
timer0_prescaler_value_t prescaler_value;
uint_8 timer0_conter_edge:1;
uint_8 timer0_mode:1;
uint_8 timer0_prescaler_enable:1;
uint_8 timer0_register_size:1;
uint_16 timer0_preload_value;
uint_8 timer0_reserved:4;
}timer0_config_t;


/*Section : Function Declaration*/
Std_ReturnType Timer0_Init(const timer0_config_t *timer1);
Std_ReturnType Timer0_Deinit(const timer0_config_t *timer1);
Std_ReturnType Timer0_Write_Value(const timer0_config_t *timer1, uint_16 value);
Std_ReturnType Timer0_Read_Value(const timer0_config_t *timer1, uint_16 *value);

#endif	/* HAL_TIME0_H */

