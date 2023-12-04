/* 
 * File:   hal_eeprom.c
 * Author: Aya Ali
 *
 * Created on November 26, 2023, 4:27 PM
 */

#include "hal_eeprom.h"

/**
 * @param Add
 * @param data
 * @return 
 */
Std_ReturnType Data_EEPROM_Write_Data(uint_16 Add, uint_8 data){
Std_ReturnType ret = E_OK ;
/*Store the interrupt statues in a variable */
uint_8 Global_Interrupt_Statues = INTCONbits.GIE;
/*Update the address */
EEADRH = (uint_8)((Add >> 8) & 0x03);
EEADR = (uint_8)(Add & 0xFF);
/*Write the data you want*/
EEDATA = data;
/*select access data EEPROM memory */
EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
/*allow write cycle to flash program/ data EEPROM */
EECON1bits.WREN = ALLOW_WRITE_CYCLE_FLASH_EEPROM;
/*DISABLE global interrupt*/
INTERRUPT_GLOBALEINTERRUPT_DISABLE();
/*Write required sequence 0x55 -> 0xAA */
EECON2 = 0x55;
EECON2 = 0xAA;
/*Initiates a data EEPROM erase/write cycle */
EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
/*wait for write complete*/
while(EECON1bits.WR);
/*Inhibits write cycle to flash program/ data EEPROM */
EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
/*Return the interrupt status */
INTCONbits.GIE = Global_Interrupt_Statues;
return ret;
}
/**
 * 
 * @param Add
 * @param data
 * @return 
 */
Std_ReturnType Data_EEPROM_Read_Data(uint_16 Add, uint_8 *data){
Std_ReturnType ret = E_OK ;

if (data == NULL){
    ret = E_NOT_OK;
}
else{
/*Update address Register*/
EEADRH = (uint_8)((Add >> 8) & 0x03);
EEADR = (uint_8)(Add & 0xFF);
/*Select Access data EEPROM */ 
EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
/*Initiates a data EEPROM read cycle*/
EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
NOP();
NOP();
/*Return data */
*data = EEDATA;
}
return ret;
}
