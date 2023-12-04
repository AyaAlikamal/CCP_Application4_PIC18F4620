/* 
 * File:   mcal_interrut_manager.h
 * Author: Aya Ali
 *
 * Created on November 25, 2023, 3:04 PM
 */

#ifndef MCAL_INTERRUT_MANAGER_H
#define	MCAL_INTERRUT_MANAGER_H
/*Section : Includes*/
#include "mcal_interrupt_config.h"

/*Section : Data Type Declaration*/

/*Section : Macro Declaration*/
#ifdef ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
  /*Disable interrupt routine for ADC module*/
#define ADC_INTERRUPT_DISABLE() (PIE1bits.ADIE = 0)
  /*Enable interrupt routine for ADC module*/
#define ADC_INTERRUPT_ENABLE()  (PIE1bits.ADIE = 1)
/*Clear the interrupt flag*/
#define ADC_CLEAR_FLAG()        (PIR1bits.ADIF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define ADC_HIGH_PRIORITY_SET()   (IPR1bits.ADIP = 1)
#define ADC_LOW_PRIORITY_SET()    (IPR1bits.ADIP = 0)
#endif
#endif
#ifdef TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
  /*Disable interrupt routine for Timer0 module*/
#define TIMER0_INTERRUPT_DISABLE() (INTCONbits.TMR0IE = 0)
  /*Enable interrupt routine for Timer0 module*/
#define TIMER0_INTERRUPT_ENABLE()  (INTCONbits.TMR0IE = 1)
/*Clear the interrupt flag*/
#define TIMER0_CLEAR_FLAG()        (INTCONbits.TMR0IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER0_HIGH_PRIORITY_SET()   (INTCON2bits.TMR0IP = 1)
#define TIMER0_LOW_PRIORITY_SET()    (INTCON2bits.TMR0IP= 0)
#endif
#endif



#ifdef TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
  /*Disable interrupt routine for Timer1 module*/
#define TIMER1_INTERRUPT_DISABLE() (PIE1bits.TMR1IE = 0)
  /*Enable interrupt routine for Timer1 module*/
#define TIMER1_INTERRUPT_ENABLE()  (PIE1bits.TMR1IE = 1)
/*Clear the interrupt flag*/
#define TIMER1_CLEAR_FLAG()        (PIR1bits.TMR1IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER1_HIGH_PRIORITY_SET()   (IPR1bits.TMR1IP = 1)
#define TIMER1_LOW_PRIORITY_SET()    (IPR1bits.TMR1IP = 0)
#endif
#endif

#ifdef TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
  /*Disable interrupt routine for Timer2 module*/
#define TIMER2_INTERRUPT_DISABLE() (PIE1bits.TMR2IE = 0)
  /*Enable interrupt routine for Timer2 module*/
#define TIMER2_INTERRUPT_ENABLE()  (PIE1bits.TMR2IE = 1)
/*Clear the interrupt flag*/
#define TIMER2_CLEAR_FLAG()        (PIR1bits.TMR2IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER2_HIGH_PRIORITY_SET()   (IPR1bits.TMR2IP = 1)
#define TIMER2_LOW_PRIORITY_SET()    (IPR1bits.TMR2IP = 0)
#endif
#endif


#ifdef TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
  /*Disable interrupt routine for Timer3 module*/
#define TIMER3_INTERRUPT_DISABLE() (PIE2bits.TMR3IE = 0)
  /*Enable interrupt routine for Timer3 module*/
#define TIMER3_INTERRUPT_ENABLE()  (PIE2bits.TMR3IE = 1)
/*Clear the interrupt flag*/
#define TIMER3_CLEAR_FLAG()        (PIR2bits.TMR3IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define TIMER3_HIGH_PRIORITY_SET()   (IPR2bits.TMR3IP = 1)
#define TIMER3_LOW_PRIORITY_SET()    (IPR2bits.TMR3IP = 0)
#endif
#endif


#ifdef CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
  /*Disable interrupt routine for CCP1 module*/
#define CCP1_INTERRUPT_DISABLE() (PIE1bits.CCP1IE = 0)
/*Enable interrupt routine for CCP1 module*/
#define CCP1_INTERRUPT_ENABLE()  (PIE1bits.CCP1IE = 1)
/*Clear the interrupt flag*/
#define CCP1_CLEAR_FLAG()        (PIR1bits.CCP1IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define CCP1_HIGH_PRIORITY_SET()   (IPR1bits.CCP1IP = 1)
#define CCP1_LOW_PRIORITY_SET()    (IPR1bits.CCP1IP = 0)
#endif
#endif


#ifdef CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE    
  /*Disable interrupt routine for CCP2 module*/
#define CCP2_INTERRUPT_DISABLE() (PIE2bits.CCP2IE = 0)
/*Enable interrupt routine for CCP2 module*/
#define CCP2_INTERRUPT_ENABLE()  (PIE2bits.CCP2IE = 1)
/*Clear the interrupt flag*/
#define CCP2_CLEAR_FLAG()        (PIR2bits.CCP2IF = 0)
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
#define CCP2_HIGH_PRIORITY_SET()   (IPRbits.CCP2IP = 1)
#define CCP2_LOW_PRIORITY_SET()    (IPRbits.CCP2IP = 0)
#endif
#endif

/*Section : Macro Function Declaration*/
/*Section : Data Type Declaration*/
/*Section : Function Declaration*/

#endif	/* MCAL_INTERRUT_MANAGER_H */

