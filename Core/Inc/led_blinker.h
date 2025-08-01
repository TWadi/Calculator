#include <stm32f4xx.h>          /* brings in RCC, GPIOA symbols */
#include "stm32f4xx_hal.h"


/* crude blocking delay ≈ n × 1 ms when SYSCLK = 16 MHz HSI */
void delay_ms(uint16_t n);
void blink();