/* 
 * File:   hal_timer3.c
 * Author: m7md
 *
 * Created on 23 August 2023, 17:29
 */

#include "hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (* TMR3InterruptHandler)(void) = NULL;
#endif
static inline void Timer3_mode_select(const timer3_t *_timer);

static uint16 timer3preload = ZERO_INIT;

Std_ReturnType Timer3_Init(const timer3_t *_timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable Timer3*/
        TIMER3_MODULE_DISABLE();
        /*Prescaller configuration*/
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value);
        /* Select the mode " timer mode or counter mode " */
        Timer3_mode_select(_timer);
        /* Preloaded value*/
        TMR3H = (_timer->timer3_preloaded_vlaue) >> 8;
        TMR3L = (uint8) (_timer->timer3_preloaded_vlaue);
        timer3preload = _timer->timer3_preloaded_vlaue;
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_Interrupt_Enable();
        TIMER3_Interrupt_Flag_Clear();
        TMR3InterruptHandler = _timer->TMR3_InterruptHandler;
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER3_HighPrioritySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER3_LowPrioritySet();
        }
        else{
            /* Nothing*/
        }
            
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer3_DeInit(const timer3_t *_timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER3_MODULE_DISABLE();
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER3_Interrupt_Disable();
#endif       
    }
    return ret;
}

Std_ReturnType Timer3_Write_Value(const timer3_t *_timer,uint16 _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = (_value) >> 8;
        TMR3L = (uint8)(_value);
    }
    return ret;
}

Std_ReturnType Timer3_Read_Value(const timer3_t *_timer,uint16 *_value){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr3l = ZERO_INIT,l_tmr3h = ZERO_INIT;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        l_tmr3h = TMR3H;
        l_tmr3l = TMR3L;
        _value = (uint16)((l_tmr3h << 8) + l_tmr3l);
        ret = E_OK;
    }
    return ret;
}

static inline void Timer3_mode_select(const timer3_t *_timer){
    if(TIMER3_TIMER_MODE == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_SYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_ASYNC_COUNTER_MODE == _timer->timer3_counter_mode){
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else{
            /* Nothing*/
        }
        }
        else{
            /* Nothing*/
        }
}

void TMR3_ISR(void){
    TIMER3_Interrupt_Flag_Clear();
    TMR3H = (timer3preload) >> 8;
    TMR3L = (uint8)(timer3preload);
    if(TMR3InterruptHandler){
        TMR3InterruptHandler();
    }
}