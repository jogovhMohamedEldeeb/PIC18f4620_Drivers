/* 
 * File:   hal_timer0.c
 * Author: m7md
 *
 * Created on 15 August 2023, 16:33
 */

#include "hal_timer0.h"


#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (* TMR0_InterruptHandler)(void) = NULL;
#endif
void TMR0_ISR(void);

static uint16 timer0_preload = ZERO_INIT;
static inline void Timer0_prescaler_config(const timer0_t *_timer);
static inline void Timer0_mode_select(const timer0_t *_timer); 
static inline void Timer0_Register_size_config(const timer0_t *_timer);


Std_ReturnType Timer0_Init(const timer0_t *_timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
        Timer0_prescaler_config(_timer);
        Timer0_mode_select(_timer);
        Timer0_Register_size_config(_timer);
        TMR0H = (_timer->timer0_preloaded_vlaue) >> 8;
        TMR0L = (uint8)(_timer->timer0_preloaded_vlaue);
        timer0_preload = _timer->timer0_preloaded_vlaue;

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_Interrupt_Enable();
        TIMER0_Interrupt_Flag_Clear();
        TMR0_InterruptHandler = _timer->TMR0_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){ 
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){ 
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet(); 
        }
        else{ /* Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
       TIMER0_MODULE_ENABLE();
       ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_DeInit(const timer0_t *_timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER0_MODULE_DISABLE();
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER0_Interrupt_Disable();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer0_Write_Value(const timer0_t *_timer,uint16 _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR0H = (_value) >> 8;
        TMR0L = (uint8)(_value);
    }
    return ret;
}

Std_ReturnType Timer0_Read_Value(const timer0_t *_timer,uint16 *_value){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr0l = ZERO_INIT,l_tmr0h = ZERO_INIT;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        l_tmr0h = TMR0H;
        l_tmr0l = TMR0L;
        _value = (uint16)((l_tmr0h << 8) + l_tmr0l);
        ret = E_OK;
    }
    return ret;
}


static inline void Timer0_prescaler_config(const timer0_t *_timer){
    if(TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_DISABLE();
    }
    else if(TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescale_value;
    }
    else{
        /* Nothing */
    }
}

static inline void Timer0_mode_select(const timer0_t *_timer){
    if(TIMER0_TIMER_MODE == _timer->timer0_mode){
        TIMER0_TIMER_MODE_ENABLE();
    }
    else if(TIMER0_COUNTER_MODE == _timer->timer0_mode){
        if(TIMER0_RISING_EDGE_ENABLE_CFG == _timer->timer0_counter_edge){
            TIMER0_RISING_EDGE_ENABLE();
        }
        else if(TIMER0_FALLING_EDGE_DISABLE_CFG == _timer->timer0_counter_edge){
            TIMER0_FALLING_EDGE_DISABLE();
        }
        else{
        /* Nothing */
        }
    }
    else{
        /* Nothing */
    }
}

static inline void Timer0_Register_size_config(const timer0_t *_timer){
    if(TIMER0_8BIT_MODE_REGIETER == _timer->timer0_register_size){
        TIMER0_8BIT_MODE_REGIETER_ENABLE();
    }
    else if(TIMER0_16BIT_MODE_REGIETER == _timer->timer0_register_size){
        TIMER0_16BIT_MODE_REGIETER_ENABLE();
    }
    else{
        /* Nothing */
    }
}
    
void TMR0_ISR(void){
    TIMER0_Interrupt_Flag_Clear();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (uint8)(timer0_preload);
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}