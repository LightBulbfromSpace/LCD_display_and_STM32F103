#include <stm32f10x.h>
#include <spi.h>

// todo: remap ability

void SPI_Config()
{
    	/** From reference manual STM32F103xx: 				**/
	/*	SPI1_REMAP = 0 										 */
	/*	SPI1_NSS (A0) - A4 		(CS -  Chip Select)	 		 */
	/*	SPI1_SCK      - A5 		(SCK - Communication  Clock) */
	/*	SPI1_MISO     - A6 		(Don't used)				 */
	/*	SPI1_MOSI     - A7		(SI -  Serial Input)		 */

	/**	In addition:									  		 **/
	/*  RSE (RESET) 		  - A2		(0 - reset, 1 - standby)  */
	/*	RS  (Register Select) - A3		(0 - cmd, 1 - data)		  */

	/** Config **/
	RCC->APB2ENR = RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_SPI1EN;	// Clocking enable
	AFIO->MAPR &= ~AFIO_MAPR_SPI1_REMAP;	// Set SPI1_REMAP = 0

	GPIOA->CRL = GPIOA->CRL & (GPIO_CRL_CNF4 | GPIO_CRL_MODE4) | GPIO_CRL_CNF4_1 | GPIO_CRL_MODE4_0; // NSS

	// SCK - alternative function, push-pull, max speed 10 MHz 
	GPIOA->CRL = GPIOA->CRL & (GPIO_CRL_CNF5 | GPIO_CRL_MODE5) | GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_0;

	// MOSI - alternative function, push-pull, max speed 10 MHz 
	GPIOA->CRL = GPIOA->CRL & (GPIO_CRL_CNF7 | GPIO_CRL_MODE7) | GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_0;
	
	SPI1->CR1 &= ~SPI_CR1_CPOL;				// CPOL (Clock polarity) = 0 (low when idle)
	SPI1->CR1 &= ~SPI_CR1_CPHA;				// CPHA (Clock phase) = 0 (capture MSB by the first edge)
	SPI1->CR1 |= SPI_CR1_BR_1;				// Baud rate = Fpclk / 8
 	SPI1->CR1 |= SPI_CR1_MSTR;				// Master mode

	SPI1->CR1 |= SPI_CR1_SPE;
}

void cmd(uint8_t bits)
{
	GPIOA->BSRR = GPIO_ODR_ODR4 << 16U;

	SPI1->DR = bits;
	while (SPI1->SR & SPI_SR_BSY);
	
	GPIOA->BSRR = GPIO_ODR_ODR4;
}

void data(uint8_t bits)
{
	cmd(bits & 0x0F);
	cmd(0x10 | (bits >> 4));

	while (SPI1->SR & SPI_SR_BSY);
}