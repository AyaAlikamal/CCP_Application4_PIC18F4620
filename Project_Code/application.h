/* 
 * File:   application.h
 * Author: AyaAli
 *
 * Created on September 22, 2023, 10:53 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include "ECU_Layer/ecu_init.h"
#include "MCAL_Layer/interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/Timer/hal_Time0.h"
#include "MCAL_Layer/Timer1/hal_timer1.h"
#include "MCAL_Layer/Timer2/hal_timer2.h"
#include "MCAL_Layer/Timer3/hal_timer3.h"
#include "MCAL_Layer/CCP1/hal_ccp1.h"

 void application_initialize(void);
 void welcome_massage(void);
 void loading_massage(void);
 void int0_ISR(void);

#endif	/* APPLICATION_H */

