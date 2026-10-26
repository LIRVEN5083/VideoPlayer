#include "commands.h"

void SPI_WriteByte8(uint8_t data) {
    while (!LL_SPI_IsActiveFlag_TXE(SPI1)); 
    LL_SPI_TransmitData8(SPI1, data);       
    while (LL_SPI_IsActiveFlag_BSY(SPI1));  
    (void)SPI1->DR; 
}

void ST7789_SendCommand(uint8_t cmd) {
    DC_CMD();
    SPI_WriteByte8(cmd);
}

void ST7789_SendData(uint8_t data) {
    DC_DATA();
    SPI_WriteByte8(data);
}

void delay_us(uint32_t us) {
    uint32_t start_tick = DWT->CYCCNT;
    uint32_t delay_ticks = us * (SystemCoreClock / 1000000U);
    
    while ((DWT->CYCCNT - start_tick) < delay_ticks);
}

void delay(uint32_t ms) {
    while (ms--) {
        delay_us(1000);
    }
}