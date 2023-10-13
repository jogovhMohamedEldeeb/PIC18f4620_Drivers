 /* 
 * File:   hel_gpio.h
 * Author: m7md
 *
 * Created on 03 July 2023, 21:36
 */

#ifndef HEL_GPIO_H
#define	HEL_GPIO_H
 

/*Section : Includes */
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/*Section : Macro Declaration  */
#define BIT_MASK (uint8) 1

#define PORT_PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER 5

#define PORTC_MASK   0xFF

#define _XTAL_FREQ 8000000UL

/*Section : Macro Function Declaration  */
#define HWREG8 (_X) (*((volatile uint8 *)(_X)))

#define SET_BIT(REG,BIT_POSN)        (REG |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)      (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)     (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG,BIT_POSN)       ((REG >> BIT_POSN) & BIT_MASK)

/*Section : Data Type Declaration  */

typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,        
}pin_index_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,            
}port_index_t;

typedef struct{
    uint8 port : 3;       /*@ref port_index_t*/
    uint8 pin : 3;       /*@ref pin_index_t*/
    uint8 direction : 1;/*@ref direction_t*/
    uint8 logic : 1  ; /*@ref logic_t*/
}pin_config_t;


/*Section : Function Declaration  */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config); // to intialize  pins
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic); // to write logic in pins
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction); // to intialize  ports
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status );
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic); // to write logic in ports
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);


#endif	/* HEL_GPIO_H */

