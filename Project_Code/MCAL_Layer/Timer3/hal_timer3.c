/* 
 * File:   hal_timer3.c
 * Author: AyaAli
 *
 * Created on December 1, 2023, 5:55 PM
 */
#include "hal_timer3.h"


static inline void Timer3_Mode_Select(const timer3_config_t *timer3);

#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
 void(*TMR3_Interrupt_Hundeler)(void) = NULL; 
#endif 
static uint_32 timer3_preload = ZERO_INIT;

Std_ReturnType Timer3_Init(const timer3_config_t *timer3){
Std_ReturnType ret = E_OK;
if(timer3 == NULL){
ret = E_NOT_OK;
}
else{
TIMER3_DISABLE_MODE();
TIMER3_PRESCALLER_SELECT(timer3->timer3_prescaller);
Timer3_Mode_Select(timer3);
TMR3H = (timer3->timer3_preload_value) >> 8;
TMR3L = (uint_8)(timer3->timer3_preload_value);
timer3_preload = timer3->timer3_preload_value;
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
  TIMER3_INTERRUPT_ENABLE();
  TIMER3_CLEAR_FLAG();
  TMR3_Interrupt_Hundeler = timer3->TMR3_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if(timer3->Timer_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      TIMER3_HIGH_PRIORITY_SET() ;
  
  }
  else if(timer3->Timer_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      TIMER3_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif
#endif
  TIMER3_ENABLE_MODE();
}
return ret;
}

Std_ReturnType Timer3_Deinit(const timer3_config_t *timer3){
Std_ReturnType ret = E_OK;
if(timer3 == NULL){
ret = E_NOT_OK;
}
else{
TIMER3_DISABLE_MODE();
#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
    TIMER3_INTERRUPT_DISABLE();
#endif 
}
return ret;

}

Std_ReturnType Timer3_Write_Value(const timer3_config_t *timer3, uint_16 value){
Std_ReturnType ret = E_OK;
if(timer3 == NULL){
ret = E_NOT_OK;
}
else{
  TMR3H = (value)>>8;
  TMR3L = (uint_8)(value);
}
return ret;

}
Std_ReturnType Timer3_Read_Value(const timer3_config_t *timer3, uint_16 *value){
Std_ReturnType ret = E_OK;
uint_8 l_tmr3l = ZERO_INIT , l_tmr3h = ZERO_INIT;
if((timer3 == NULL) || (value == NULL)){
ret = E_NOT_OK;
}
else{
l_tmr3l = TMR3L;
 l_tmr3h = TMR3H;
 *value = ((uint_16)(l_tmr3h << 8)+ l_tmr3l);
}
return ret;

}
static inline void Timer3_Mode_Select(const timer3_config_t *timer3){
    if(timer3->timer3_mode == TIMER3_TIMER_MODE  ){
    TIMER3_TIMER_MODE_ENABLE(); 
    }
    else if(timer3->timer3_mode == TIMER3_COUNTER_MODE  ){
    TIMER3_COUNTER_MODE_ENABLE(); 
    if(timer3->timer3_counter_mode == TIMER3_SYNC_COUNTER_MODE){
    TIMER3_SYNC_COUNTER_MODE_ENABLE(); 
    }
    else if(timer3->timer3_counter_mode == TIMER3_ASYNC_COUNTER_MODE){
    TIMER3_ASYNC_COUNTER_MODE_ENABLE(); 
    }
    else {}
    } 
    else{}
}

void TIMER3_ISR(void){
TIMER3_CLEAR_FLAG();
TMR3H = (timer3_preload)>>8;
TMR3L = (uint_8)(timer3_preload);
if(TMR3_Interrupt_Hundeler){
 TMR3_Interrupt_Hundeler();
}
}