/* 
 * File:   hal_ccp1.c
 * Author: Aya Ali
 *
 * Created on December 2, 2023, 9:18 PM
 */

#include "hal_ccp1.h"

#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static void (*CCP1_Interrupt_Hundeler)(void);
#endif
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
static void (*CCP2_Interrupt_Hundeler)(void);
#endif
static void ccp_capture_mode_timer_select(const ccp_t *ccp_obj);
static Std_ReturnType Set_Compare_Mode(const ccp_t *ccp_obj);
static Std_ReturnType Set_Capture_Mode(const ccp_t *ccp_obj);
//#if(CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELECTED) 
Std_ReturnType CCP_CAPTURE_Init(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;
if(ccp_obj == NULL){
ret = E_NOT_OK;
}
else{
     CCP1_SET_MODE(CCP_MODULE_DISABLE);
    if(ccp_obj->ccp_mode == CCP_CAPTURE_MODE_SELECTED){
      ret = Set_Capture_Mode(ccp_obj);
      ret = gpio_pin_intialize(&(ccp_obj->ccp_pin));
      
if(ccp_obj->ccp_module_type == CCP1_Module){
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
CCP1_INTERRUPT_ENABLE();
CCP1_CLEAR_FLAG();
CCP1_Interrupt_Hundeler = ccp_obj->CCP1_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if( ccp_obj->CCP1_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      CCP1_HIGH_PRIORITY_SET() ;
  
  }
  else if(ccp_obj->CCP1_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      CCP1_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif

#endif  
            }
 else if(ccp_obj->ccp_module_type == CCP2_Module){
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
CCP2_INTERRUPT_ENABLE();
CCP2_CLEAR_FLAG();
CCP2_Interrupt_Hundeler = ccp_obj->CCP2_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if( ccp_obj->CCP1_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      CCP1_HIGH_PRIORITY_SET() ;
  
  }
  else if(ccp_obj->CCP1_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      CCP1_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif

#endif  
            }            
    }
}
    return ret;
}


Std_ReturnType CCP1_CAPTURE_Deinit(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;
if(ccp_obj == NULL){
ret = E_NOT_OK;
}
else{
 if(ccp_obj->ccp_module_type == CCP1_Module){   
CCP1_SET_MODE(CCP_MODULE_DISABLE);
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
   CCP1_INTERRUPT_DISABLE();
#endif 
 }
  else if(ccp_obj->ccp_module_type == CCP2_Module){
  CCP2_SET_MODE(CCP_MODULE_DISABLE);
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
   CCP2_INTERRUPT_DISABLE();
#endif 
  } 

}
return ret;
}

Std_ReturnType CCP1_IsCapturedData_Ready(uint_8 *captured_status){
Std_ReturnType ret = E_OK;
if(captured_status == NULL){
ret = E_NOT_OK;
}
else{
    if(PIR1bits.CCP1IF == CCP_CAPTURE_READY){
    *captured_status = CCP_CAPTURE_READY;
    CCP1_CLEAR_FLAG();
    CCP2_CLEAR_FLAG();
    }
    else{
     *captured_status = CCP_CAPTURE_NOT_READY;
    }

}
return ret;
}
Std_ReturnType CCP_Captured_Mode_Read_Value(uint_16 *captured_value){
Std_ReturnType ret = E_OK;
CCP_PERIOD_REG_T capure_temp_value = {.ccp_low = 0,.ccp_high = 0 };
if(captured_value == NULL){
ret = E_NOT_OK;
}
else{
capure_temp_value.ccp_low = CCPR1L;
capure_temp_value.ccp_high = CCPR1H;
*captured_value = capure_temp_value.ccp_16bit;
}
 return ret;
}
//#endif 

//#if(CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELECTED)  
Std_ReturnType CCP_COMPARE_Init(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;
if(ccp_obj == NULL){
ret = E_NOT_OK;
}
else{
      CCP1_SET_MODE(CCP_MODULE_DISABLE);
     if(ccp_obj->ccp_mode == CCP_COMPARE_MODE_SELECTED)
    {  
         ret = Set_Compare_Mode(ccp_obj);
         ret = gpio_pin_intialize(&(ccp_obj->ccp_pin)); 
     }
if(ccp_obj->ccp_module_type == CCP1_Module){
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
CCP1_INTERRUPT_ENABLE();
CCP1_CLEAR_FLAG();
CCP1_Interrupt_Hundeler = ccp_obj->CCP1_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if( ccp_obj->CCP1_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      CCP1_HIGH_PRIORITY_SET() ;
  
  }
  else if(ccp_obj->CCP1_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      CCP1_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif

#endif  
            }
 else if(ccp_obj->ccp_module_type == CCP2_Module){
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
CCP2_INTERRUPT_ENABLE();
CCP2_CLEAR_FLAG();
CCP2_Interrupt_Hundeler = ccp_obj->CCP2_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if( ccp_obj->CCP1_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      CCP1_HIGH_PRIORITY_SET() ;
  
  }
  else if(ccp_obj->CCP1_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      CCP1_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif

#endif  
     }
     }
return ret;
}

Std_ReturnType CCP1_COMPARE_Deinit(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;
if(ccp_obj == NULL){
ret = E_NOT_OK;
}
else{
    if(ccp_obj->ccp_module_type == CCP1_Module){
CCP1_SET_MODE(CCP_MODULE_DISABLE);
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
   CCP1_INTERRUPT_DISABLE();
#endif
 }
  else if(ccp_obj->ccp_module_type == CCP2_Module){
  
  CCP2_SET_MODE(CCP_MODULE_DISABLE);
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
   CCP2_INTERRUPT_DISABLE();
#endif
  }  
}
return ret;
}

Std_ReturnType CCP1_IsCompare_Completed(uint_8 *compare_status){
Std_ReturnType ret = E_OK;
if(compare_status == NULL){
ret = E_NOT_OK;
}
else{
    if(PIR1bits.CCP1IF == CCP_COMPARE_READY){
    *compare_status = CCP_COMPARE_READY;
    CCP1_CLEAR_FLAG();
    }
    else{
        *compare_status = CCP_COMPARE_NOT_READY;
    }


}
return ret;
}

Std_ReturnType CCP1_Compare_Mode_Set_Value(const ccp_t *ccp_obj , uint_16 compare_value){
Std_ReturnType ret = E_OK;
if(ccp_obj == NULL){
    ret = E_NOT_OK;
}
else{
CCP_PERIOD_REG_T compare_temp_value = {.ccp_low = 0,.ccp_high = 0 };
compare_temp_value.ccp_16bit = compare_value;

 if(ccp_obj->ccp_module_type == CCP1_Module){
            CCPR1L = compare_temp_value.ccp_low;
            CCPR1H = compare_temp_value.ccp_high;
    }
 else if(ccp_obj->ccp_module_type == CCP2_Module){
            CCPR2L = compare_temp_value.ccp_low;
            CCPR2H = compare_temp_value.ccp_high;    
     
            }
  else{}

}
return ret;
}
//#endif


//#if(CCP1_CFG_SELECTED_MODE == CCP1_CFG_PWM_MODE_SELECTED) 
Std_ReturnType CCP_PWM_Init(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;
if(ccp_obj == NULL){
ret = E_NOT_OK;
}
else{
    CCP1_SET_MODE(CCP_MODULE_DISABLE);        
if(ccp_obj->ccp_mode == CCP_PWM_MODE_SELECTED){
     if(ccp_obj->ccp_module_type == CCP1_Module){
            if(ccp_obj->ccp_mode_variant == CCP_PWM_MODE){
                CCP1_SET_MODE(CCP_PWM_MODE);
            } 
            else{}
            }
 else if(ccp_obj->ccp_module_type == CCP2_Module){
     if(ccp_obj->ccp_mode_variant == CCP_PWM_MODE){
               CCP2_SET_MODE(CCP_PWM_MODE);
            } 
            else{}
            }
  else{}
}
 else{}       
PR2 = (uint_8)((_XTAL_FREQ/(ccp_obj->PWM_Freq * 4.0 * ccp_obj->timer2_prescaler_value * ccp_obj->timer2_postscaler_value))-1);

         ret = gpio_pin_intialize(&(ccp_obj->ccp_pin)); 
 if(ccp_obj->ccp_module_type == CCP1_Module){         
#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
CCP1_INTERRUPT_ENABLE();
CCP1_CLEAR_FLAG();
CCP1_Interrupt_Hundeler = ccp_obj->CCP1_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if( ccp_obj->CCP1_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      CCP1_HIGH_PRIORITY_SET() ;
  
  }
  else if(ccp_obj->CCP1_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      CCP1_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif

#endif 
 }
 if(ccp_obj->ccp_module_type == CCP2_Module){         
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
CCP2_INTERRUPT_ENABLE();
CCP2_CLEAR_FLAG();
CCP2_Interrupt_Hundeler = ccp_obj->CCP2_Interrupt_Hundeler;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  INTERRUPT_PRIORITYLEVEL_ENABLE();
  if( ccp_obj->CCP1_priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
      CCP2_HIGH_PRIORITY_SET() ;
  
  }
  else if(ccp_obj->CCP1_priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
      CCP2_LOW_PRIORITY_SET();
  } 
#else   
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
#endif

#endif 
 }        

}
return ret;
}

Std_ReturnType CCP_PWM_Deinit(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;
if(ccp_obj == NULL){
ret = E_NOT_OK;
}
else{
     if(ccp_obj->ccp_module_type == CCP1_Module){
    CCP1_SET_MODE(CCP_MODULE_DISABLE);       
    #ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
       CCP1_INTERRUPT_DISABLE();
    #endif      
            }
 else if(ccp_obj->ccp_module_type == CCP2_Module){
    CCP2_SET_MODE(CCP_MODULE_DISABLE);
#ifdef CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
   CCP2_INTERRUPT_DISABLE();
#endif  
 
 }

}
return ret;
}

Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *ccp_obj, const uint_8 duty){
Std_ReturnType ret = E_OK;
uint_16 l_duty_temp = 0;
if(ccp_obj == NULL){
ret = E_NOT_OK;
}
else{
l_duty_temp = (uint_16)(((PR2 + 1) *(duty / 100.0)) * 4);
if(ccp_obj->ccp_module_type == CCP1_Module){
CCP1CONbits.DC1B = (uint_8)(l_duty_temp & 0x0003);
CCPR1L = (uint_8)(l_duty_temp >> 2);
}
else if(ccp_obj->ccp_module_type == CCP2_Module){
CCP2CONbits.DC2B = (uint_8)(l_duty_temp & 0x0003);
CCPR2L = (uint_8)(l_duty_temp >> 2);
}
else{}
}
 return ret;
}

Std_ReturnType CCP_PWM_Start(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;

if(ccp_obj == NULL){
ret = E_NOT_OK;
}
else{
if(ccp_obj->ccp_module_type == CCP1_Module){
CCP1CONbits.CCP1M = CCP_PWM_MODE;
}
else if(ccp_obj->ccp_module_type == CCP2_Module){
CCP2CONbits.CCP2M = CCP_PWM_MODE;
}
else{}
}
return ret;

}

Std_ReturnType CCP_PWM_Stop(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;
uint_16 l_duty_temp = 0;
if(ccp_obj == NULL){
ret = E_NOT_OK;
}
else{

if(ccp_obj->ccp_module_type == CCP1_Module){
CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
}
else if(ccp_obj->ccp_module_type == CCP2_Module){
CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
}
else{}
}
 return ret;

}

void CCP1_ISR(void){
CCP1_CLEAR_FLAG();
if(CCP1_Interrupt_Hundeler){
CCP1_Interrupt_Hundeler();
}
}

void CCP2_ISR(void){
CCP2_CLEAR_FLAG();
if(CCP2_Interrupt_Hundeler){
CCP2_Interrupt_Hundeler();
}
}
static void ccp_capture_mode_timer_select(const ccp_t *ccp_obj){
    if(ccp_obj->ccp_ct== CCP1_CCP2_TIMER3){
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    else if(ccp_obj->ccp_ct == CCP1_TIMER1_CCP2_TIMER3){
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    
    }
    else if(ccp_obj->ccp_ct == CCP1_CC2_TIMER1){
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    
    }  

}

//#endif
static Std_ReturnType Set_Compare_Mode(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;
if(ccp_obj->ccp_module_type == CCP1_Module){
switch(ccp_obj->ccp_mode_variant){
           case CCP_COMPARE_MODE_SET_PIN_LOW: 
           CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
           break;
           case CCP_COMPARE_MODE_SET_PIN_HIGH: 
           CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
           break;
           case CCP_COMPARE_MODE_TOGGLE_ON_MATCH: 
           CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
           break;
           case CCP_COMPARE_MODE_GEN_SW_INTERRUPT: 
           CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
           break;
           case CCP_COMPARE_MODE_GEN_EVENT: 
           CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
           break;
           default: ret = E_NOT_OK;
}}
else if(ccp_obj->ccp_module_type == CCP2_Module){
switch(ccp_obj->ccp_mode_variant){
           case CCP_COMPARE_MODE_SET_PIN_LOW: 
           CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
           break;
           case CCP_COMPARE_MODE_SET_PIN_HIGH: 
           CCP2_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
           break;
           case CCP_COMPARE_MODE_TOGGLE_ON_MATCH: 
           CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE_ON_MATCH);
           break;
           case CCP_COMPARE_MODE_GEN_SW_INTERRUPT: 
           CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
           break;
           case CCP_COMPARE_MODE_GEN_EVENT: 
           CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);
           break;
           default: ret = E_NOT_OK;
}}
else{}
ccp_capture_mode_timer_select(ccp_obj);
return ret;
}
static Std_ReturnType Set_Capture_Mode(const ccp_t *ccp_obj){
Std_ReturnType ret = E_OK;
if(ccp_obj->ccp_module_type == CCP1_Module){
 switch(ccp_obj->ccp_mode_variant){
           case CCP_CAPTURE_MODE_1_FALLING_EDGE: 
           CCP1_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
           break;
           case CCP_CAPTURE_MODE_1_RISING_EDGE: 
           CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
           break;
           case CCP_CAPTURE_MODE_4_RISING_EDGE: 
           CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
           break;
           case CCP_CAPTURE_MODE_16_RISING_EDGE: 
           CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
           break;
          default: ret = E_NOT_OK;
      }  
    }
else if(ccp_obj->ccp_module_type == CCP2_Module){
switch(ccp_obj->ccp_mode_variant){
           case CCP_CAPTURE_MODE_1_FALLING_EDGE: 
           CCP2_SET_MODE(CCP_CAPTURE_MODE_1_FALLING_EDGE);
           break;
           case CCP_CAPTURE_MODE_1_RISING_EDGE: 
           CCP2_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);
           break;
           case CCP_CAPTURE_MODE_4_RISING_EDGE: 
           CCP2_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);
           break;
           case CCP_CAPTURE_MODE_16_RISING_EDGE: 
           CCP2_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);
           break;
          default: ret = E_NOT_OK;
      }  


}
else{}
  ccp_capture_mode_timer_select(ccp_obj);
return ret;

}