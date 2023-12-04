/* 
 * File:   mcal_interrut_manager.h
 * Author: Aya Ali
 *
 * Created on November 25, 2023, 3:04 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint_8 RB4_Flag = 1,RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;
#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
void  __interrupt() Interrupt_Manager_High(void){
  if((INTCONbits.INT0IE ==INTERRUPT_ENABLE) && (INTCONbits.INT0IF==INTERRUPT_OCCUR)){
    INT0_ISR();
    }
    else{}
   if((INTCON3bits.INT2E ==INTERRUPT_ENABLE) && (INTCON3bits.INT2F ==INTERRUPT_OCCUR)){
    INT2_ISR();
    }
    else{}
  
}
void __interrupt(low_priority) Interrupt_Manager_Low(void){
 if((INTCON3bits.INT1E ==INTERRUPT_ENABLE) && (INTCON3bits.INT1F ==INTERRUPT_OCCUR)){
    INT1_ISR();
    }
    else{}
}
#else
void __interrupt() Interrupt_Manager(void){
    if((INTCONbits.INT0IE ==INTERRUPT_ENABLE) && (INTCONbits.INT0IF==INTERRUPT_OCCUR)){
    INT0_ISR();
    }
    else{}
    if((INTCON3bits.INT1E ==INTERRUPT_ENABLE) && (INTCON3bits.INT1F ==INTERRUPT_OCCUR)){
    INT1_ISR();
    }
    else{}
    if((INTCON3bits.INT2E ==INTERRUPT_ENABLE) && (INTCON3bits.INT2F ==INTERRUPT_OCCUR)){
    INT2_ISR();
    }
    else{}
    if((INTCONbits.RBIE ==INTERRUPT_ENABLE) && (INTCONbits.RBIF ==INTERRUPT_OCCUR) && 
        (PORTBbits.RB4 == HIGH)&& (RB4_Flag== 1)){
        RB4_Flag = 0;
        RB4_ISR(1);
    }
    else{}
    if((INTCONbits.RBIE ==INTERRUPT_ENABLE) && (INTCONbits.RBIF ==INTERRUPT_OCCUR)&& 
       (PORTBbits.RB4 == LOW)&& (RB4_Flag== 0)){
        RB4_Flag = 1;
        RB4_ISR(0);
    }
    else{}
    if((INTCONbits.RBIE ==INTERRUPT_ENABLE) && (INTCONbits.RBIF ==INTERRUPT_OCCUR) &&
        (PORTBbits.RB5 == HIGH)&& (RB5_Flag== 1)){
          RB5_Flag = 0;
          RB5_ISR(1);
    }
    else{}
    if((INTCONbits.RBIE ==INTERRUPT_ENABLE) && (INTCONbits.RBIF ==INTERRUPT_OCCUR)&& 
        (PORTBbits.RB5 == LOW)&& (RB5_Flag== 0)){
          RB5_Flag = 1;
          RB5_ISR(0);
    }
    else{}
    if((INTCONbits.RBIE ==INTERRUPT_ENABLE) && (INTCONbits.RBIF ==INTERRUPT_OCCUR) && 
       (PORTBbits.RB6 == HIGH)&& (RB6_Flag== 1)){
          RB6_Flag = 0;
          RB6_ISR(1);
    }
    else{}
    if((INTCONbits.RBIE ==INTERRUPT_ENABLE) && (INTCONbits.RBIF ==INTERRUPT_OCCUR)&&
        (PORTBbits.RB6 == LOW)&& (RB6_Flag== 0)){
          RB6_Flag = 1;
          RB6_ISR(0);
    }
    else{} 
    if((INTCONbits.RBIE ==INTERRUPT_ENABLE) && (INTCONbits.RBIF ==INTERRUPT_OCCUR) &&
        (PORTBbits.RB7 == HIGH)&& (RB7_Flag== 1)){
          RB7_Flag = 0;
          RB7_ISR(1);
    }
    else{}
    if((INTCONbits.RBIE ==INTERRUPT_ENABLE) && (INTCONbits.RBIF ==INTERRUPT_OCCUR)&&
       (PORTBbits.RB7 == LOW)&& (RB7_Flag== 0)){  
          RB7_Flag = 1;
          RB7_ISR(0);
    }
    else{} 
    if((PIE1bits.ADIE ==INTERRUPT_ENABLE) && (PIR1bits.ADIF==INTERRUPT_OCCUR)){
    ADC_ISR();
    }
    else{}
if((INTCONbits.TMR0IE ==INTERRUPT_ENABLE) && (INTCONbits.TMR0IF ==INTERRUPT_OCCUR)){
    TIMER0_ISR();
    }
    else{}
if((PIE1bits.TMR1IE ==INTERRUPT_ENABLE) && (PIR1bits.TMR1IF  ==INTERRUPT_OCCUR)){
    TIMER1_ISR();
    }
    else{}
if((PIE1bits.TMR2IE ==INTERRUPT_ENABLE) && (PIR1bits.TMR2IF ==INTERRUPT_OCCUR)){
    TIMER2_ISR();
    }
    else{}
if((PIE2bits.TMR3IE ==INTERRUPT_ENABLE) && (PIR2bits.TMR3IF ==INTERRUPT_OCCUR)){
    TIMER3_ISR();
    }
    else{}

if((PIE1bits.CCP1IE ==INTERRUPT_ENABLE) && (PIR1bits.CCP1IF ==INTERRUPT_OCCUR)){
    CCP1_ISR();
    }
    else{}
if((PIE2bits.CCP2IE ==INTERRUPT_ENABLE) && (PIR2bits.CCP2IF ==INTERRUPT_OCCUR)){
    CCP2_ISR();
    }
    else{}
}
#endif