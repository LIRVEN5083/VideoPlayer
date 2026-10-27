#ifndef _CORE_H
#define _CORE_H

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_adc.h"
#include "stm32f4xx_ll_dma.h"
#include <stdlib.h>

#define GPIO_PORT       GPIOA
#define PIN_RST         LL_GPIO_PIN_0 // PA0 Reset
#define PIN_DC          LL_GPIO_PIN_1 // PA1 Command
#define PIN_BLK         LL_GPIO_PIN_2 // PA2 Light

#define PIN_SCL         LL_GPIO_PIN_5  // PA5 SCL
#define PIN_SDA         LL_GPIO_PIN_7  // PA7 SDA

#define DC_CMD()        { while(LL_SPI_IsActiveFlag_BSY(SPI1)); LL_GPIO_ResetOutputPin(GPIO_PORT, PIN_DC); }
#define DC_DATA()       { while(LL_SPI_IsActiveFlag_BSY(SPI1)); LL_GPIO_SetOutputPin(GPIO_PORT, PIN_DC); }

#define RST_ACTIVE()    LL_GPIO_ResetOutputPin(GPIO_PORT, PIN_RST)
#define RST_IDLE()      LL_GPIO_SetOutputPin(GPIO_PORT, PIN_RST)
#define BLK_ON()        LL_GPIO_SetOutputPin(GPIO_PORT, PIN_BLK)

extern __attribute__((aligned(4))) uint16_t frame_buffer[240 * 240];

#endif