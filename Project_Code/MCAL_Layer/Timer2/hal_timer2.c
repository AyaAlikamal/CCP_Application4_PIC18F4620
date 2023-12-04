/* 
 * File:   hal_timer2.c
 * Author: AyaAli
 *
 * Created on December 1, 2023, 5:52 PM
 */
#include "hal_timer2.h"

#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
 void(*TMR2_Interrupt_Hundeler)(void) = NULL; 
#endif 

static uint_8 timer2_preloaded = ZERO_INIT;
Std_ReturnType Timer2_Init(const timer2_config_t *timer2){
Std_ReturnType ret = E_OK;
if(timer2 == NULL){
    ret = E_NOT_OK;
}
else{
TIMER2_Module_DISABLE();
TIMER2_PRESCALLER_SELECT(timer2->timer2_prescaller_value);
TIMER2_POSTCALLER_SELECT(timer2->timer2_post_scaller_value);
TMR2 = timer2->timer2_preloaded_value;
timer2_preloaded = timer2->timer2_preloaded_value;
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
  TIMER2_INTERRUPT_ENABLE();
  TIMER2_CLEAR_FLAG();
  TMR2_Interrupt_Hundeler = timer2->TMR2_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if(timer2->Timer_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      TIMER2_HIGH_PRIORITY_SET() ;
  
  }
  else if(timer2->Timer_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      TIMER2_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif
#endif

TIMER2_Module_ENABLE();
}
return ret;
}
Std_ReturnType Timer2_Deinit(const timer2_config_t *timer2){
Std_ReturnType ret = E_OK;
if(timer2 == NULL){
    ret = E_NOT_OK;
}
else{
    TIMER2_Module_DISABLE();
#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
    TIMER2_INTERRUPT_DISABLE();
#endif 

}
return ret;

}
Std_ReturnType Timer2_Write_Value(const timer2_config_t *timer2, uint_8 value){

    Std_ReturnType ret = E_OK;
if(timer2 == NULL){
    ret = E_NOT_OK;
}
else{
    TMR2 = value;
}
return ret;

}
Std_ReturnType Timer2_Read_Value(const timer2_config_t *timer2, uint_8 *value){
Std_ReturnType ret = E_OK;
if((timer2 == NULL) || (value == NULL)){
    ret = E_NOT_OK;
}
else{
 *value = TMR2;
}
return ret;

}

void TIMER2_ISR(){
  TIMER2_CLEAR_FLAG();
  TMR2 = timer2_preloaded;
  if(TMR2_Interrupt_Hundeler){
      TMR2_Interrupt_Hundeler();
  }
}

