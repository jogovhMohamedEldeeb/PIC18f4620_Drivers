/* 
 * File:   hal_timer2.h
 * Author: m7md
 *
 * Created on 22 August 2023, 21:36
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H
 
/* ----------------- Includes -----------------*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hel_gpio.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/ 
#define TIMER2_PostSCALER_DIV_BY_1           0
#define TIMER2_PostSCALER_DIV_BY_2           1
#define TIMER2_PostSCALER_DIV_BY_3           2
#define TIMER2_PostSCALER_DIV_BY_4           3
#define TIMER2_PostSCALER_DIV_BY_5           4
#define TIMER2_PostSCALER_DIV_BY_6           5
#define TIMER2_PostSCALER_DIV_BY_7           6
#define TIMER2_PostSCALER_DIV_BY_8           7
#define TIMER2_PostSCALER_DIV_BY_9           8
#define TIMER2_PostSCALER_DIV_BY_10          9
#define TIMER2_PostSCALER_DIV_BY_11          10
#define TIMER2_PostSCALER_DIV_BY_12          11
#define TIMER2_PostSCALER_DIV_BY_13          12
#define TIMER2_PostSCALER_DIV_BY_14          13
#define TIMER2_PostSCALER_DIV_BY_15          14
#define TIMER2_PostSCALER_DIV_BY_16          15


#define TIMER2_PRESCALER_DIV_BY_1           0
#define TIMER2_PRESCALER_DIV_BY_4           1    
#define TIMER2_PRESCALER_DIV_BY_16          2

/* ----------------- Macro Functions Declarations -----------------*/
#define TIMER2_MODULE_ENABLE()                  (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()                 (T2CONbits.TMR2ON = 0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_)    (T2CONbits.T2CKPS = _PRESCALER_)

#define TIMER1_POSTSCALER_SELECT(_POSTSCALER_)  (T2CONbits.TOUTPS = _POSTSCALER_)
/* ----------------- Data Type Declarations -----------------*/
 typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TMR2_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 timer2_preloaded_vlaue;
    uint8 timer2_prescaler_value : 2;
    uint8 timer2_postscaler_value :4;
    uint8 timer2_reserved : 2;
}timer2_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer,uint16 _value);
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer,uint16 *_value);
 
#endif	/* HAL_TIMER2_H */

