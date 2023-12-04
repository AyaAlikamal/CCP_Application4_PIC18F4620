/* 
 * File:   mcal_interrupt_config.h
 * Author: Aya Ali
 * Created on November 25, 2023, 3:05 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H
/*Section : Includes*/
#include "../../../../Embeded-Compiler/pic/include/proc/pic18f4620.h"
#include  "../mcal_std_type.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../GPIO/hal_gpio.h"

/*Section : Macro Declaration*/
#define INTERRUPT_ENABLE           1
#define INTERRUPT_DISABLE          0
#define INTERRUPT_OCCUR            1
#define INTERRUPT_NOT_OCCUR        0
#define INTERRUPT_PRIORITY_ENABLE  1
#define INTERRUPT_PRIORITY_DISABLE 0
/*Section : Macro Function Declaration*/

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
/*enable priority level on interrupt*/
#define INTERRUPT_PRIORITYLEVEL_ENABLE()         (RCONbits.IPEN = 1)
/*disable priority level on interrupt*/
#define INTERRUPT_PRIORITYLEVEL_DISABLE()        (RCONbits.IPEN = 0)

/*enable high prioprity glopale intterrupt */
#define INTERRUPT_GLOBALEINTERRUPTHIGH_ENABLE()  (INTCONbits.GIEH = 1)
/*disable high prioprity glopale intterrupt */
#define INTERRUPT_GLOBALEINTERRUPTHIGH_DISABLE() (INTCONbits.GIEH = 0)
/*enable LOW prioprity glopale intterrupt */
#define INTERRUPT_GLOBALEINTERRUPTLOW_ENABLE()   (INTCONbits.GIEL = 1)
/*disable LOW prioprity glopale intterrupt */
#define INTERRUPT_GLOBALEINTERRUPTLOW_DISABLE()  (INTCONbits.GIEL = 0)
#else
/*enable glopale intterrupt */
#define INTERRUPT_GLOBALEINTERRUPT_ENABLE()  (INTCONbits.GIE = 1)
/*disable glopale intterrupt */
#define INTERRUPT_GLOBALEINTERRUPT_DISABLE() (INTCONbits.GIE = 0)
/*enable PERIPHERAL intterrupt */
#define INTERRUPT_PERIPHERALINTERRUPT_ENABLE()   (INTCONbits.PEIE = 1)
/*disable PERIPHERAL intterrupt */
#define INTERRUPT_PERIPHERALINTERRUPT_ENABLE()   (INTCONbits.PEIE = 0)
#endif
/*Section : Data Type Declaration*/

typedef enum {
    Interrupt_Periority_LOW = 0,
    Interrupt_Periority_HIGH        
}Interrupt_Periority_cfg;

/*Section : Function Declaration*/
#endif	/* MCAL_INTERRUPT_CONFIG_H */

