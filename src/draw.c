#include "draw.h"

void ST7789_PushBuffer(void) {
    ST7789_SendCommand(0x2C); 
    while (LL_SPI_IsActiveFlag_BSY(SPI1));
    DC_DATA();
    
    uint32_t size_bytes = 57600; 
    uint8_t* byte_buffer = (uint8_t*)frame_buffer;

    LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_3);
    LL_DMA_ClearFlag_TC3(DMA2); 
    LL_DMA_ConfigAddresses(DMA2, LL_DMA_STREAM_3, (uint32_t)byte_buffer, LL_SPI_DMA_GetRegAddr(SPI1), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_3, size_bytes); 
    LL_SPI_EnableDMAReq_TX(SPI1);
    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_3);
    while (!LL_DMA_IsActiveFlag_TC3(DMA2));

    LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_3);
    LL_DMA_ClearFlag_TC3(DMA2); 
    LL_DMA_ConfigAddresses(DMA2, LL_DMA_STREAM_3, (uint32_t)(byte_buffer + size_bytes), LL_SPI_DMA_GetRegAddr(SPI1), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_3, size_bytes); 
    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_3);
    while (!LL_DMA_IsActiveFlag_TC3(DMA2));
    
    while (LL_SPI_IsActiveFlag_BSY(SPI1));
    LL_SPI_DisableDMAReq_TX(SPI1);
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
    ST7789_PushBuffer();
}