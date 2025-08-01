#include "stm32f4xx.h"   
#include "spi_low.h"
#include "macros.h"


void spi_gpio_init(void)
{
    RCC->AHB1ENR |= (1U << 0 );  // GPIOA
    RCC->AHB1ENR |= (1U << 1 );  // GPIOB
    RCC->AHB1ENR |= (1U << 2 );  // GPIOC
    RCC->APB2ENR |= (1U << 12);  // SPI1
    (void)RCC->APB2ENR;          // dummy read usualy used to unsure the clock is ready 
    GPIOB->MODER &= ~(3U << 12); // clear bit 6 GPIOB (CS- Ship select)
    GPIOB->MODER |=  (1U << 12); // set pin 6 as output GPIOB
    GPIOA->MODER &= ~(3U << 18); // clear mode bits for PA9 
    GPIOA->MODER |=  (1U << 18); // set PA9 = output 
    GPIOA->MODER &= ~(3U << 10); // clear bit 5 GIPO A (SCLK)
    GPIOA->MODER |=  (2U << 10); // set GPIOA pin5 to alternative function 
    GPIOA->MODER &= ~(3U << 14); // clear bit 7 GIPO A (MOSI)
    GPIOA->MODER |=  (2U << 14); // set GPIOA pin7 to alternative function 
    GPIOC->MODER &= ~(3U << 14);  
    GPIOC->MODER |=  (1U << 14);   
    GPIOA->AFR[0] &= ~(0xF << 20); // clear the 4-bit field for pin-5 (bits 23:20)
    GPIOA->AFR[0] |=  (5U << 20); 
    GPIOA->AFR[0] &= ~(0xF << 28); // clear the 4-bit field for PA7 (bits 31:28) 
    GPIOA->AFR[0] |=  (5U  << 28); // write 0101b → AF5 = SPI1_MOSI 
    SPI1->CR1 = 0;
    SPI1->CR1 |= (1U << 2);
    SPI1->CR1 |= (0U << 3);
    SPI1->CR1 |= (1U << 8);
    SPI1->CR1 |= (1U << 9);
    SPI1->CR1 |= (1U << 6);
    RCC->AHB1ENR |= (1U << 0);
    GPIOA->MODER &= ~(3U << (10 * 2));
    GPIOA->MODER |= (1U << (10 * 2));
    GPIOA->ODR |= (1U << 10);
  


}


void tft_write_cmd(uint8_t byte)
{
    DC_CMD();
    CS_LOW();
    *(volatile uint8_t *)&SPI1->DR = byte;
    while (!(SPI1->SR & SPI_SR_TXE));   /* wait until transmit buffer empty */
    CS_HIGH();                          /* release the chip-select */

}

void tft_write_dat(uint8_t byte)
{
    DC_DATA();                             /* data mode */
    CS_LOW();                              /* select display */
    *(volatile uint8_t *)&SPI1->DR = byte; /* start transfer */
    while (!(SPI1->SR & SPI_SR_TXE));      /* wait until DR emptied into shift register */
    while (SPI1->SR & SPI_SR_BSY);         /* wait until last bit has actually gone out */
    (void)SPI1->DR;                        /* read back dummy received byte to clear RXNE */
    CS_HIGH();                             /* deselect */
}
