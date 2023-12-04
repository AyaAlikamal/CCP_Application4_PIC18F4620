/* 
 * File:   hal_Time0.c
 * Author: DELL
 *
 * Created on November 30, 2023, 4:11 PM
 */
#include "hal_Time0.h"
static inline void Timer0_Prescaler_Config(const timer0_config_t *timer1);
static inline void Timer0_Mode_Select(const timer0_config_t *timer1);
static inline void Timer0_Register_Size(const timer0_config_t *timer1);

#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static  void(*TMR0_Interrupt_Hundeler)(void) = NULL; 
#endif 
static uint_16 timer0_preload = 0;

Std_ReturnType Timer0_Init(const timer0_config_t *timer1){
Std_ReturnType ret = E_OK;
if(timer1 == NULL){
ret = E_NOT_OK;
}
else{
  TIMER0_DISABLE();  
  Timer0_Prescaler_Config(timer1);
  Timer0_Mode_Select(timer1);
  Timer0_Register_Size(timer1);
  TMR0H = (timer1->timer0_preload_value)>>8;
  TMR0L = (uint_8)(timer1->timer0_preload_value);
  timer0_preload = timer1->timer0_preload_value;
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
  TIMER0_INTERRUPT_ENABLE();
  TIMER0_CLEAR_FLAG();
  TMR0_Interrupt_Hundeler = timer1->TMR0_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if(timer1->Timer_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      TIMER0_HIGH_PRIORITY_SET() ;
  
  }
  else if(timer1->Timer_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      TIMER0_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif
#endif
  TIMER0_ENABLE();
}
return ret;     
}
Std_ReturnType Timer0_Deinit(const timer0_config_t *timer1){
Std_ReturnType ret = E_OK;
if(timer1 == NULL){
ret = E_NOT_OK;
}
else{
   TIMER0_DISABLE();    
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
TIMER0_INTERRUPT_DISABLE();
#endif 
}
return ret;      
}


Std_ReturnType Timer0_Write_Value(const timer0_config_t *timer1, uint_16 value){
Std_ReturnType ret = E_OK;
if(timer1 == NULL){
ret = E_NOT_OK;
}
else{
  TMR0H = (value)>>8;
  TMR0L = (uint_8)(value);
}
return ret;  
 
}

Std_ReturnType Timer0_Read_Value(const timer0_config_t *timer1, uint_16 *value){
Std_ReturnType ret = E_OK;
uint_8 l_tmr0l = ZERO_INIT , l_tmr0h = ZERO_INIT;
if(timer1 == NULL){
ret = E_NOT_OK;
}
else{
 l_tmr0l = TMR0L;
 l_tmr0h = TMR0H;
 *value = ((uint_16)(l_tmr0h<<8)+ l_tmr0l);
}
return ret;  
}
void TIMER0_ISR(void){
TIMER0_CLEAR_FLAG();
TMR0H = (timer0_preload)>>8;
TMR0L = (uint_8)(timer0_preload);
if(TMR0_Interrupt_Hundeler){
TMR0_Interrupt_Hundeler();
}
}

static inline void Timer0_Prescaler_Config(const timer0_config_t *timer1){
    if(timer1->timer0_prescaler_enable == TIMER0_PRESCALLER_ENABLE_COUNTER_CFG){
        TIMER0_PRESCALLER_ENABLE();
        T0CONbits.T0PS = timer1->prescaler_value;
    }
    else if (timer1->timer0_prescaler_enable == TIMER0_PRESCALLER_DISABLE_COUNTER_CFG)
    {
    TIMER0_PRESCALLER_DISABLE();
    }
    else{}

}

static inline void Timer0_Mode_Select(const timer0_config_t *timer1){
    if(timer1->timer0_mode == TIMER0_COUNTER_MODE_CFG){
        TIMER0_COUNTER_MODE();
        if(timer1->timer0_conter_edge == TIMER0_RAISING_EDG_COFG){
        TIMER0_SOURCE_RAISING_COUNTER_EDGE();
        }
        else if(timer1->timer0_conter_edge == TIMER0_FALLING_EDG_COFG  ){
        TIMER0_SOURCE_FaLLING_COUNTER_EDGE();
        }
    }
    else if (timer1->timer0_mode == TIMER0_TIMER_MODE_CFG)
    {
    TIMER0_TIMER_MODE();
    }
    else{}

}

static inline void Timer0_Register_Size(const timer0_config_t *timer1){
    if(timer1->timer0_register_size == TIMER0_8BIT_MODE_CFG){
        TIMER0_8BIT_MODE();
    }
    else if(timer1->timer0_register_size == TIMER0_16BIT_MODE_CFG ){
        TIMER0_16BIT_MODE(); 
        }
        
    else{}

}