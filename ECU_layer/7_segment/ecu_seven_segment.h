/* 
 * File:   ecu_seven_segment.h
 * Author: m7md
 *
 * Created on 18 July 2023, 01:27
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/************************ Includes ************************/
#include "ecu_seven_segment_cfg.h"
#include "../../MCAL_layer/GPIO/hel_gpio.h"

/************************  Macro Declaration ************************/
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

/************************  Macro Function Declaration ************************/


/************************  Data Type Declaration ************************/
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE   
} segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
segment_type_t segment_type;
}segment_t;

/************************  Software interface Declaration ************************/
Std_ReturnType seven_segment_initialize(const segment_t *seg);
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */

