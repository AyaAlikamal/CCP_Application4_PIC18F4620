/* 
 * File:   hal_timer1.c
 * Author: AyaAli
 *
 * Created on December 1, 2023, 1:14 PM
 */
#include "hal_timer1.h"

static inline void Timer1_Mode_Select(const timer1_config_t *timer1);

#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
  void(*TMR1_Interrupt_Hundeler)(void) = NULL; 
#endif 
static uint_32 timer1_preload = ZERO_INIT;

Std_ReturnType Timer1_Init(const timer1_config_t *timer1){
Std_ReturnType ret = E_OK;
if(timer1 == NULL){
ret = E_NOT_OK;
}
else{
TIMER1_DISABLE();
Timer1_Mode_Select(timer1);
TIMER1_PRESCALLER_SELECT(timer1->timer1_prescaller);
TMR1H = (timer1->timer1_preload_value)>>8;
TMR1L = (uint_8)(timer1->timer1_preload_value);
timer1_preload = timer1->timer1_preload_value;
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
  TIMER1_INTERRUPT_ENABLE();
  TIMER1_CLEAR_FLAG();
  TMR1_Interrupt_Hundeler = timer1->TMR1_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if(timer1->Timer_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      TIMER1_HIGH_PRIORITY_SET() ;
  
  }
  else if(timer1->Timer_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      TIMER1_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif
#endif
  TIMER1_ENABLE();
}
return ret;
}


Std_ReturnType Timer1_Deinit(const timer1_config_t *timer1){
Std_ReturnType ret = E_OK;
if(timer1 == NULL){
    ret = E_NOT_OK;
}
else{
    TIMER1_DISABLE();    
#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
    TIMER1_INTERRUPT_DISABLE();
#endif 
}
return ret;

}


Std_ReturnType Timer1_Write_Value(const timer1_config_t *timer1, uint_16 value){
Std_ReturnType ret = E_OK;
if(timer1 == NULL){
ret = E_NOT_OK;
}
else{
  TMR1H = (value)>>8;
  TMR1L = (uint_8)(value);
}
return ret;

}
Std_ReturnType Timer1_Read_Value(const timer1_config_t *timer1, uint_16 *value){
Std_ReturnType ret = E_OK;
uint_8 l_tmr1l = ZERO_INIT , l_tmr1h = ZERO_INIT;
if((timer1 == NULL) ||(value == NULL)){
ret = E_NOT_OK;
}
else{
 l_tmr1l = TMR1L;
 l_tmr1h = TMR1H;
 *value = ((uint_16)(l_tmr1h<<8)+ l_tmr1l);
}
return ret;

}

static inline void Timer1_Mode_Select(const timer1_config_t *timer1){
    if(timer1->timer1_mode == TIMER1_COUNTER_MODE_CFG){
           TIMER1_COUNTER_MODE() ;
        if(timer1->timer1_counter_mode == TIMER1_SYNC_Counter_CFG){
           TIMER1_SYNC_Counter_CFG_Enable();
        }
        else if(timer1->timer1_counter_mode == TIMER1_ASYNC_Counter_CFG  ){
           TIMER1_ASYNC_Counter_CFG_Enable() ;
        }
        else{}
    }
    else if (timer1->timer1_mode == TIMER1_TIMER_MODE_CFG)
    {
           TIMER1_TIMER_MODE()  ;
    }
    else{}

}

void TIMER1_ISR(void){
TIMER1_CLEAR_FLAG();
TMR1H = (timer1_preload) >> 8;
TMR1L = (uint_8)(timer1_preload);
if(TMR1_Interrupt_Hundeler){
 TMR1_Interrupt_Hundeler();
}
}