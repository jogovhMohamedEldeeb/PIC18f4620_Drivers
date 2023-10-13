/* 
 * File:   ecu_button.h
 * Author: m7md
 *
 * Created on 13 July 2023, 13:33
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H
 

 /************************ Includes ************************/
#include "ecu_button_cfg.h"
#include "../../MCAL_layer/GPIO/hel_gpio.h"



/************************  Macro Declaration ************************/
 

/************************  Macro Function Declaration ************************/


/************************  Data Type Declaration ************************/


/************************  Software interface Declaration ************************/

typedef enum {
    BUTTON_PASSED,
    BUTTON_RELEASED,        
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW,
}button_active_t;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;


 /************************  Software interface Declaration ************************/
/**
 * 
 * @brief Intialize the assigned pin to be Input
 * @param btn pointer to the button configurations
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType button_intialize(const button_t *btn);
/**
 * 
 * @brief read the state of the button 
 * @param btn pointer to the button configurations
 * @param btn_state button state @ref button_state_t
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);
#endif	/* ECU_BUTTON_H */

