/* 
 * File:   mcal_external_interrupt.h
 * Author: Aya Ali
 *
 * Created on November 25, 2023, 3:06 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/*Section : Includes*/
#include "mcal_interrupt_config.h"
/*Section : Macro Declaration*/
/*Section : Macro Function Declaration*/
#ifdef INTERRUPT_INTx_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*ENABLE external interrupt at INT0*/
#define EX_INT0_INTERRUPT_ENABLE()       (INTCONbits.INT0IE = 1)
/*disABLE external interrupt at INT0*/
#define EX_INT0_INTERRUPT_DISABLE()      (INTCONbits.INT0IE = 0)
/*clear the interrupt flag for the external interrupt*/
#define EX_INT0_INTERRUPT_FLAG_CLEAR()   (INTCONbits.INT0IF = 0)
/*set the edge detect for rising edge (negative edge)*/
#define EX_INT0_RISINGSET()              (INTCON2bits.INTEDG0 = 1)
/*set the edge detect for falling edge (positive edge)*/
#define EX_INT0_FALLINGSET()             (INTCON2bits.INTEDG0 = 0)

/*ENABLE external interrupt at INT1*/
#define EX_INT1_INTERRUPT_ENABLE()       (INTCON3bits.INT1IE = 1)
/*disABLE external interrupt at INT1*/
#define EX_INT1_INTERRUPT_DISABLE()      (INTCON3bits.INT1IE = 0)
/*clear the interrupt flag for the external interrupt*/
#define EX_INT1_INTERRUPT_FLAG_CLEAR()   (INTCON3bits.INT1IF = 0)
/*set the edge detect for rising edge (negative edge)*/
#define EX_INT1_RISINGSET()              (INTCON2bits.INTEDG1 = 1)
/*set the edge detect for falling edge (positive edge)*/
#define EX_INT1_FALLINGSET()             (INTCON2bits.INTEDG1 = 0)


/*ENABLE external interrupt at INT2*/
#define EX_INT2_INTERRUPT_ENABLE()       (INTCON3bits.INT2IE= 1)
/*disABLE external interrupt at INT2*/
#define EX_INT2_INTERRUPT_DISABLE()      (INTCON3bits.INT2IE = 0)
/*clear the interrupt flag for the external interrupt*/
#define EX_INT2_INTERRUPT_FLAG_CLEAR()   (INTCON3bits.INT2IF = 0)
/*set the edge detect for rising edge (negative edge)*/
#define EX_INT2_RISINGSET()              (INTCON2bits.INTEDG2 = 1)
/*set the edge detect for falling edge (positive edge)*/
#define EX_INT2_FALLINGSET()             (INTCON2bits.INTEDG2 = 0)

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*set the INT1 priority to high*/
#define EX_INT1_HIGH_PRIORITY_SET()      (INTCON3bits.INT1IP = 1)
/*set the INT1 priority to low*/
#define EX_INT1_LOW_PRIORITY_SET()       (INTCON3bits.INT1IP = 0)
/*set the INT2 priority to high*/
#define EX_INT2_HIGH_PRIORITY_SET()      (INTCON3bits.INT2IP = 1)
/*set the INT2 priority to low*/
#define EX_INT2_LOW_PRIORITY_SET()       (INTCON3bits.INT2IP = 0)
#endif
#endif

#ifdef INTERRUPT_ONCHANGE_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/*ENABLE external interrupt at RBx*/
#define EX_RBx_INTERRUPT_ENABLE()       (INTCONbits.RBIE = 1)
/*disABLE external interrupt at RBx*/
#define EX_RBx_INTERRUPT_DISABLE()      (INTCONbits.RBIE = 0)
/*clear the interrupt flag for the external interrupt*/
#define EX_RBx_INTERRUPT_FLAG_CLEAR()   (INTCONbits.RBIF = 0)

#ifdef INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
/*set the RBx priority to high*/
#define EX_RBx_HIGH_PRIORITY_SET()      (INTCON2bits.RBIP = 1)
/*set the RBx priority to low*/
#define EX_RBx_LOW_PRIORITY_SET()       (INTCON2bits.RBIP = 0)
#endif

#endif

/*Section : Data Type Declaration*/
typedef enum{
   EX_Interrupt_Rising_Edge =0,
   EX_Interrupt_Falling_Edge       
}EX_Interrupt_edg;

typedef enum{
   EX_Interrupt_INT0 =0,
   EX_Interrupt_INT1,
   EX_Interrupt_INT2        
}EX_Interrupt_src;

typedef struct {
    void (*Ext_Intterrupt)(void);
   pin_config_t mcu_pin;
   EX_Interrupt_src   source;
   EX_Interrupt_edg   edge;
   Interrupt_Periority_cfg priority;       
}Ex_Interrupt_INTx_t;

typedef struct {
 pin_config_t mcu_pin;
 void (*Ext_Intterrupt_HIGH)(void);
 void (*Ext_Intterrupt_LOW)(void);
 Interrupt_Periority_cfg priority;
}Ex_Interrupt_RBx_t;

/*Section : Data Type Declaration*/
/*Section : Function Declaration*/
Std_ReturnType Interrupt_INTx_Initialization(const Ex_Interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_INTx_DeInitialization(const Ex_Interrupt_INTx_t *int_obj);
Std_ReturnType Interrupt_RBx_Initialization(const Ex_Interrupt_RBx_t *int_obj);
Std_ReturnType Interrupt_RBx_DeInitialization(const Ex_Interrupt_RBx_t *int_obj);


#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

