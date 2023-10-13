/* 
 * File:   hal_eeprom.c
 * Author: m7md
 *
 * Created on 07 August 2023, 15:33
 */

#include "hal_eeprom.h"


Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    Std_ReturnType ret = E_OK;
    /* Read the interrupt status ( Enabled or Disabled ) */
    uint8 Global_interrupt_status = INTCONbits.GIE;
    /* Update the address register */
    EEADRH = (uint8) ((bAdd >> 8) & 0x03);
    EEADR = (uint8) (bAdd & 0xFF);
    /* Update the Data Register */
    EEDATA = bData;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    /* Allows write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = 1;
    /* Disable all interrupts "General Interrupt" */
    INTERRUPT_GlobalInterruptDisable();
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = 1;
    /* Wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = 0;
    /* Restore the Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIE = Global_interrupt_status;
    
    return ret;
}

Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    Std_ReturnType ret = E_OK;
    if(NULL == bData){
        ret = E_NOT_OK;
    }
    else{
    /* Update the Address Registers */
    EEADRH = (uint8) ((bAdd >> 8) & 0x03);
    EEADR = (uint8) (bAdd & 0xFF);
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    /* Initiates a data EEPROM read cycle */
    EECON1bits.RD = 1;
    NOP();  /* NOPs may be required for latency at high frequencies */
    NOP();  /* NOPs may be required for latency at high frequencies */
    /* Return data */   
    *bData = EEDATA;
    ret = E_OK;
    }
    return ret;
}