#ifndef _COMMANDS_H
#define _COMMANDS_H

#include "core.h"

//TODO: Base commands for Display
void SPI_WriteByte8(uint8_t data);
void ST7789_SendCommand(uint8_t cmd);
void ST7789_SendData(uint8_t data);

//TODO: Base delay
void delay_us(uint32_t us);
void delay(uint32_t ms);

#endif