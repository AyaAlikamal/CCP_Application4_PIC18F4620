/* 
 * File:   ecu_kypad_cfg.h
 * Author: Aya Ali
 *
 * Created on November 1, 2023, 4:57 PM
 */


#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H
/*Section : Includes*/
#include "ecu_kypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"


/*Section : Macro Declaration*/
#define KEYPAD_ROWS_NUMBER 4
#define KEYPAD_COLUMNS_NUMBER 4

/*Section : Data Type Declaration*/
typedef struct {
pin_config_t keypad_rows[KEYPAD_ROWS_NUMBER];
pin_config_t keypad_columns[KEYPAD_COLUMNS_NUMBER];
}keypad_t;
/*Section : Macro Function Declaration*/
/*Section : Data Type Declaration*/
/*Section : Function Declaration*/

Std_ReturnType keypade_initialize(const keypad_t *kepad_obj);
Std_ReturnType keypade_get_value(const keypad_t *kepad_obj, uint_8 *value);

#endif	/* ECU_KEYPAD_H */

