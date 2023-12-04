/* 
 * File:   hal_adc.h
 * Author: AyaAli
 *
 * Created on November 28, 2023, 10:29 AM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
/*Section : Includes*/
#include "hal_adc_cfg.h"
#include "../../MCAL_Layer/mcal_std_type.h"
#include "../GPIO/hal_gpio.h"
#include "../../pic/include/proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"

/*Section : Macro Declaration*/

#define ADC_AN0_ANALOG_FUNCTIONALITY   0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY   0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY   0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY   0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY   0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY   0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY   0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY   0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY   0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY   0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY  0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY  0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY  0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY   0x01
#define ADC_ALL_DIGITAL_FUNCTIONALITY  0x0F

#define ADC_RESLUT_RIGHT 0x01U
#define ADC_RESLUT_LEFT  0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLE  0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLE 0x00U
#define ADC_CONVERSION_COMPLETED      1
#define ADC_CONVERSION_NOT_COMPLETED  0


/*Section : Macro Function Declaration*/
/*Select the ADC conversion statues in progress or idle*/
#define ADC_CONVERSION_STATUES() (ADCON0bits.GO_nDONE)
/*Start ADC conversion*/
#define ADC_START_CONVERSION()   (ADCON0bits.GO_DONE = 1)
/*Enable the ADC conversion*/
#define ADC_CONVERSION_ENABLE()  (ADCON0bits.ADON = 1)
/*Disable the ADC conversion*/
#define ADC_CONVERSION_DISABLE() (ADCON0bits.ADON = 0)

#define ADC_ENABLE_VOLTAGE_REFRECE() do{ADCON1bits.VCFG1 = 1;\
                                        ADCON1bits.VCFG0 = 1;\
                                        }while(0)
#define ADC_DISABLE_VOLTAGE_REFRECE() do{ADCON1bits.VCFG1 = 0;\
                                        ADCON1bits.VCFG0 = 0;\
                                        }while(0)
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

#define ADC_RESULT_RIGHT_FORMT() (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMT()  (ADCON2bits.ADFM = 0)
/*Section : Data Type Declaration*/
typedef enum{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,        
    ADC_CHANNEL_AN12
}adc_channel_select_t;

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD ,
    ADC_4_TAD ,
    ADC_6_TAD ,
    ADC_8_TAD ,
    ADC_12_TAD ,
    ADC_16_TAD ,        
    ADC_20_TAD  
}adc_Acquisition_time_t;

typedef enum{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64        
}adc_conversion_clock_t;

typedef struct{
#ifdef ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE   
  void(*ADC_INTERRUPTHUNDLER)(void); 
  Interrupt_Periority_cfg priority;
#endif
  adc_Acquisition_time_t acquisition_time;
  adc_conversion_clock_t conversion_clock;
  adc_channel_select_t  defualt_channel;
  uint_8 voltage_reference : 1;
  uint_8 result_format: 1;
  uint_8 ADC_RESERVED: 6;
}adc_conf_t;

typedef uint_16 adc_result;

/*Section : Function Declaration*/
Std_ReturnType ADC_Init(const adc_conf_t *_adc_obj);
Std_ReturnType ADC_Deinit(const adc_conf_t *_adc_obj);
Std_ReturnType ADC_SelectChannel(const adc_conf_t *_adc_obj,adc_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc_obj);
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *_adc_obj, uint_8 *conversion_statues);
Std_ReturnType ADC_GetConversion_Result(const adc_conf_t *_adc_obj, adc_result *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const adc_conf_t *_adc_obj, adc_channel_select_t channel, adc_result *conversion_result );
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc_obj, adc_channel_select_t channel);
#endif	/* HAL_ADC_H */

