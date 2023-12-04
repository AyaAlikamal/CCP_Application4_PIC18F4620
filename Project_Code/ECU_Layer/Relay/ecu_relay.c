/* 
 * File:   ecu_relay_cfg.h
 * Author: Aya Ali
 *
 * Created on October 19, 2023, 5:20 PM
 */

/*Section : Includes*/
#include "ecu_relay.h"


/**
 * @brief Initialize the relay module 
 * @param _relay is a pointer to the relay module configuration
 * @return status of the function
 *         E_NOT_OK: the function has issue while performing this action
 *         E_OK    : the function done successfully
 */
Std_ReturnType Relay_Initialize( const Relay_t *_relay){
Std_ReturnType ret = E_OK;
if(_relay == NULL){
ret = E_NOT_OK;
}
else{

     pin_config_t pin_obj = {.port =_relay->Relay_Port, 
                             .pin = _relay->Relay_Pin, 
                             .logic = _relay->Relay_Status, 
                             .direction = Output};

      gpio_pin_intialize(&pin_obj);
}
}
/**
 * @brief Turn on the relay
 * @param _relay is a pointer to the relay module configuration
 * @return status of the function
 *         E_NOT_OK: the function has issue while performing this action
 *         E_OK    : the function done successfully
 */
Std_ReturnType Relay_Turn_ON( const Relay_t *_relay){
Std_ReturnType ret = E_OK;
if(_relay == NULL){
    ret = E_NOT_OK;

}
else{
      pin_config_t pin_obj = {.port =_relay->Relay_Port, 
                             .pin = _relay->Relay_Pin, 
                             .logic = _relay->Relay_Status, 
                             .direction = Output};

      gpio_pin_write_logic(&pin_obj, HIGH);
}
}
/**
 * @brief Turn off the relay
 * @param _relay is a pointer to the relay module configuration
 * @return status of the function
 *         E_NOT_OK: the function has issue while performing this action
 *         E_OK    : the function done successfully
 */
Std_ReturnType Relay_Turn_OFF( const Relay_t *_relay){
Std_ReturnType ret = E_OK;
if(_relay == NULL){
ret = E_NOT_OK;
}
else{
      pin_config_t pin_obj = {.port =_relay->Relay_Port, 
                             .pin = _relay->Relay_Pin, 
                             .logic = _relay->Relay_Status, 
                             .direction = Output};
      gpio_pin_write_logic(&pin_obj, LOW);
}
}
