/* 
 * File:   ecu_led.h
 * Author: AyaAli
 *
 * Created on September 22, 2023, 10:50 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*Section : Includes*/
//#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/*Section : Data Type Declaration*/
typedef enum{
    LED_OFF=0,
    LED_ON  
}led_status_t;

typedef struct{
    uint_8 Port_Name :4;
    uint_8 pin : 3 ;
    uint_8 led_statues: 1;
}led_t;

/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/



/*Section : Function Declaration*/
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);

#endif	/* ECU_LED_H */

