/* 
 * File:   mcal_interrupt_manager.h
 * Author: Aya Ali
 *
 * Created on November 25, 2023, 3:06 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H
/*Section : Includes*/
#include "mcal_interrupt_config.h"

/*Section : Data Type Declaration*/


/*Section : Macro Declaration*/
/*Section : Macro Function Declaration*/
/*Section : Data Type Declaration*/
/*Section : Function Declaration*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint_8 source);
void RB5_ISR(uint_8 source);
void RB6_ISR(uint_8 source);
void RB7_ISR(uint_8 source);
void ADC_ISR(void);
void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

