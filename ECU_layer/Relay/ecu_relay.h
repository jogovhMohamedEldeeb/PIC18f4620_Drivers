/* 
 * File:   ecu_relay.h
 * Author: m7md
 *
 * Created on 15 July 2023, 18:52
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H


/************************ Includes ************************/
#include "ecu_relay_cfg.h"
#include "../../MCAL_layer/GPIO/hel_gpio.h"

/************************  Macro Declaration ************************/
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U

/************************  Macro Function Declaration ************************/


/************************  Data Type Declaration ************************/
typedef struct{
    uint8 relay_port : 4;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
}relay_t;

/************************  Software interface Declaration ************************/
Std_ReturnType relay_initialize(const relay_t *relay);
Std_ReturnType relay_on(const relay_t *relay);
Std_ReturnType relay_off(const relay_t *relay);

#endif	/* ECU_RELAY_H */

