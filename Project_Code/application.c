/* 
 * File:   application.c
 * Author: AyaAli
 * Created on September 22, 2023, 10:24 AM
 */
#include "application.h"

timer3_config_t timer3;
ccp_t ccp_obj;
volatile uint_8  ccp1_callback_flag = 0;
void CCP1_DefualtInterruptHundeler(){
Std_ReturnType ret = E_OK;
    ccp1_callback_flag++;
    ret = Timer3_Write_Value(&timer3, 0);
    if(ccp1_callback_flag == 1){
        ret = CCP1_Compare_Mode_Set_Value(&ccp_obj, 12500);
        CCP1_CFG_SELECTED_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);
    }
    else if (ccp1_callback_flag == 2){
       ret = CCP1_Compare_Mode_Set_Value(&ccp_obj, 37500);
       CCP1_CFG_SELECTED_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);
       ccp1_callback_flag = 0;
    }
    else{}
}
int main() {
   
Std_ReturnType ret = E_NOT_OK;
ccp_obj.CCP1_Interrupt_Hundeler = CCP1_DefualtInterruptHundeler;
ccp_obj.ccp_module_type = CCP1_Module;
ccp_obj.ccp_mode = CCP_COMPARE_MODE_SELECTED;
ccp_obj.ccp_mode_variant =  CCP_COMPARE_MODE_SET_PIN_LOW;
ccp_obj.ccp_ct = CCP1_CCP2_TIMER3;
ccp_obj.ccp_pin.port = PORTC_INDEX;
ccp_obj.ccp_pin.pin = PIN2;
ccp_obj.ccp_pin.direction = Input;
ret = CCP1_Compare_Mode_Set_Value(&ccp_obj, 37500);
ret = CCP_COMPARE_Init(&ccp_obj);

timer3.TMR3_Interrupt_Hundeler = NULL;
timer3.Timer_priority = Interrupt_Periority_LOW;
timer3.timer3_mode = TIMER3_TIMER_MODE;
timer3.timer3_prescaller = TIMER3_PRESCALLER_DIV_BY_1;
timer3.timer3_preload_value = 0;
timer3.timer3_register_wr_mode = TIMER3_RW_REG_16BIT_MODE;
ret = Timer3_Init(&timer3);

while(1){
 

}
 return (EXIT_SUCCESS);
}
void application_initialize(void){
   Std_ReturnType ret = E_NOT_OK;

}
