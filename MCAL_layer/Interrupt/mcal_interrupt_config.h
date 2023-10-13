/* 
 * File:   mcal_interrupt_config.h
 * Author: m7md
 *
 * Created on 02 August 2023, 20:23
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

 
/************************ Includes ************************/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h"
#include "../../MCAL_layer/GPIO/hel_gpio.h"

/************************  Macro Declaration ************************/
#define INTERRUPT_ENABLE          1
#define INTERRUPT_DISABLE         0
#define INTERRUPT_OCCUR           1
#define INTERRUPT_NOT_OCCUR       0
#define INTERRUPT_PRIORITY_ENABLE 1
#define INTERRUPT_PRIORITY_ISABLE 0

/************************  Macro Function Declaration ************************/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
/* This macro will enable priority levels on interrupts. */
#define INTERRUPT_PriorityLevelsEnable()  (RCONbits.IPEN = 1)
/* This macro will disable  priority levels on interrupts. */
#define INTERRUPT_PriorityLevelsDisable() (RCONbits.IPEN = 0)

/* This macro will enable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH = 1)
/* This macro will disable high priority global interrupts. */
#define INTERRUPT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)

/* This macro will enable low priority global interrupts. */
#define INTERRUPT_GlobalInterruptLowEnable()   (INTCONbits.GIEL = 1)
/* This macro will disable low priority global interrupts. */
#define INTERRUPT_GlobalInterruptLowDisable()  (INTCONbits.GIEL = 0)
#else
/* This macro will enable global interrupts. */
#define INTERRUPT_GlobalInterruptEnable()  (INTCONbits.GIE = 1)
/* This macro will disable global interrupts. */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)
/* This macro will enable peripheral interrupts. */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
/* This macro will disable peripheral interrupts. */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)
#endif
/************************  Data Type Declaration ************************/
 
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY ,
             
}interrupt_priority_cfg;

/************************  Software interface Declaration ************************/
 

#endif	/* MCAL_INTERRUPT_CONFIG_H */

