/* 
 * File:   mcal_external_interrupt.h
 * Author: Aya Ali
 *
 * Created on November 25, 2023, 3:06 PM
 */
#include"mcal_external_interrupt.h"

static void(*INT0_Interrupt_Handular)(void)= NULL;
static void(*INT1_Interrupt_Handular)(void)= NULL;
static void(*INT2_Interrupt_Handular)(void)= NULL;

static void(*RB4_Interrupt_Handular_HIGH)(void)= NULL;
static void(*RB4_Interrupt_Handular_LOW)(void)= NULL;
static void(*RB5_Interrupt_Handular_HIGH)(void)= NULL;
static void(*RB5_Interrupt_Handular_LOW)(void)= NULL;
static void(*RB6_Interrupt_Handular_HIGH)(void)= NULL;
static void(*RB6_Interrupt_Handular_LOW)(void)= NULL;
static void(*RB7_Interrupt_Handular_HIGH)(void)= NULL;
static void(*RB7_Interrupt_Handular_LOW)(void)= NULL;

static Std_ReturnType Interrupt_INT0_SetHandular(void(*Interrupt_Handular)(void));
static Std_ReturnType Interrupt_INT1_SetHandular(void(*Interrupt_Handular)(void));
static Std_ReturnType Interrupt_INT2_SetHandular(void(*Interrupt_Handular)(void));

