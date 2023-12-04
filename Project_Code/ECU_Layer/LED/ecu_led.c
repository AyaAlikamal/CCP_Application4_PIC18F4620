#include "ecu_led.h"
/**
 * @brief initialize the led pin
 * @param led
 * @return 
 */
Std_ReturnType led_initialize(const led_t *led){
    
Std_ReturnType ret = E_OK;
if(led == NULL){
   ret = E_NOT_OK;
}
else{
    pin_config_t pin_obj = {.port = led->Port_Name,
                        .pin = led->pin,
                        .direction = Output, 
                        .logic = led->led_statues
                        } ;
    gpio_pin_intialize(&pin_obj);  
}
return ret;

}
/**
 * 
 * @param led
 * @return 
 */

Std_ReturnType led_turn_on(const led_t *led){
Std_ReturnType ret = E_OK;
if(led == NULL){
   ret = E_NOT_OK;
}
else{
     pin_config_t pin_obj = {.port = led->Port_Name,
                        .pin = led->pin,
                        .direction = Output, 
                        .logic = led->led_statues
                        } ;
     gpio_pin_write_logic(&pin_obj, HIGH);
}
return ret;
}

/**
 * 
 * @param led
 * @return 
 */

Std_ReturnType led_turn_off(const led_t *led){
Std_ReturnType ret = E_OK;
if(led == NULL){
   ret = E_NOT_OK;
}
else{
     pin_config_t pin_obj = {.port = led->Port_Name,
                        .pin = led->pin,
                        .direction = Output, 
                        .logic = led->led_statues
                        } ;
      gpio_pin_write_logic(&pin_obj, LOW);
}
return ret;

}

/**
 * 
 * @param led
 * @return 
 */
Std_ReturnType led_toggle(const led_t *led){
Std_ReturnType ret = E_OK;
if(led == NULL){
   ret = E_NOT_OK;
}
else{
     pin_config_t pin_obj = {.port = led->Port_Name,
                        .pin = led->pin,
                        .direction = Output, 
                        .logic = led->led_statues
                        } ;
     gpio_pin_toggle_logic(&pin_obj);
    
}
return ret;


}
