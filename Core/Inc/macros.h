#pragma once

#define CS_LOW()  (GPIOB->BSRR = (1U << 6) << 16) 
#define CS_HIGH()  (GPIOB->BSRR = (1U << 6))      
#define DC_CMD()  (GPIOC->BSRR = (1U << 7) << 16)   
#define DC_DATA()  (GPIOC->BSRR = (1U << 7))      
#define RST_LOW()  (GPIOA->BSRR = (1U << 9) << 16)  /* PA9 = 0 */
#define RST_HIGH() (GPIOA->BSRR = (1U << 9))        /* PA9 = 1 */
