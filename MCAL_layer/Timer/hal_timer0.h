/* 
 * File:   hal_timer0.h
 * Author: m7md
 *
 * Created on 15 August 2023, 16:33
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* ----------------- Includes -----------------*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hel_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"


/* ----------------- Macro Declarations -----------------*/
#define TIMER0_PRESCALER_ENABLE_CFG         1
#define TIMER0_PRESCALER_DISABLE_CFG        0

#define TIMER0_RISING_EDGE_ENABLE_CFG       1
#define TIMER0_FALLING_EDGE_DISABLE_CFG     0

#define TIMER0_TIMER_MODE                   1
#define TIMER0_COUNTER_MODE                 0

#define TIMER0_8BIT_MODE_REGIETER           1
#define TIMER0_16BIT_MODE_REGIETER          0

/* ----------------- Macro Functions Declarations -----------------*/
#define TIMER0_PRESCALER_ENABLE()               (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE()              (T0CONbits.PSA = 1)

#define TIMER0_RISING_EDGE_ENABLE()             (T0CONbits.T0SE = 1)
#define TIMER0_FALLING_EDGE_DISABLE()            (T0CONbits.T0SE = 0)

#define TIMER0_TIMER_MODE_ENABLE()              (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()            (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_MODE_REGIETER_ENABLE()      (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_MODE_REGIETER_ENABLE()     (T0CONbits.T08BIT = 0)

#define TIMER0_MODULE_ENABLE()                  (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()                (T0CONbits.TMR0ON = 0)

/* ----------------- Data Type Declarations -----------------*/
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,         
}timer0_prescaler_Select_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TMR0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    timer0_prescaler_Select_t prescale_value;
    uint16 timer0_preloaded_vlaue;
    uint8 timer0_reserved : 4;
    uint8 prescaler_enable : 1;
    uint8 timer0_mode : 1;
    uint8 timer0_counter_edge : 1;
    uint8 timer0_register_size : 1;
}timer0_t;
/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType Timer0_Init(const timer0_t *_timer);
Std_ReturnType Timer0_DeInit(const timer0_t *_timer);
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer,uint16 _value);
Std_ReturnType Timer0_Read_Value(const timer0_t *_timer,uint16 *_value);

#endif	/* HAL_TIMER0_H */

