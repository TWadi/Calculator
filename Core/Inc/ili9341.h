#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Display geometry
#define ILI9341_WIDTH  240
#define ILI9341_HEIGHT 320

// Some handy pre-defined colors (RGB565)
#define ILI9341_COLOR_BLACK   0x0000
#define ILI9341_COLOR_WHITE   0xFFFF
#define ILI9341_COLOR_RED     0xF800
#define ILI9341_COLOR_GREEN   0x07E0
#define ILI9341_COLOR_BLUE    0x001F
#define ILI9341_COLOR_YELLOW  0xFFE0
#define ILI9341_COLOR_CYAN    0x07FF
#define ILI9341_COLOR_MAGENTA 0xF81F
#define ILI9341_COLOR_ORANGE  0xFD20  // approximate

/** Initialize the ILI9341 display (reset, configuration, display on). */
void ili9341_init(void);

/** Draw a single pixel in RGB565 format. */
void ili9341_draw_pixel(uint16_t x, uint16_t y, uint16_t rgb565);

/** Fill a rectangle region with a given RGB565 color. */
void ili9341_fill_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void draw_scene(void);
/** Fill entire screen with a given RGB565 color. */
static inline void ili9341_fill_screen(uint16_t color)
{
    ili9341_fill_rect(0, 0, ILI9341_WIDTH, ILI9341_HEIGHT, color);
}

/** Convert 24-bit RGB to 16-bit RGB565 packed format. */
static inline uint16_t ili9341_color565(uint8_t r, uint8_t g, uint8_t b)
{
    return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

#ifdef __cplusplus
}
#endif
