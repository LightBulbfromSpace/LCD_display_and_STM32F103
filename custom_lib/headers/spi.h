#include <stm32f10x.h>

#define CS_LOW 	GPIOA->BSRR = GPIO_ODR_ODR4 << 16U;
#define CS_HIGH GPIOA->BSRR = GPIO_ODR_ODR4;
#define RESET_ON GPIOA->BSRR = GPIO_ODR_ODR2 << 16U;
#define RESET_OFF GPIOA->BSRR = GPIO_ODR_ODR4;
#define RS_CMD GPIOA->BSRR = GPIO_ODR_ODR3 << 16U;
#define RS_DATA GPIOA->BSRR = GPIO_ODR_ODR3;

void SPI_Config();
void SPI_write(uint8_t bits);
void cmd(uint8_t bits);
void data(uint8_t bits);