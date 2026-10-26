#include "draw.h"

void ST7789_PushBuffer(void) {
    ST7789_SendCommand(0x2C); // RAM Write
    DC_DATA();
    
    LL_SPI_Disable(SPI1);
    LL_SPI_SetDataWidth(SPI1, LL_SPI_DATAWIDTH_16BIT);
    LL_SPI_Enable(SPI1);
    
    uint32_t total_pixels = 240 * 240;
    uint32_t i = 0;
    
    for (; i < total_pixels; i += 4) {
        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        LL_SPI_TransmitData16(SPI1, frame_buffer[i]);

        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        LL_SPI_TransmitData16(SPI1, frame_buffer[i+1]);

        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        LL_SPI_TransmitData16(SPI1, frame_buffer[i+2]);

        while (!LL_SPI_IsActiveFlag_TXE(SPI1));
        LL_SPI_TransmitData16(SPI1, frame_buffer[i+3]);
    }
    
    while (!LL_SPI_IsActiveFlag_TXE(SPI1));
    while (LL_SPI_IsActiveFlag_BSY(SPI1));
    
    LL_SPI_Disable(SPI1);
    LL_SPI_SetDataWidth(SPI1, LL_SPI_DATAWIDTH_8BIT);
    LL_SPI_Enable(SPI1);
    (void)SPI1->DR;
}

void DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if (x >= 240 || y >= 240) return;
    frame_buffer[y * 240 + x] = __builtin_bswap16(color);
}

void ClearBuffer(uint16_t color) {
    uint16_t swapped_color = __builtin_bswap16(color);
    for (uint32_t i = 0; i < 240 * 240; i++) {
        frame_buffer[i] = swapped_color;
    }
}

void Render(uint16_t color){
    ClearBuffer(color);
}