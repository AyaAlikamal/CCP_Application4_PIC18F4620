/* 
 * File:   ecu_relay.h
 * Author: Aya Ali
 *
 * Created on October 19, 2023, 5:20 PM
 */
#ifndef ECU_RELAY_H
#define	ECU_RELAY_H
/*Section : Includes*/

#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/*Section : Macro Declaration*/
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U
/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef struct {
    uint_8 Relay_Port :4;
    uint_8 Relay_Pin :3;
    uint_8 Relay_Status: 1;
}Relay_t;


/*Section : Function Declaration*/
Std_ReturnType Relay_Initialize( const Relay_t *_relay);
Std_ReturnType Relay_Turn_ON( const Relay_t *_relay);
Std_ReturnType Relay_Turn_OFF( const Relay_t *_relay);
#endif	/* ECU_RELAY_H */

