/* 
 * File:   ecu_relay_cfg.h
 * Author: Aya Ali
 *
 * Created on October 19, 2023, 5:20 PM
 */

#include "ecu_dc_motor.h"

Std_ReturnType DC_Motor_Intialize(const dc_motor_t *dc_motor){
Std_ReturnType ret = E_OK;
if(dc_motor == NULL){
    ret = E_NOT_OK;

}

else{
 
    gpio_pin_intialize(&(dc_motor->dc_motors[DC_MOTOR_PIN1]));
     gpio_pin_intialize(&(dc_motor->dc_motors[DC_MOTOR_PIN2]));
}
return ret;
}
Std_ReturnType DC_Motor_Move_Right(const dc_motor_t *dc_motor){
Std_ReturnType ret = E_OK;
if(dc_motor == NULL){
    ret = E_NOT_OK;

}

else{

    gpio_pin_write_logic(&(dc_motor->dc_motors[DC_MOTOR_PIN1]), HIGH);
    gpio_pin_write_logic(&(dc_motor->dc_motors[DC_MOTOR_PIN2]), LOW);
}
return ret;


}
Std_ReturnType DC_Motor_Move_Left(const dc_motor_t *dc_motor){
Std_ReturnType ret = E_OK;
if(dc_motor == NULL){
    ret = E_NOT_OK;

}

else{
   gpio_pin_write_logic(&(dc_motor->dc_motors[DC_MOTOR_PIN1]), LOW);
    gpio_pin_write_logic(&(dc_motor->dc_motors[DC_MOTOR_PIN2]), HIGH);
    
}
return ret;

}
Std_ReturnType DC_Motor_Stop(const dc_motor_t *dc_motor){
Std_ReturnType ret = E_OK;

if(dc_motor == NULL){
    ret = E_NOT_OK;

}

else{

    gpio_pin_write_logic(&(dc_motor->dc_motors[DC_MOTOR_PIN1]), LOW);
    gpio_pin_write_logic(&(dc_motor->dc_motors[DC_MOTOR_PIN2]), LOW);
    
    
}
return ret;


}
