/* 
 * File:   ecu_button.c
 * Author: Aya Ali
 *
 * Created on October 11, 2023, 10:35 AM
 */
 

/**
 * 
 * @param btn
 * @return 
 */
#include "ecu_button.h"
Std_ReturnType Button_Initialize(const button_t *btn){
    Std_ReturnType ret = E_OK;
    if(btn == NULL){
        ret = E_NOT_OK;
    }
    else{
    ret = gpio_pin_direction_intialize(&(btn->button_pin));
    return ret;
    }
}
/**   
 * @param btn 
 * @param btn_state
 * @return 
 */

Std_ReturnType Button_Read_State(const button_t *btn ,button_state_t *btn_state){
 Std_ReturnType ret = E_OK;
 logic_t Pin_Logic_Status = LOW;
    if((btn == NULL) || (btn_state == NULL) ){
        ret = E_NOT_OK;
    }
 
    else{
           gpio_pin_read_logic(&(btn->button_pin),&Pin_Logic_Status);
        if (BUTTON_ACTIVE_HIGH == btn->button_connection){
            if(Pin_Logic_Status == HIGH){
         
            *btn_state = BUTTON_PRESSED;
            }
            else{ 
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection){
           
             if(Pin_Logic_Status == HIGH){
         
            *btn_state = BUTTON_RELEASED;
            }
            else{ 
                *btn_state = BUTTON_PRESSED;
            }
            
        }
        else {/*Nothing*/}
           ret = E_OK;
    }
return ret;



}


