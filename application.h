/* 
 * File:   application.h
 * Author: m7md
 *
 * Created on 03 July 2023, 21:56
 */

#ifndef APPLICATION_H
#define	APPLICATION_H



/************************ Includes ************************/
#include "MCAL_layer/GPIO/hel_gpio.h"
#include "ECU_layer/LED/ecu_led.h"
#include "ECU_layer/button/ecu_button.h"
#include "ECU_layer/Relay/ecu_relay.h"
#include "ECU_layer/DC_Motor/ecu_dc_motor.h"
#include "ECU_layer/7_segment/ecu_seven_segment.h"
#include "ECU_layer/KeyPad/ecu_keypad.h"
#include "ECU_layer/Chr_LCD/ecu_chr_lcd.h"
#include "MCAL_layer/Interrupt/mcal_external_interrupt.h"
#include "ECU_layer/ecu_layer_init.h"
#include "MCAL_layer/EEPROM/hal_eeprom.h"
#include "MCAL_layer/ADC/hal_adc.h"
#include "MCAL_layer/Timer/hal_timer0.h"
#include "MCAL_layer/Timer1/hal_timer1.h"
#include "MCAL_layer/Timer2/hal_timer2.h"
#include "MCAL_layer/Timer3/hal_timer3.h"
#include "MCAL_layer/CCP1/hal_ccp1.h"
#include "MCAL_layer/usart/hal_usart.h"
#include "MCAL_layer/SPI/hal_spi.h"
#include "MCAL_layer/I2C/hal_i2c.h"

/************************  Macro Declaration ************************/
 

/************************  Macro Function Declaration ************************/


/************************  Data Type Declaration ************************/


/************************  Software interface Declaration ************************/


void application_intialize(void); 


#endif	/* APPLICATION_H */

