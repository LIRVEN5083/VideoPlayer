#ifndef _INIT_H
#define _INIT_H

#include "core.h"
#include "commands.h"

void delay_init(void);

// TODO: ST7789 init
void SPI1_Init(void);
void ST7789_Init(void);

#endif