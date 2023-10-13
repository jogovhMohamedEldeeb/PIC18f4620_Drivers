/* 
 * File:   hal_spi.c
 * Author: m7md
 *
 * Created on 14 September 2023, 16:05
 */


#include "hal_spi.h"
static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_config_t *Config);
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_config_t *Config);
static void MSSP_SPI_Interrupt_Init(const SPI_config_t *Config);

#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*SPI_InterruptHandler)(void) = NULL;
#endif

Std_ReturnType SPI_Init(const SPI_config_t *Config){
    Std_ReturnType ret = E_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* MSSP SPI Mode Select */
        SSPCON1bits.SSPM = Config->spi_mode;
        /* GPIO PIN Configurations */
        if((Config->spi_mode == SPI_MASTER_MODE_FOSC_DIV4) || (Config->spi_mode == SPI_MASTER_MODE_FOSC_DIV16)
                || (Config->spi_mode == SPI_MASTER_MODE_FOSC_DIV64) || (Config->spi_mode == SPI_MASTER_MODE_FOSC_TMR2)){
            MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(Config);
        }
        else if((Config->spi_mode == SPI_SLAVE_MODE_SS_ENABLE) || (Config->spi_mode == SPI_SLAVE_MODE_SS_DISABLE)){
            MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(Config);
        }
        /* Clock Polarity Select */
        SSPCON1bits.CKP = Config->spi_config.ClockPolarity;
        /* SPI Sample Select */
        SSPSTATbits.SMP = Config->spi_config.SampleSelect;
        /* SPI Clock Select */
        SSPSTATbits.CKE = Config->spi_config.ClockSelect;
        /* MSSP SPI Interrupt Configurations*/
        MSSP_SPI_Interrupt_Init(Config);
        /* Enable SPI Module */
        SPI_ENABLE_MODULE();
    }
    return ret;
}
 

Std_ReturnType SPI_DeInit(const SPI_config_t *Config){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* Interrupt Configurations */    
    }
    return ret;
}

Std_ReturnType SPI_Send_Byte(const SPI_config_t *Config, const uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF = _data;
        /* Waiting to transmit */
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF = 0;
    }
    return ret;
}

Std_ReturnType SPI_Read_Byte(const SPI_config_t *Config, uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == Config || NULL == _data){
        ret = E_NOT_OK;
    }
    else{
        /* receive not complete */
        while(SSPSTATbits.BF == 0);
        *_data = SSPBUF;
    }
    return ret;
}

Std_ReturnType SPI_Send_Byte_NonBlocking(const SPI_config_t *Config, const uint8 _data){
    Std_ReturnType ret = E_NOT_OK;
    
    if(0 == PIR1bits.SSPIF){
        SSPBUF = _data;
    }
    if(1 == PIR1bits.SSPIF){
        PIR1bits.SSPIF = 0;
    }
    
    return ret;
}

Std_ReturnType SPI_Read_Byte_NonBlocking(const SPI_config_t *Config, uint8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != _data){
        if(SSPSTATbits.BF == 1){
            *_data = SSPBUF;
            ret = E_OK;
        }
    }
    return ret;
}

static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const SPI_config_t *Config){
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX,.pin = GPIO_PIN5,.direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX,.pin = GPIO_PIN4,.direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX,.pin = GPIO_PIN3,.direction = GPIO_DIRECTION_OUTPUT};
    
    ret = gpio_pin_direction_intialize(&SPI_SDO);
    ret = gpio_pin_direction_intialize(&SPI_SDI);
    ret = gpio_pin_direction_intialize(&SPI_CLK);
    
}

static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_config_t *Config){
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX,.pin = GPIO_PIN5,.direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX,.pin = GPIO_PIN4,.direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX,.pin = GPIO_PIN3,.direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_SS = {.port = PORTA_INDEX,.pin = GPIO_PIN5,.direction = GPIO_DIRECTION_INPUT};
    
    ret = gpio_pin_direction_intialize(&SPI_SDO);
    ret = gpio_pin_direction_intialize(&SPI_SDI);
    ret = gpio_pin_direction_intialize(&SPI_CLK);
    
    if(SPI_SLAVE_MODE_SS_ENABLE == Config->spi_mode){
        ret = gpio_pin_direction_intialize(&SPI_SS);
    }
}

void MSSP_SPI_ISR(void){
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptFlagClear();
    if(SPI_InterruptHandler){
        SPI_InterruptHandler();
    }
#endif
}

static void MSSP_SPI_Interrupt_Init(const SPI_config_t *Config){
    /* Interrupt Configuration */
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    MSSP_SPI_InterruptEnable();
    MSSP_SPI_InterruptFlagClear();
    SPI_InterruptHandler = Config->MSSP_SPI_InterruptHandler;
    
    /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY == Config->priority){
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_SPI_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == Config->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_SPI_LowPrioritySet();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
#endif
#endif    
}