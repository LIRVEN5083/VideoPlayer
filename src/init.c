#include "init.h"

void delay_init(void) {
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL |= (1 << 0);
}

void DMA_Init(void) {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);

    LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_3, LL_DMA_CHANNEL_3);
    LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_3, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_3, LL_DMA_PRIORITY_VERYHIGH);
    LL_DMA_SetMode(DMA2, LL_DMA_STREAM_3, LL_DMA_MODE_NORMAL);
    
    LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_3, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_3, LL_DMA_PERIPH_NOINCREMENT);

    LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_3, LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_3, LL_DMA_PDATAALIGN_BYTE);
}

void SPI1_Init(void) {
    LL_GPIO_InitTypeDef gpio_init = {0};
    LL_SPI_InitTypeDef spi_init = {0};

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

    gpio_init.Pin = PIN_SCL | PIN_SDA;
    gpio_init.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_init.Pull = LL_GPIO_PULL_NO;
    gpio_init.Alternate = LL_GPIO_AF_5; 
    LL_GPIO_Init(GPIO_PORT, &gpio_init);

    gpio_init.Pin = PIN_RST | PIN_DC | PIN_BLK;
    gpio_init.Mode = LL_GPIO_MODE_OUTPUT;
    LL_GPIO_Init(GPIO_PORT, &gpio_init);

    RST_ACTIVE();
    LL_GPIO_ResetOutputPin(GPIO_PORT, PIN_DC);
    LL_GPIO_ResetOutputPin(GPIO_PORT, PIN_BLK);
    delay(100);

    spi_init.TransferDirection = LL_SPI_FULL_DUPLEX; 
    spi_init.Mode = LL_SPI_MODE_MASTER;
    spi_init.DataWidth = LL_SPI_DATAWIDTH_8BIT; 
    spi_init.ClockPolarity = LL_SPI_POLARITY_HIGH; 
    spi_init.ClockPhase = LL_SPI_PHASE_2EDGE;     
    spi_init.NSS = LL_SPI_NSS_SOFT;                
    spi_init.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2; // 48Mhz
    spi_init.BitOrder = LL_SPI_MSB_FIRST;
    spi_init.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
    LL_SPI_Init(SPI1, &spi_init);
    
    SPI1->CR1 |= SPI_CR1_SSI; 
    LL_SPI_Enable(SPI1); 
}

void ST7789_Init(void) {
    RST_IDLE(); 
    delay(150);
    ST7789_SendCommand(0x01); // Software Reset
    delay(150);
    ST7789_SendCommand(0x11); // Sleep Out
    delay(120);

    ST7789_SendCommand(0xB0); // RAM Control
    ST7789_SendData(0x00);    
    ST7789_SendData(0xF8);    // Включает 16-битный доступ к RAM дисплея (MSB/LSB)

    ST7789_SendCommand(0x3A); // Interface Pixel Format
    ST7789_SendData(0x05);    // 0x05 = 16-bit/pixel (RGB565). Значение 0x55 избыточно, 0x05 — стандарт.

    ST7789_SendCommand(0x36); // Memory Data Access Control
    ST7789_SendData(0x00);    // Направление развертки

    // Настройка окон (240x240)
    ST7789_SendCommand(0x2A); 
    ST7789_SendData(0x00); ST7789_SendData(0x00);
    ST7789_SendData(0x00); ST7789_SendData(0xEF);

    ST7789_SendCommand(0x2B); 
    ST7789_SendData(0x00); ST7789_SendData(0x00);
    ST7789_SendData(0x00); ST7789_SendData(0xEF);

    // Разгон генератора
    ST7789_SendCommand(0xB2); // Porch Setting
    ST7789_SendData(0x0C); ST7789_SendData(0x0C);
    ST7789_SendData(0x00); ST7789_SendData(0x33); ST7789_SendData(0x33);

    ST7789_SendCommand(0xC6); // Frame Rate Control
    ST7789_SendData(0x01);    // 111 Гц

    ST7789_SendCommand(0x21); // Display Inversion On (у ST7789 цвета почти всегда инвертированы по умолчанию)
    ST7789_SendCommand(0x29); // Display On 
    delay(50);
    BLK_ON(); 
}
