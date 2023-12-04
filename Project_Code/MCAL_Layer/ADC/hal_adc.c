/* 
 * File:   hal_adc.c
 * Author: AyaAli
 * Created on November 28, 2023, 10:29 AM
 */
#include "hal_adc.h"

#ifdef ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
static void(*ADC_Interrupt_Handular)(void)= NULL;
#endif
static inline void adc_input_port_configure(adc_channel_select_t channel);
static inline void select_result_format(const adc_conf_t *_adc_obj);
static inline void select_voltage_reference(const adc_conf_t *_adc_obj);
/**
 * 
 * @param _adc_obj
 * @return 
 */
Std_ReturnType ADC_Init(const adc_conf_t *_adc_obj){
Std_ReturnType ret = E_OK;
if(_adc_obj == NULL){
ret = E_NOT_OK;
}
else{
/*Disable the ADC*/
ADC_CONVERSION_DISABLE();
/*Configure the acquisition time*/
ADCON2bits.ACQT =_adc_obj->acquisition_time;
/*configure the conversion clock*/
ADCON2bits.ADCS = _adc_obj->conversion_clock;
/*Select the channel*/
ADCON0bits.CHS = _adc_obj->defualt_channel;
/*configure the pin */
adc_input_port_configure(_adc_obj->defualt_channel);
/*configure interrupt*/
#ifdef ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE  
  INTERRUPT_GLOBALEINTERRUPT_ENABLE();
  INTERRUPT_PERIPHERALINTERRUPT_ENABLE();
  ADC_INTERRUPT_ENABLE();
  ADC_CLEAR_FLAG();
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
  if(_adc_obj->priority == Interrupt_Periority_HIGH){
      INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE() ;
  ADC_HIGH_PRIORITY_SET();
  }
  else if(_adc_obj->priority == Interrupt_Periority_LOW){
      INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE();
  ADC_LOW_PRIORITY_SET();
  }
  else{}
 #endif 
  ADC_Interrupt_Handular = _adc_obj->ADC_INTERRUPTHUNDLER;
#endif
/*configure result formate*/
select_result_format(_adc_obj->result_format);
/*configure voltage formate*/
select_voltage_reference(_adc_obj->voltage_reference);
/*Enable the ADC*/
ADC_CONVERSION_ENABLE();
}
return ret;
}
/**
 * 
 * @param _adc_obj
 * @return 
 */
Std_ReturnType ADC_Deinit(const adc_conf_t *_adc_obj){
Std_ReturnType ret = E_OK;
if(_adc_obj == NULL){
ret = E_NOT_OK;
}
else{
/*Disable the ADC*/
ADC_CONVERSION_DISABLE();
ADC_INTERRUPT_DISABLE();
}
return ret;
}
/**
 * 
 * @param _adc_obj
 * @param channel
 * @return 
 */
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc_obj, adc_channel_select_t channel){
Std_ReturnType ret = E_OK;
if(_adc_obj == NULL){
ret = E_NOT_OK;
}
else{
    /*configure the channel you want*/
    ADCON0bits.CHS = channel;
    adc_input_port_configure(channel);
    
}
return ret;
}
/**
 * 
 * @param _adc_obj
 * @return 
 */
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc_obj){
Std_ReturnType ret = E_OK;
if(_adc_obj == NULL){
ret = E_NOT_OK;
}
else{
ADC_START_CONVERSION();
    
}
return ret;
}
/**
 * 
 * @param _adc_obj
 * @param conversion_statues
 * @return 
 */
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc_obj, uint_8 *conversion_statues){
Std_ReturnType ret = E_OK;
if((_adc_obj == NULL)|| (conversion_statues == NULL)){
ret = E_NOT_OK;
}
else{
    *conversion_statues =(uint_8)(!ADCON0bits.GO_nDONE);
}
return ret;
}
/**
 * 
 * @param _adc_obj
 * @param conversion_result
 * @return 
 */
Std_ReturnType ADC_GetConversion_Result(const adc_conf_t *_adc_obj, adc_result *conversion_result){
Std_ReturnType ret = E_OK;
if((_adc_obj == NULL)|| (conversion_result == NULL)){
ret = E_NOT_OK;
}
else{
   if(_adc_obj->result_format == ADC_RESLUT_RIGHT){
       *conversion_result = (adc_result)((ADRESH << 8) + ADRESL);
    }
    else if(_adc_obj->result_format == ADC_RESLUT_LEFT){
     *conversion_result = (adc_result)(((ADRESH << 8) + ADRESL) >> 6);
    }
    else{
     *conversion_result = (adc_result)((ADRESH << 8) + ADRESL);
    }
}
return ret;
}
/**
 * 
 * @param _adc_obj
 * @param channel
 * @param conversion_result
 * @return 
 */
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc_obj, adc_channel_select_t channel, adc_result *conversion_result ){
    Std_ReturnType ret = E_OK;
    uint_8 l_Conversion_status = ZERO_INIT;
if((_adc_obj == NULL)|| (conversion_result == NULL)){
ret = E_NOT_OK;
}
else{
    /*Select channel*/
   ret = ADC_SelectChannel(_adc_obj,channel);
   /*Start conversion*/
   ret = ADC_StartConversion(_adc_obj);
   /*check the conversion is done or no*/
   ret = ADC_IsConversionDone(_adc_obj,& l_Conversion_status);
   /*check conversion completed*/
   while(ADCON0bits.GO_nDONE);   //blocking
   ret = ADC_GetConversion_Result(_adc_obj,conversion_result);
}
return ret;
}
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc_obj, adc_channel_select_t channel){
 Std_ReturnType ret = E_OK;

if((_adc_obj == NULL)){
ret = E_NOT_OK;
}
else{
    /*Select channel*/
   ret = ADC_SelectChannel(_adc_obj,channel);
   /*Start conversion*/
   ret = ADC_StartConversion(_adc_obj);
}
return ret;

}
static inline void adc_input_port_configure(adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0:
            SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1:
            SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2:
            SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;    
        case ADC_CHANNEL_AN3:
            SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4:
            SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5:
            SET_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6:
            SET_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7:
            SET_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8:
            SET_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9:
            SET_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10:
            SET_BIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11:
            SET_BIT(TRISB, _TRISB_RB4_POSN);
            break;    
        case ADC_CHANNEL_AN12:
            SET_BIT(TRISB, _TRISB_RB0_POSN);
            break;   
        default:   ;
    }
}

static inline void select_result_format(const adc_conf_t *_adc_obj){
    if(_adc_obj->result_format == ADC_RESLUT_RIGHT){
    ADC_RESULT_RIGHT_FORMT();
    }
    else if(_adc_obj->result_format == ADC_RESLUT_LEFT){
    ADC_RESULT_LEFT_FORMT();
    }
    else{
    ADC_RESULT_RIGHT_FORMT();
    }
}

static inline void select_voltage_reference(const adc_conf_t *_adc_obj){
    if(_adc_obj->voltage_reference== ADC_VOLTAGE_REFERENCE_ENABLE){
    ADC_ENABLE_VOLTAGE_REFRECE();
    }
    else if(_adc_obj->voltage_reference == ADC_VOLTAGE_REFERENCE_DISABLE){
    ADC_DISABLE_VOLTAGE_REFRECE();
    }
    else{
    ADC_ENABLE_VOLTAGE_REFRECE();
    }
}

void ADC_ISR(void){
ADC_CLEAR_FLAG();
if(ADC_Interrupt_Handular){
ADC_Interrupt_Handular();
}
}