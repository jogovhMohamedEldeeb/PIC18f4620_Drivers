 
/* 
 * File:   hal_gpio.c
 * Author: m7md
 *
 * Created on 03 July 2023, 21:19
 */


#include "hel_gpio.h"

/* References to the data direction control registers */
volatile uint8 *tris_regiters[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/* References to the data  latch register (read and write to Data Latch */
volatile uint8 *lat_regiters[]  = {&LATA, &LATB, &LATC, &LATD, &LATE};
/* References to the port status registers */
volatile uint8 *port_regiters[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/**
 * @brief Intialize the direction of a specific pin @ref direction_t
 * @param _pin_config pointer to the configurations @ref pin_config_t
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE 
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER - 1){
        ret = E_NOT_OK;
    }
    else{
        switch(_pin_config->direction)
         {
            case GPIO_DIRECTION_OUTPUT : 
                CLEAR_BIT(*tris_regiters[_pin_config->port],_pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_regiters[_pin_config->port],_pin_config->pin);
                break;
            default : ret = E_NOT_OK;
         }
        }
    
    return ret;
} 
#endif
/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t
 * @param dic_status
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE 
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status){
   Std_ReturnType ret = E_OK;
   if(NULL == _pin_config|| NULL == direction_status || _pin_config->pin > PORT_PIN_MAX_NUMBER - 1){
       ret = E_NOT_OK;
   }
   else{
      *direction_status =  READ_BIT(*tris_regiters[_pin_config->port],_pin_config->pin);
   }
   return ret;
} 
#endif
/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t
 * @param logic
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE 
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic){ 
     Std_ReturnType ret = E_OK;
     
     if(NULL == _pin_config || _pin_config->logic > PORT_PIN_MAX_NUMBER - 1){
         ret = E_NOT_OK;
     }
     else{
         switch(logic){
             case GPIO_LOW:
                 CLEAR_BIT(*lat_regiters[_pin_config->port],_pin_config->pin);
                 break;
             case GPIO_HIGH:
                 SET_BIT(*lat_regiters[_pin_config->port],_pin_config->pin);
                 break;
             default : ret = E_NOT_OK ;             
         }
     }
      
     return ret;
} 
#endif
/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t
 * @param logic
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE 
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic){
   Std_ReturnType ret = E_OK;
   
   if(NULL == _pin_config|| NULL == logic || _pin_config->pin > PORT_PIN_MAX_NUMBER - 1){
       ret = E_NOT_OK;
   }
   else{
      *logic =  READ_BIT(*tris_regiters[_pin_config->port],_pin_config->pin);
   }
   return ret; 
} 
#endif
/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE 
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config){
     Std_ReturnType ret = E_OK;
     
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER - 1){
         ret = E_NOT_OK;
     }
     else{
         TOGGLE_BIT(*lat_regiters[_pin_config->port],_pin_config->pin);
     }

     return ret;    
} 
/**
 * 
 * @param _pin_config pointer to the configurations @ref pin_config_t
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#endif
#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE 
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config){
     Std_ReturnType ret = E_OK;
     
     if(NULL == _pin_config){
         ret = E_NOT_OK;
     }
     else{
         gpio_pin_direction_intialize(_pin_config);
         gpio_pin_write_logic(_pin_config,_pin_config->logic);
     }
         
     return ret;  
}
#endif
/**
 * 
 * @param port
 * @param direction
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction){
     Std_ReturnType ret = E_OK;
     if(port > PORT_MAX_NUMBER-1){
         ret = E_NOT_OK;
     }
     else{
         *tris_regiters[port] = direction;
     }
     return ret;    
}
#endif
/**
 * 
 * @param port
 * @param direction_status
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status ){
     Std_ReturnType ret = E_OK;
     if(NULL == direction_status && port > PORT_MAX_NUMBER-1){
         ret = E_NOT_OK;
     }
     else{
         *direction_status = *tris_regiters[port];
     }
     
     return ret;    
} 
#endif
/**
 * 
 * @param port
 * @param logic
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic){
     Std_ReturnType ret = E_OK;
     
     if(port > PORT_MAX_NUMBER-1){
      ret = E_NOT_OK;   
     }
     else{
        *lat_regiters[port] = logic; 
     }
     
     return ret;    
} 
#endif
/**
 * 
 * @param port
 * @param logic
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic){
     Std_ReturnType ret = E_OK;
     
     if(port > PORT_MAX_NUMBER-1 && NULL == logic){
        ret = E_NOT_OK;   
     }
     else{
        *logic = *lat_regiters[port]; 
     }
     return ret;  
} 
#endif
/**
 * 
 * @param port
 * @return Status of the function 
 *              (E_OK) : the function done successfully
 *              (E_NOT_OK) : the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION==CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
     Std_ReturnType ret = E_OK;
     
     if(port > PORT_MAX_NUMBER-1){
       ret = E_NOT_OK;   
     }
     else{
           *lat_regiters[port] ^= PORTC_MASK;
     }
     
     return ret;    
}
#endif