static Std_ReturnType Interrupt_INTx_Enable(const Ex_Interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const Ex_Interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Periority_Init(const Ex_Interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const Ex_Interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const Ex_Interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const Ex_Interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_SetHandular(const Ex_Interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const Ex_Interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const Ex_Interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Periority_Init(const Ex_Interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const Ex_Interrupt_RBx_t *int_obj);

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Initialization(const Ex_Interrupt_INTx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
 ret = E_NOT_OK;
}
else{
    /*enable for external interrupt */
    ret = Interrupt_INTx_Disable(int_obj);
    /*clear the external interrupt flag*/
    ret = Interrupt_INTx_Clear_Flag(int_obj);
    /*configure for external interrupt edge*/
    ret = Interrupt_INTx_Edge_Init(int_obj);
    /*configure for external interrupt priority*/
    #ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    ret = Interrupt_INTx_Periority_Init(int_obj);
    #endif
    /*configure for external interrupt pin*/
    ret = Interrupt_INTx_Pin_Init(int_obj);   
    /*configure default interrupt callback*/
    ret = Interrupt_INTx_SetHandular(int_obj);
    /*disable for external interrupt */
    ret = Interrupt_INTx_Enable(int_obj); 
}
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInitialization(const Ex_Interrupt_INTx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
 ret = E_NOT_OK;
}
else{
  ret = Interrupt_INTx_Disable(int_obj);
}
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Initialization(const Ex_Interrupt_RBx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
ret  = E_NOT_OK;
}
else{
 EX_RBx_INTERRUPT_DISABLE();
 EX_RBx_INTERRUPT_FLAG_CLEAR();
 
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_PRIORITYLEVEL_ENABLE();
    if(int_obj->priority == Interrupt_Periority_LOW){
        INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
        EX_RBx_LOW_PRIORITY_SET();
    }
    else if(int_obj->priority == Interrupt_Periority_HIGH){
        INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE();
        EX_RBx_HIGH_PRIORITY_SET();
    }
    else{}    
#else 
       INTERRUPT_GLOBALEINTERRUPT_ENABLE();
       INTERRUPT_PERIPHERALINTERRUPT_ENABLE(); 
#endif  
       /*initialize the RBX pins as inputs*/
  ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin)); 
  switch(int_obj->mcu_pin.pin){
      case PIN4:
      RB4_Interrupt_Handular_HIGH = int_obj->Ext_Intterrupt_HIGH;
      RB4_Interrupt_Handular_LOW = int_obj->Ext_Intterrupt_LOW;
      break;    
      case PIN5:
      RB5_Interrupt_Handular_HIGH  = int_obj->Ext_Intterrupt_HIGH; 
      RB5_Interrupt_Handular_LOW = int_obj->Ext_Intterrupt_LOW;
      break; 
      case PIN6:
      RB6_Interrupt_Handular_HIGH  = int_obj->Ext_Intterrupt_HIGH; 
      RB6_Interrupt_Handular_LOW = int_obj->Ext_Intterrupt_LOW;   
      break; 
      case PIN7:
      RB7_Interrupt_Handular_HIGH  = int_obj->Ext_Intterrupt_HIGH; 
      RB7_Interrupt_Handular_LOW = int_obj->Ext_Intterrupt_LOW;  
      break;
      default:
      ret = E_NOT_OK;
      break;
  }     
 
 EX_RBx_INTERRUPT_ENABLE();
}
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_DeInitialization(const Ex_Interrupt_RBx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
 ret = E_NOT_OK;
}
else{
     EX_RBx_INTERRUPT_DISABLE();
 EX_RBx_INTERRUPT_FLAG_CLEAR();
}
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable(const Ex_Interrupt_INTx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
    ret = E_NOT_OK;
}
else{
  switch(int_obj->source){
        case EX_Interrupt_INT0: 
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE  
        INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE();
#else 
         INTERRUPT_GLOBALEINTERRUPT_ENABLE();
         INTERRUPT_PERIPHERALINTERRUPT_ENABLE(); 
#endif         
         EX_INT0_INTERRUPT_ENABLE();
         break;
        case EX_Interrupt_INT1: 
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE  
            INTERRUPT_PRIORITYLEVEL_ENABLE();
        if(int_obj->priority == Interrupt_Periority_LOW){
            INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
            }
            else if(int_obj->priority == Interrupt_Periority_HIGH){
                INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE();
            }
            else{}    
#else 
         INTERRUPT_GLOBALEINTERRUPT_ENABLE();
         INTERRUPT_PERIPHERALINTERRUPT_ENABLE(); 
#endif 
         EX_INT1_INTERRUPT_ENABLE();
         break;
        case EX_Interrupt_INT2:
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE  
            INTERRUPT_PRIORITYLEVEL_ENABLE() ;   
        if(int_obj->priority == Interrupt_Periority_LOW){
            INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
            }
            else if(int_obj->priority == Interrupt_Periority_HIGH){
                INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE();
            }
            else{}    
       
#else 
         INTERRUPT_GLOBALEINTERRUPT_ENABLE();
         INTERRUPT_PERIPHERALINTERRUPT_ENABLE(); 
#endif   
         EX_INT2_INTERRUPT_ENABLE();
         break;
        default: ret = E_NOT_OK;
    }
}
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable(const Ex_Interrupt_INTx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
 ret = E_NOT_OK;
}
else{
 switch(int_obj->source){
        case EX_Interrupt_INT0: 
         EX_INT0_INTERRUPT_DISABLE();
         break;
        case EX_Interrupt_INT1: 
         EX_INT1_INTERRUPT_DISABLE();
         break;
        case EX_Interrupt_INT2: 
         EX_INT2_INTERRUPT_DISABLE();
         break;
        default: ret = E_NOT_OK;
    }
}
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Periority_Init(const Ex_Interrupt_INTx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
 ret = E_NOT_OK;
}
else{
switch(int_obj->source){
        case EX_Interrupt_INT1: 
            if(int_obj->priority == Interrupt_Periority_LOW){
               EX_INT1_HIGH_PRIORITY_SET();
            }
            else if(int_obj->priority == Interrupt_Periority_HIGH){
               EX_INT1_LOW_PRIORITY_SET();
            }
            else{}
         break;
        case EX_Interrupt_INT2: 
        if(int_obj->priority == Interrupt_Periority_LOW){
               EX_INT2_HIGH_PRIORITY_SET();
            }
            else if(int_obj->priority == Interrupt_Periority_HIGH){
               EX_INT2_LOW_PRIORITY_SET();
            }
            else{}
         break;
        default: ret = E_NOT_OK;
    }
}
    return ret;
}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const Ex_Interrupt_INTx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
 ret = E_NOT_OK;
}
else{
switch(int_obj->source){
        case EX_Interrupt_INT0: 
             if(int_obj->edge == EX_Interrupt_Rising_Edge){
              EX_INT0_RISINGSET();
            }
            else if(int_obj->edge == EX_Interrupt_Falling_Edge){
               EX_INT0_FALLINGSET();
            }
            else{}
         break;
        case EX_Interrupt_INT1: 
            if(int_obj->edge == EX_Interrupt_Rising_Edge){
              EX_INT1_RISINGSET();
            }
            else if(int_obj->priority == EX_Interrupt_Falling_Edge){
               EX_INT1_FALLINGSET();
            }
            else{}
         break;
        case EX_Interrupt_INT2: 
        if(int_obj->edge == EX_Interrupt_Rising_Edge){
               EX_INT2_RISINGSET();
            }
            else if(int_obj->priority == EX_Interrupt_Falling_Edge){
              EX_INT2_FALLINGSET();
            }
            else{}
         break;
        default: ret = E_NOT_OK;
    }
}
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const Ex_Interrupt_INTx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
 ret = E_NOT_OK;
}
else{
    ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
}
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const Ex_Interrupt_INTx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
 ret = E_NOT_OK;
}
else{
  switch(int_obj->source){
        case EX_Interrupt_INT0: 
         EX_INT0_INTERRUPT_FLAG_CLEAR();
         break;
        case EX_Interrupt_INT1: 
         EX_INT1_INTERRUPT_FLAG_CLEAR();
         break;
        case EX_Interrupt_INT2: 
         EX_INT2_INTERRUPT_FLAG_CLEAR();
         break;
        default: ret = E_NOT_OK;
    }
}
    return ret;

}
/**
 * 
 * @param Interrupt_Handular
 * @return 
 */
