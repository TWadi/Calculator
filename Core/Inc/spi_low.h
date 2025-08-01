#pragma once
#include <stdint.h>

void spi_gpio_init(void);
void tft_write_cmd(uint8_t byte);
void tft_write_dat(uint8_t byte);
