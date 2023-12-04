/* 
 * File:   ecu_init.c
 * Author:  Aya Ali
 *
 * Created on November 1, 2023, 6:32 PM
 */
#include "ecu_init.h"


lcd_4_bit_t lcd_1 = {

.lcd_rs.port = PORTC_INDEX,
.lcd_rs.pin =  PIN0,
.lcd_rs.logic = LOW,
.lcd_rs.direction = Output,
.lcd_en.port = PORTC_INDEX,
.lcd_en.pin =  PIN1,
.lcd_en.logic = LOW,
.lcd_en.direction = Output,
.lcd_data[0].port = PORTC_INDEX,
.lcd_data[0].pin = PIN2,
.lcd_data[0].direction = Output,
.lcd_data[0].logic = LOW,
.lcd_data[1].port = PORTC_INDEX,
.lcd_data[1].pin = PIN3,
.lcd_data[1].direction = Output,
.lcd_data[1].logic = LOW,
.lcd_data[2].port = PORTC_INDEX,
.lcd_data[2].pin = PIN4,
.lcd_data[2].direction = Output,
.lcd_data[2].logic = LOW,
.lcd_data[3].port = PORTC_INDEX,
.lcd_data[3].pin = PIN5,
.lcd_data[3].direction = Output,
.lcd_data[3].logic = LOW,
};

lcd_8_bit_t lcd_2 = {

.lcd_rs.port = PORTC_INDEX,
.lcd_rs.pin =  PIN6,
.lcd_rs.logic = LOW,
.lcd_rs.direction = Output,
.lcd_en.port = PORTC_INDEX,
.lcd_en.pin =  PIN7,
.lcd_en.logic = LOW,
.lcd_en.direction = Output,
.lcd_data[0].port = PORTD_INDEX,
.lcd_data[0].pin = PIN0,
.lcd_data[0].direction = Output,
.lcd_data[0].logic = LOW,
.lcd_data[1].port = PORTD_INDEX,
.lcd_data[1].pin = PIN1,
.lcd_data[1].direction = Output,
.lcd_data[1].logic = LOW,
.lcd_data[2].port = PORTD_INDEX,
.lcd_data[2].pin = PIN2,
.lcd_data[2].direction = Output,
.lcd_data[2].logic = LOW,
.lcd_data[3].port = PORTD_INDEX,
.lcd_data[3].pin = PIN3,
.lcd_data[3].direction = Output,
.lcd_data[3].logic = LOW,

.lcd_data[4].port = PORTD_INDEX,
.lcd_data[4].pin = PIN4,
.lcd_data[4].direction = Output,
.lcd_data[4].logic = LOW,
.lcd_data[5].port = PORTD_INDEX,
.lcd_data[5].pin = PIN5,
.lcd_data[5].direction = Output,
.lcd_data[5].logic = LOW,
.lcd_data[6].port = PORTD_INDEX,
.lcd_data[6].pin = PIN6,
.lcd_data[6].direction = Output,
.lcd_data[6].logic = LOW,
.lcd_data[7].port = PORTD_INDEX,
.lcd_data[7].pin = PIN7,
.lcd_data[7].direction = Output,
.lcd_data[7].logic = LOW,
};


void ECU_Layer_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4_bit_initialize(&lcd_1);
//    ret = lcd_8_bit_initialize(&lcd_2);
}