static Std_ReturnType Interrupt_INT0_SetHandular(void(*Interrupt_Handular)(void)){
Std_ReturnType ret = E_OK;
if(Interrupt_Handular == NULL){
    ret = E_NOT_OK;
}
else{
INT0_Interrupt_Handular = Interrupt_Handular; 
}
return ret;
}
/**
 * 
 * @param Interrupt_Handular
 * @return 
 */
static Std_ReturnType Interrupt_INT1_SetHandular(void(*Interrupt_Handular)(void)){
Std_ReturnType ret = E_OK;
if(Interrupt_Handular == NULL){
 ret = E_NOT_OK;
}
else{
INT1_Interrupt_Handular = Interrupt_Handular; 
}
return ret;
}
/**
 * @param Interrupt_Handular
 * @return 
 */
static Std_ReturnType Interrupt_INT2_SetHandular(void(*Interrupt_Handular)(void)){
Std_ReturnType ret = E_OK;
if(Interrupt_Handular == NULL){
 ret = E_NOT_OK;
}
else{
    INT2_Interrupt_Handular = Interrupt_Handular; 
}
return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_SetHandular(const Ex_Interrupt_INTx_t *int_obj){
Std_ReturnType ret = E_OK;
if(int_obj == NULL){
 ret = E_NOT_OK;
}
else{
  switch(int_obj->source){
        case EX_Interrupt_INT0: 
         ret = Interrupt_INT0_SetHandular(int_obj->Ext_Intterrupt);
         break;
        case EX_Interrupt_INT1: 
        ret = Interrupt_INT1_SetHandular(int_obj->Ext_Intterrupt);
         break;
        case EX_Interrupt_INT2: 
         ret = Interrupt_INT2_SetHandular(int_obj->Ext_Intterrupt);
         break;
        default: ret = E_NOT_OK;
    }
}
    return ret;


}

void INT0_ISR(void){
    /*must clear the flag*/
    EX_INT0_INTERRUPT_FLAG_CLEAR();
    /*code*/
    /*call back handular function*/
    if(INT0_Interrupt_Handular){INT0_Interrupt_Handular();}
    else{}
}
void INT1_ISR(void){
    /*must clear the flag*/
    EX_INT1_INTERRUPT_FLAG_CLEAR();
    /*code*/
    /*call back handular function*/
    if(INT1_Interrupt_Handular){INT1_Interrupt_Handular();}
    else{}
}
void INT2_ISR(void){
    /*must clear the flag*/
    EX_INT2_INTERRUPT_FLAG_CLEAR();
    /*code*/
    /*call back handular function*/
    if(INT2_Interrupt_Handular){INT2_Interrupt_Handular();}
    else{}
}

void RB4_ISR(uint_8 source){
EX_RBx_INTERRUPT_FLAG_CLEAR();

if(source == 0){
if(RB4_Interrupt_Handular_LOW){RB4_Interrupt_Handular_LOW();}
    else{}
}
else if (source == 1){
if(RB4_Interrupt_Handular_HIGH){RB4_Interrupt_Handular_HIGH();}
    else{}
}
else{}
}
void RB5_ISR(uint_8 source){
 EX_RBx_INTERRUPT_FLAG_CLEAR();
if(source == 0){
if(RB5_Interrupt_Handular_LOW){RB5_Interrupt_Handular_LOW();}
    else{}
}
else if (source == 1){
if(RB5_Interrupt_Handular_HIGH){RB5_Interrupt_Handular_HIGH();}
    else{}
}
else{}  
}
void RB6_ISR(uint_8 source){
 EX_RBx_INTERRUPT_FLAG_CLEAR();
if(source == 0){
if(RB6_Interrupt_Handular_LOW){RB6_Interrupt_Handular_LOW();}
    else{}
}
else if (source == 1){
if(RB6_Interrupt_Handular_HIGH){RB6_Interrupt_Handular_HIGH();}
    else{}
}
else{}  
}
void RB7_ISR(uint_8 source){
 EX_RBx_INTERRUPT_FLAG_CLEAR();
if(source == 0){
if(RB7_Interrupt_Handular_LOW){RB7_Interrupt_Handular_LOW();}
    else{}
}
else if (source == 1){
if(RB7_Interrupt_Handular_HIGH){RB7_Interrupt_Handular_HIGH();}
    else{}
}
else{}  
}

