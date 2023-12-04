/* 
 * File:   ecu_button.h
 * Author: Aya Ali
 *
 * Created on October 11, 2023, 10:35 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
#include "ecu_button_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/*Section : Includes*/
/*Section : Data Type Declaration*/
typedef enum{
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED,        
}button_state_t;

typedef enum{
  BUTTON_ACTIVE_HIGH = 0,
  BUTTON_ACTIVE_LOW,       
}Button_active_t;

typedef struct{
    pin_config_t button_pin;
 button_state_t button_state;
Button_active_t button_connection; 
}button_t;
 
/*Section : Macro Declaration*/
/*Section : Macro Function Declaration*/



/*Section : Function Declaration*/
Std_ReturnType Button_Initialize(const button_t *btn);
Std_ReturnType Button_Read_State(const button_t *btn ,button_state_t *btn_state);



#endif	/* ECU_BUTTON_H */

