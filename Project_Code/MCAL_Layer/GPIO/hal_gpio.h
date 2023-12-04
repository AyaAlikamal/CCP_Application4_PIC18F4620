/* 
 * File:   hal_gpio.h
 * Author: AyaAli
 *
 * Created on September 22, 2023, 10:34 AM
 */


#ifndef HAL_GPIO_H
#define	HAL_GPIO_H
/*Section : Includes*/
#include "../../../../Embeded-Compiler/pic/include/proc/pic18f4620.h"
#include "../mcal_std_type.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/*Section : Data Type Declaration*/


/*Section : Macro Declaration*/

#define BIT_MASK 1
#define PORT_PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER  5 
#define PORTC_MASK 0xFF




/*Section : Macro Function Declaration*/

#define HWREG8 (_X)  (*((volatile uint_8 *)(_X)))


#define SET_BIT(REG, BIT_POSN)      (REG |= (BIT_MASK<<BIT_POSN))  
#define CLEAR_BIT(REG, BIT_POSN)    (REG &= ~(BIT_MASK<<BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)   (REG ^=(BIT_MASK<<BIT_POSN))
#define READ_BIT(REG, BIT_POSN)     ((REG >>BIT_POSN)&BIT_MASK)




/*Section : Data Type Declaration*/
typedef enum{
    LOW = 0,
    HIGH        
}logic_t;


typedef enum{
    Output = 0,
    Input      
}direction_t;

typedef enum{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7        
}pin_index;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX        
}Port_Index;

typedef struct{
    uint_8 port :3;
    uint_8 pin  :3;
    uint_8 direction :1;
    uint_8 logic : 1;
}pin_config_t;

/*Section : Function Declaration*/

Std_ReturnType gpio_pin_direction_intialize(const pin_config_t * pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * pin_config, direction_t * direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t * pin_config, logic_t  logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t * pin_config, logic_t * logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t * pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t * pin_config);


Std_ReturnType gpio_port_direction_intialize(Port_Index port, uint_8 direction);
Std_ReturnType gpio_port_get_direction_status(Port_Index port, uint_8 *direction_status);
Std_ReturnType gpio_port_write_logic(Port_Index port, uint_8 logic);
Std_ReturnType gpio_port_read_logic(Port_Index port, uint_8 *logic);
Std_ReturnType gpio_port_toggle_logic(Port_Index port);

#endif	/* HAL_GPIO_H */

