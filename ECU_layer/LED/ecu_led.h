/* 
 * File:   ecu_led.h
 * Author: m7md
 *
 * Created on 03 July 2023, 21:51
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
 


/*Section : Includes */
#include "../../MCAL_layer/GPIO/hel_gpio.h"
#include "ecu_led_cfg.h"
/*Section : Includes */
/*Section : Macro Declaration  */
 

/*Section : Macro Function Declaration  */


/*Section : Data Type Declaration  */
typedef enum{
    LED_OFF,
    LED_ON,          
}led_status_t;

typedef struct{
    uint8 port_name : 4;
    uint8 pin : 3;
    uint8 led_status : 1;
}led_t;


/*Section : Function Declaration  */
 
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);

#endif	/* ECU_LED_H */

