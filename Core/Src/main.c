#include "stm32f4xx_hal.h"
#include "ili9341.h"
#include "calculator_ui.h"

int main(void)
{
    HAL_Init();
    ili9341_init();

    draw_calculator();

    while (1) { }
}
