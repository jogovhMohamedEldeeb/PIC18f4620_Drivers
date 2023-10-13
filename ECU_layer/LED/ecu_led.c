
/* 
 * File:   ecu_led.c
 * Author: m7md
 *
 * Created on 03 July 2023, 21:51
 */

#include "ecu_led.h"


/**
 * 
 * @brief intialize the assigned pin to be be OUTPUT and turn off
 * @param led : pointer to led the led module configuration 
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 * 
 */

Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret = E_OK;
    
    if(NULL == led)
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name,.pin = led->pin,
                            .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status };
        gpio_pin_intialize(&pin_obj);
    }   
    return ret;
}
/**
 * 
 * @brief Turn the led on
 * @param led : pointer to led the led module configuration 
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    
    if(NULL == led )
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name,.pin = led->pin,
                            .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status };
        gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
    }
        return ret;
}
/**
 * 
 * @brief Turn the led off
 * @param led : pointer to led the led module configuration 
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
    
    if(NULL == led )
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name,.pin = led->pin,
                            .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status };
        gpio_pin_write_logic(&pin_obj,GPIO_LOW);
    }
    return ret;
}
/**
 * 
 * @brief Toggle the led 
 * @param led : pointer to led the led module configuration 
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType led_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
    
    if(NULL == led )
    {
        ret = E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led->port_name,.pin = led->pin,
                            .direction = GPIO_DIRECTION_OUTPUT,.logic = led->led_status };
        gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}