#include "init.h"
#include "draw.h"
#include "colors.h"

__attribute__((aligned(4))) uint16_t frame_buffer[240 * 240];

int main(void) {
    delay_init();
    SPI1_Init();
    ST7789_Init();

    while (1) {
        Render(COLOR_CYAN);
        Render(COLOR_MAGENTA);
    }
    return 0;
}
