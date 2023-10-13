/* 
 * File:   hal_timer2.c
 * Author: m7md
 *
 * Created on 22 August 2023, 21:36
 */

#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (* TMR2InterruptHandler)(void) = NULL;
#endif

static uint16 timer2preload = ZERO_INIT;
Std_ReturnType Timer2_Init(const timer2_t *_timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TIMER2_MODULE_DISABLE();
        TIMER1_PRESCALER_SELECT(_timer->timer2_prescaler_value);
        TIMER1_POSTSCALER_SELECT(_timer->timer2_postscaler_value);
        TMR2 = _timer->timer2_preloaded_vlaue;
        timer2preload = _timer->timer2_preloaded_vlaue;
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_Interrupt_Enable();
        TIMER2_Interrupt_Flag_Clear();
        TMR2InterruptHandler = _timer->TMR2_InterruptHandler;
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
        TIMER2_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType Timer2_DeInit(const timer2_t *_timer){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        /* Disable timer1*/
        TIMER2_MODULE_DISABLE();
        /* Disable interrupt if active */
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_Interrupt_Disable();
#endif
        ret = E_OK; 
    }
    return ret;
}
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer,uint16 _value){
    Std_ReturnType ret = E_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = _value;
    }
    return ret;
}
Std_ReturnType Timer2_Read_Value(const timer2_t *_timer,uint16 *_value){
    Std_ReturnType ret = E_OK;
    if((NULL == _timer) || (NULL == _value)){
        ret = E_NOT_OK;
    }
    else{
         *_value = TMR2;
    }
    return ret;
}
 
void TMR2_ISR(void){
    TIMER2_Interrupt_Flag_Clear();
    TMR2 = timer2preload;
    if(TMR2InterruptHandler){
        TMR2InterruptHandler();
    }
}