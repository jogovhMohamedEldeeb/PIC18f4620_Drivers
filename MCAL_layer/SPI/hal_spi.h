/* 
 * File:   hal_spi.h
 * Author: m7md
 *
 * Created on 14 September 2023, 16:05
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/* ----------------- Includes -----------------*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/hel_gpio.h"
#include "../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/ 

/* SPI Buffer Full Status*/
#define SPI_BUFFER_FULL_RECEIVE_COMPLETE        1
#define SPI_BUFFER_FULL_RECEIVE_NOT_COMPLETE    0

/* SPI Clock Select  */
#define SPI_CLOCK_SELECT_ACTIVE_TO_IDLE     1
#define SPI_CLOCK_SELECT_IDLE_TO_ACTIVE     0

/* SPI Sample bit  */
#define SPI_DATA_SAMPLR_END     1
#define SPI_DATA_SAMPLR_MIDDLE  0

/* Synchronous Serial Port Mode Select */
#define SPI_MASTER_MODE_FOSC_DIV4    0
#define SPI_MASTER_MODE_FOSC_DIV16   1
#define SPI_MASTER_MODE_FOSC_DIV64   2
#define SPI_MASTER_MODE_FOSC_TMR2    3
#define SPI_SLAVE_MODE_SS_ENABLE     4
#define SPI_SLAVE_MODE_SS_DISABLE    5

/* Receive Overflow Indicator */
#define SPI_SLAVE_RECEIVE_OVERFLOW_DETECT       1
#define SPI_SLAVE_RECEIVE_OVERFLOW_NOT_DETECT   0

/* Write Collision Detect */
#define SPI_WRITE_COLLISION_DETECT      1
#define SPI_WRITE_COLLISION_NOT_DETECT  0

/* Clock Polarity Select  */
#define SPI_DATA_STATE_HIGH_LEVEL   1
#define SPI_DATA_STATE_LOE_LEVEL    0


/* ----------------- Macro Functions Declarations -----------------*/
#define SPI_ENABLE_MODULE()         (SSPCON1bits.SSPEN = 1)
#define SPI_DISABLE_MODULE()        (SSPCON1bits.SSPEN = 0)
 
/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    uint8 ClockPolarity : 2;
    uint8 SampleSelect  : 2;
    uint8 ClockSelect   : 2;
    uint8 Reserved      : 2;
}SPI_Control_config; 

typedef struct{
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* MSSP_SPI_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint8 spi_mode;
    SPI_Control_config spi_config;
}SPI_config_t; 

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType SPI_Init(const SPI_config_t *Config);
Std_ReturnType SPI_DeInit(const SPI_config_t *Config);
Std_ReturnType SPI_Send_Byte(const SPI_config_t *Config, const uint8 _data);
Std_ReturnType SPI_Read_Byte(const SPI_config_t *Config, uint8 *_data);
Std_ReturnType SPI_Send_Byte_NonBlocking(const SPI_config_t *Config, const uint8 _data);
Std_ReturnType SPI_Read_Byte_NonBlocking(const SPI_config_t *Config, uint8 *_data);

#endif	/* HAL_SPI_H */

