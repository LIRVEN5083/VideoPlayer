#ifndef _DRAW_H
#define _DRAW_H

#include "core.h"
#include "commands.h"
#include "math.h"

void ST7789_PushBuffer(void);

void DrawPixel(uint16_t x, uint16_t y, uint16_t color);

void ClearBuffer(uint16_t color);

void Render(uint16_t color);

#endif