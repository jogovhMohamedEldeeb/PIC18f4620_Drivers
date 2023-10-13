/* 
 * File:   hal_eeprom.h
 * Author: m7md
 *
 * Created on 07 August 2023, 15:33
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/************************ Includes ************************/
//#include "../proc/pic18f4620.h"
#include "../../MCAL_layer/mcal_std_types.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"


/************************  Macro Declaration ************************/
 

/************************  Macro Function Declaration ************************/


/************************  Data Type Declaration ************************/
 

/************************  Software interface Declaration ************************/

Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);

 
#endif	/* HAL_EEPROM_H */

