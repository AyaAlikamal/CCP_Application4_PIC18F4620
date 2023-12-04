/* 
 * File:   ecu_7segment_cfg.h
 * Author: Aya Ali
 *
 * Created on October 27, 2023, 12:53 PM
 */

/*Section : Includes*/
#include "ecu_7segment.h"

Std_ReturnType segment_initialize (const Segment_t *segment){
    Std_ReturnType ret = E_OK;
    if(segment == NULL){
    ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_intialize(&(segment->segment_pins[SEGMENT_PIN_0]));
        ret = gpio_pin_intialize(&(segment->segment_pins[SEGMENT_PIN_1]));
        ret = gpio_pin_intialize(&(segment->segment_pins[SEGMENT_PIN_2]));
        ret = gpio_pin_intialize(&(segment->segment_pins[SEGMENT_PIN_3]));
    }
    return ret;
}

Std_ReturnType segment_write_data (const Segment_t *segment, uint_8 number){
    Std_ReturnType ret = E_OK;
    if((segment == NULL) & (number >9)){
    ret = E_NOT_OK;
    }
    else{
    ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN_0]), number & 0x01);
    ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN_1]), (number>>1) & 0x01);
    ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN_2]), (number>>2) & 0x01);
    ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN_3]), (number>>3) & 0x01); 
    }
    return ret;
}
