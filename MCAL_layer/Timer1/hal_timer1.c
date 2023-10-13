/* 
 * File:   hal_timer1.c
 * Author: m7md
 *
 * Created on 20 August 2023, 17:59
 */

#include "hal_timer1.h"

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (* TMR1InterruptHandler)(void) = NULL;
#endif

static uint16 timer1preload = ZERO_INIT;
static inline void Timer1_mode_select(const timer1_t *_timer);
void TMR1_ISR(void);

Std_ReturnType Timer1_Init(const timer1_t *_timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable timer1*/
        TIMER1_MODULE_DISABLE();
        /* Prescaller Select Configuration*/
        TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler_value);
        /* Select the mode "timer mode or counter mode"   */
        Timer1_mode_select(_timer);
        /* Preloaded value*/
        TMR1H = (_timer->timer1_preloaded_vlaue) >> 8;
        TMR1L = (uint8)(_timer->timer1_preloaded_vlaue);
        timer1preload = _timer->timer1_preloaded_vlaue;
        /* Interrupt Configuration */
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_Interrupt_Enable();
        TIMER1_Interrupt_Flag_Clear();
        TMR1InterruptHandler = _timer->TMR1_InterruptHandler;
        /* Interrupt Priority Configuration */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(INTERRUPT_HIGH_PRIORITY == _timer->priority){ 
            /* Enable all high priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER1_HighPrioritySet(); 
        }
        else if(INTERRUPT_LOW_PRIORITY == _timer->priority){ 
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER1_LowPrioritySet(); 
        }
        else{ /* Nothing */ }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
#endif
        /* Enable timer1*/
        TIMER1_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer1_DeInit(const timer1_t *_timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable timer1*/
        TIMER1_MODULE_DISABLE();
        /* Disable interrupt if active */
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER1_Interrupt_Disable();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType Timer1_Write_Value(const timer1_t *_timer,uint16 _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR1H = (_value) >> 8;
        TMR1L = (uint8)(_value);
    }
    return ret;
}

Std_ReturnType Timer1_Read_Value(const timer1_t *_timer,uint16 *_value){
    Std_ReturnType ret = E_OK;
    uint8 l_tmr1l = ZERO_INIT,l_tmr1h = ZERO_INIT;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
        l_tmr1h = TMR1H;
        l_tmr1l = TMR1L;
        _value = (uint16)((l_tmr1h << 8) + l_tmr1l);
        ret = E_OK;
    }
    return ret;
}

static inline void Timer1_mode_select(const timer1_t *_timer){
    if(TIMER1_TIMER_MODE == _timer->timer1_mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode){
        TIMER1_COUNTER_MODE_ENABLE();
        if(TIMER1_SYNC_COUNTER_MODE == _timer->timer1_counter_mode){
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_ASYNC_COUNTER_MODE == _timer->timer1_counter_mode){
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else{
        /* Nothing */
        }
    }
    else{
        /* Nothing */
    }
}

void TMR1_ISR(void){
    TIMER1_Interrupt_Flag_Clear();
    TMR1H = (timer1preload) >> 8;
    TMR1L = (uint8)(timer1preload);
    if(TMR1InterruptHandler){
        TMR1InterruptHandler();
    }
}