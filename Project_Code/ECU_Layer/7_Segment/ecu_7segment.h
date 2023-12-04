/* 
 * File:   ecu_7segment.h
 * Author: Aya Ali
 *
 * Created on October 27, 2023, 12:53 PM
 */

#ifndef ECU_7SEGMENT_H
#define	ECU_7SEGMENT_H

/*Section : Includes*/

#include "ecu_7segment_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/*Section : Macro Declaration*/
#define SEGMENT_PIN_0 0 
#define SEGMENT_PIN_1 1
#define SEGMENT_PIN_2 2
#define SEGMENT_PIN_3 3
/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/

typedef enum {
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE        
}Segment_type_t;

typedef struct{
pin_config_t segment_pins[4];
Segment_type_t segment_type;
}Segment_t;
/*Section : Function Declaration*/

Std_ReturnType segment_initialize (const Segment_t *segment);
Std_ReturnType segment_write_data (const Segment_t *segment, uint_8 number);


#endif	/* ECU_7SEGMENT_H */

