#include <stdint.h>
#include <utils.h>
#include <spi.h>
#include <display.h>
#include <stm32f10x.h>
#include <stdbool.h>


int __attribute((noreturn)) main(void) {

	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH = GPIOC->CRH & ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13) | GPIO_CRH_MODE13_0;

	SPI_Config();

	CS_LOW
	RESET_ON
	delay(10000);
	RESET_OFF
	delay(1000);

	cmd(0xA2);		// LCD drive voltage bias ratio: 1/9 bias
	cmd(0xA0);		// RAM address and SEG output correspondence (ADC selection)
	cmd(0xC0);		// Common output mode selection (normal)
	cmd(0x81);		// Electronic volume mode set
	cmd(0x07);		// Electronic register set (elect. volume value = 0x07 - middle)
	cmd(0x24);		// Voltage regulator internal resistor ratio set
	cmd(0x2F);		// Power control set (ratio = 0.5)
	cmd(0xA6);		// LCD display normal color
	cmd(0x40);		// Set start line
	
	
	cmd(0xAF);		// Display ON
	

	// set_page(0x01);
	// set_column(0x01);
	// data(0xA3);
	
	cmd(0xA4);
	GPIOC->ODR |= GPIO_ODR_ODR13;

	while (1)
	{
		cmd(0xE3);  // nop();
	}


}
