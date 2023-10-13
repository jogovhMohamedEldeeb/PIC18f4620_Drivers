/* 
 * File:   ecu_relay.h
 * Author: m7md
 *
 * Created on 15 July 2023, 18:52
 */

#include "ecu_relay.h"

/**
 * 
 * @brief intialize the assigned pin to be be OUTPUT and turn the relay OFF or NO
 * @param relay : pointer to the relay module configuration 
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 * 
 */
Std_ReturnType relay_initialize(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if(NULL == relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = { .port = relay->relay_port, .pin = relay->relay_pin,
                .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status};
        gpio_pin_intialize(&pin_obj);
    }
    return ret;          
}

/**
 * 
 * @brief Turn the relay ON
 * @param relay : pointer to the relay module configuration 
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 * 
 */
Std_ReturnType relay_on(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if(NULL == relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = { .port = relay->relay_port, .pin = relay->relay_pin,
                .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status};
        gpio_pin_write_logic(&pin_obj,GPIO_HIGH);;
    }
    return ret;  
}
/**
 * 
 * @brief Turn the relay OFF
 * @param relay : pointer to the relay module configuration 
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 * 
 */

Std_ReturnType relay_off(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    if(NULL == relay){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = { .port = relay->relay_port, .pin = relay->relay_pin,
                .direction = GPIO_DIRECTION_OUTPUT, .logic = relay->relay_status};
         gpio_pin_write_logic(&pin_obj,GPIO_LOW);
    }
    return ret;  
}