/* 
 * File:   ecu_dc_motor.h
 * Author: Aya Ali
 *
 * Created on October 21, 2023, 6:41 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H


/*Section : Includes*/
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/*Section : Macro Declaration*/

#define DC_MOTOR_ON_STATUS 0x01U
#define DC_MOTOR_OFF_STATUS 0x00U
#define DC_MOTOR_PIN1 0x00U
#define DC_MOTOR_PIN2 0x01U



/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef struct{
pin_config_t dc_motors[2];
}dc_motor_t;

/*Section : Function Declaration*/

Std_ReturnType DC_Motor_Intialize(const dc_motor_t *dc_motor);
Std_ReturnType DC_Motor_Move_Right(const dc_motor_t *dc_motor);
Std_ReturnType DC_Motor_Move_Left(const dc_motor_t *dc_motor);
Std_ReturnType DC_Motor_Stop(const dc_motor_t *dc_motor);
#endif	/* ECU_DC_MOTOR_H */

