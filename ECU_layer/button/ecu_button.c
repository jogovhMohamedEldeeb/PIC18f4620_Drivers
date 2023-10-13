
/* 
 * File:   ecu_button.c
 * Author: m7md
 *
 * Created on 13 July 2023, 13:33
 */

#include "ecu_button.h"
/**
 * 
 * @brief Intialize the assigned pin to be Input
 * @param btn pointer to the button configurations
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType button_intialize(const button_t *btn){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == btn){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_direction_intialize(&(btn->button_pin));
    }
    return ret;
    
}
/**
 * 
 * @brief read the state of the button 
 * @param btn pointer to the button configurations
 * @param btn_state button state @ref button_state_t
 * @return status of the function
 *      E_OK : the function done successfully
 *      E_NOT_OK : the function has issue while performing action
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_NOT_OK;
    logic_t pin_logic_status = GPIO_LOW;
    
    if((NULL == btn) || (NULL == btn_state)){
        ret = E_NOT_OK;
    }
    else{
        gpio_pin_read_logic(&(btn->button_pin),&(pin_logic_status));
        if(BUTTON_ACTIVE_HIGH == btn->button_connection){
            if(GPIO_HIGH == pin_logic_status){
                *btn_state = BUTTON_PASSED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }       
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection){
            if(GPIO_HIGH == pin_logic_status){
                *btn_state = BUTTON_RELEASED;
            }
            else{
                *btn_state = BUTTON_RELEASED;
            }
        }
        else{
            /* Nothing */
        }
    }
    return ret;
}
