
/* 
 * File:   ecu_kypad_cfg.h
 * Author: Aya Ali
 *
 * Created on November 1, 2023, 4:57 PM
 */
#include "ecu_keypad.h"

static const uint_8 *keypad_btn_values[KEYPAD_ROWS_NUMBER][KEYPAD_COLUMNS_NUMBER]={ 
                                                                      {'7','8','9','/'},
                                                                      {'4','5','6','*'},
                                                                      {'1','2','3','+'},
                                                                      {'#','0','=','-'}
                                                                      };

/**
 * @brief: initialize the kepad pins 
 * @param kepad_obj
 * @return ret = E_OK: if the function works as programmed
 *               E_NOT_OK: if the parameter is null
 */
Std_ReturnType keypade_initialize(const keypad_t *kepad_obj){
Std_ReturnType ret = E_OK;
uint_8 row_index = ZERO_INIT;
uint_8 column_index = ZERO_INIT;
if(kepad_obj == NULL){
    ret = E_NOT_OK;
}
else{
    for (row_index = ZERO_INIT ;  row_index <= KEYPAD_ROWS_NUMBER; row_index++){
        ret = gpio_pin_intialize(&(kepad_obj->keypad_rows[row_index]));
    }
    for (column_index = ZERO_INIT ;  column_index <= KEYPAD_ROWS_NUMBER; column_index++){
        ret = gpio_pin_direction_intialize(&(kepad_obj->keypad_columns[column_index]));
    }
}
return ret;
}

/**
 * @brief: initialize the kepad pins 
 * @param kepad_obj, value of the button pressed
 * @return ret = E_OK: if the function works as programmed
 *               E_NOT_OK: if the parameter is null
 */
Std_ReturnType keypade_get_value(const keypad_t *kepad_obj, uint_8 *value){
Std_ReturnType ret = E_OK;
uint_8 l_row_index = ZERO_INIT;
uint_8 l_column_index = ZERO_INIT;
uint_8 l_row_counter = ZERO_INIT;
uint_8 column_logic = ZERO_INIT;
if((kepad_obj == NULL) || (value == NULL)){
    ret = E_NOT_OK;
}
else{
    
 for (l_row_index = ZERO_INIT ;  l_row_index <= KEYPAD_ROWS_NUMBER; l_row_index++){
     for (l_row_counter = ZERO_INIT ;  l_row_counter <= KEYPAD_ROWS_NUMBER; l_row_counter++){
     ret = gpio_pin_write_logic(&(kepad_obj->keypad_rows[l_row_counter]), LOW); 
     }
     ret = gpio_pin_write_logic(&(kepad_obj->keypad_rows[l_row_index]), HIGH); 
    _delay(200000);     
      for(l_column_index = ZERO_INIT ;  l_column_index <= KEYPAD_COLUMNS_NUMBER; l_column_index++){
          ret = gpio_pin_read_logic(&(kepad_obj->keypad_columns[l_column_index]),&column_logic );
          if(column_logic == HIGH){
          *value =  keypad_btn_values[l_row_index][l_column_index];
          }
      }
 }

}
return ret;
}