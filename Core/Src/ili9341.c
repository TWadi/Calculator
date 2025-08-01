#include "stm32f4xx_hal.h"   // must come before using HAL_Delay
#include "ili9341.h"
#include "spi_low.h"
#include "macros.h"
#include <math.h>

/* helper: set column+row to a single pixel (address window) */
static void set_addr(uint16_t x, uint16_t y)
{
    /* Column address set: start = x, end = x */
    tft_write_cmd(0x2A);
    tft_write_dat(x >> 8);
    tft_write_dat(x);
    tft_write_dat(x >> 8);
    tft_write_dat(x);

    /* Page address set: start = y, end = y */
    tft_write_cmd(0x2B);
    tft_write_dat(y >> 8);
    tft_write_dat(y);
    tft_write_dat(y >> 8);
    tft_write_dat(y);

    /* Memory write */
    tft_write_cmd(0x2C);
}

void ili9341_init(void)
{
    spi_gpio_init();   /* set up SPI pins and peripheral */

    /* Hardware reset sequence */
    RST_HIGH();
    HAL_Delay(5);
    RST_LOW();
    HAL_Delay(10);
    RST_HIGH();
    HAL_Delay(120);

    /* Basic init commands */
    tft_write_cmd(0x11);   /* Sleep Out */
    HAL_Delay(120);

    tft_write_cmd(0x3A);   /* Pixel Format Set */
    tft_write_dat(0x55);   /* 16 bits/pixel (RGB565) */

    tft_write_cmd(0x36);   /* Memory Access Control (orientation) */
    tft_write_dat(0x48);   /* adjust if you want rotation */

    tft_write_cmd(0x29);   /* Display ON */
}

void ili9341_draw_pixel(uint16_t x, uint16_t y, uint16_t rgb565)
{
    set_addr(x, y);
    tft_write_dat(rgb565 >> 8);
    tft_write_dat(rgb565);
}

void ili9341_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    /* Column address window */
    tft_write_cmd(0x2A);
    tft_write_dat(x >> 8);
    tft_write_dat(x);
    tft_write_dat((x + w - 1) >> 8);
    tft_write_dat(x + w - 1);

    /* Page address window */
    tft_write_cmd(0x2B);
    tft_write_dat(y >> 8);
    tft_write_dat(y);
    tft_write_dat((y + h - 1) >> 8);
    tft_write_dat(y + h - 1);

    /* Memory write */
    tft_write_cmd(0x2C);
    for (uint32_t i = 0; i < (uint32_t)w * h; ++i) {
        tft_write_dat(color >> 8);
        tft_write_dat(color);
    }
}
