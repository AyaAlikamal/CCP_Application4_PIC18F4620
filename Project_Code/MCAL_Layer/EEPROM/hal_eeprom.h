/* 
 * File:   hal_eeprom.h
 * Author: Aya Ali
 *
 * Created on November 26, 2023, 4:27 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H
/*Section : Includes*/
#include "../../../Embeded-Compiler/pic/include/proc/pic18f4620.h"
#include "../mcal_std_type.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*Section : Macro Declaration*/

#define ACCESS_FLASH_PROGRAM_MEMORY        1
#define ACCESS_EEPROM_PROGRAM_MEMORY       0

#define ACCESS_FLASH_EEPROM_MEMORY         0
#define ACCESS_CONFIG_REGISTERS            1

#define ALLOW_WRITE_CYCLE_FLASH_EEPROM     1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM  0

#define INITIATE_DATA_EEPROM_WRITE_ERASE   1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED  0

#define INITIATE_DATA_EEPROM_READ          1 
/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
/*Section : Function Declaration*/

Std_ReturnType Data_EEPROM_Write_Data(uint_16 Add, uint_8 data);
Std_ReturnType Data_EEPROM_Read_Data(uint_16 Add, uint_8 *data);
#endif	/* HAL_EEPROM_H */

