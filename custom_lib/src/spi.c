#include <stm32f10x.h>
#include <spi.h>

#define CS_LINE_NO (4)

void SPI_select() {
	GPIOA->BSRR = (1 << CS_LINE_NO) << 16U; // reset bit
}

void SPI_deselect() {
	GPIOA->BSRR = (1 << CS_LINE_NO); //set bit
}

void SPI_Config()
{
    /** From reference manual STM32F103xx: 							 **/
	/*		SPI1_REMAP = 0 											  */
	/*		SPI1_NSS (A0) - A4 		(CS -  Chip Select)	 			  */
	/*		SPI1_SCK      - A5 		(SCK - Communication  Clock)	  */
	/*		SPI1_MISO     - A6 		(Don't used)				 	  */
	/*		SPI1_MOSI     - A7		(SI -  Serial Input)			  */

	/**	In addition:									  		 	 **/
	/*  	RSE (RESET) 		  - A2		(0 - reset, 1 - standby)  */
	/*		RS  (Register Select) - A3		(0 - cmd, 1 - data)		  */


	/** Config **/

	RCC->APB2ENR = RCC_APB2ENR_IOPAEN | RCC_APB2ENR_SPI1EN;	// Clocking enable
	AFIO->MAPR &= ~AFIO_MAPR_SPI1_REMAP;	// Set SPI1_REMAP = 0

	// RESET - MODE[00] (general function, push-pull), CNF[11] (max speed 50 MHz)
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2) | GPIO_CRL_MODE2;

	// RS - MODE[00] (general function, push-pull), CNF[11] (max speed 50 MHz)
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_CNF3 | GPIO_CRL_MODE3) | GPIO_CRL_MODE3;

	// CS - MODE[10] (alternate function, push-pull), CNF[11] (max speed 50 MHz) 
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4) | GPIO_CRL_CNF4_1 | GPIO_CRL_MODE4; // NSS

	// SCK - MODE[10] (alternate function, push-pull), CNF[11] (max speed 50 MHz)
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5) | GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5;

	// MOSI - MODE[10] (alternate function, push-pull), CNF[11] (max speed 50 MHz)
	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7) | GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7;

	SPI_deselect();

	// Bits enabled: SSM(9), SSI(8), SPE (6), BR (5:3), MSTR (2)
	SPI1->CR1 = 0x0354;						// 0b0000001101010100

	GPIOA->ODR |= GPIO_ODR_ODR2;			// Turn off RESET
}

// void SPI_Config() {
// 	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN;
// 	RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
// 	RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
// 	//PA6 -- MISO
// 	//PA7 -- MOSI
// 	//PA5 -- SCK
// 	//PA4 -- NSS
// 	//clear all modes 
// 	GPIOA->CRL = GPIOA->CRL & ~(GPIO_CRL_CNF5|GPIO_CRL_MODE5 |
// 		GPIO_CRL_CNF7|GPIO_CRL_MODE7|
// 		GPIO_CRL_CNF6|GPIO_CRL_MODE6|
// 		GPIO_CRL_CNF4|GPIO_CRL_MODE4);
// 	// set modes
// 	GPIOA->CRL |= GPIO_CRL_CNF7_1|GPIO_CRL_MODE7 |
// 		GPIO_CRL_CNF5_1|GPIO_CRL_MODE5; //alternate output push-pull 50Mhz
// 	GPIOA->CRL |= GPIO_CRL_CNF6_0; //input floating
// 	GPIOA->CRL |= GPIO_CRL_MODE4_1|GPIO_CRL_MODE4_0; // output push-pull 50Mhz
// 	SPI_deselect();
	
// 	SPI1->CR2 = 0;
// 	SPI1->CR1 = SPI_CR1_BR_2| // SPI_CR1_BR_2| // SPI_CR1_BR_0|SPI_CR1_BR_1|SPI_CR1_BR_2|
// 		SPI_CR1_SSM |
// 		SPI_CR1_SSI | SPI_CR1_MSTR;
// 	SPI1->CR1 |= SPI_CR1_CPOL|SPI_CR1_CPHA;
// }

void SPI_write(uint8_t bits)
{
	while (!(SPI1->SR & SPI_SR_TXE));
	SPI1->DR = bits;
}

void cmd(uint8_t bits)
{
	CS_LOW()
	RS_CMD()
	
	SPI_write(bits);
	while (SPI1->SR & SPI_SR_BSY);

	CS_HIGH()
}

void data(uint8_t bits)
{
    while (SPI1->SR & SPI_SR_BSY);
    CS_HIGH()
	CS_LOW()
	RS_DATA()

	SPI_write(bits);
	while (SPI1->SR & SPI_SR_BSY);

	CS_HIGH()
}