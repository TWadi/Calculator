#include "led_blinker.h"


void blink(){
 /* 1. Enable GPIO-A clock — RCC_AHB1ENR, bit 0 (GPIOAEN)  */
    RCC->AHB1ENR = 0x00000001;                        /*﻿:contentReference[oaicite:0]{index=0} */

    /* 2. PA10 → general-purpose output (MODER bits 21:20 = 01) */
    GPIOA->MODER &= ~(3 << 20);  /* clear both bits first  */   /*﻿:contentReference[oaicite:1]{index=1} */
    GPIOA->MODER |=  (1 << 20);  /* set bit 20 => output   */

    while (1)
    {
        /* 3. drive PA10 HIGH, wait, then LOW — ODR bit 10    */
        GPIOA->ODR |=  (1 << 10);                           /*﻿:contentReference[oaicite:2]{index=2} */
        delay_ms(500);
      //  GPIOA->ODR &= ~(1 << 10);
      //  delay_ms(500);
    }
}

/*------------------------------------------------------------*/
void delay_ms(uint16_t n)
{
    volatile int i;
    for (; n > 0; n--)                /* outer loop = ms count      */
        for (i = 0; i < 1600; i++)    /* inner loop ≈ 1 ms at 16 MHz */
            ;                         /* (tweak if you change HCLK) */
}