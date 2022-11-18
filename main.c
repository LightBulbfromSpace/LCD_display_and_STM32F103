#include <stdint.h>
#include <utils.h>
#include <spi.h>
#include <display.h>
#include <stm32f10x.h>
#include <stdbool.h>


int __attribute((noreturn)) main(void) {
	
	SPI_Config();
	
	display_config();
	
	clear();

	//for (uint8_t j = 0; j < 4; j++)
	//{
		// set_page(0x00);
		// for (uint8_t i = 0; i < 150; i++)
		// data(0xFF);
	//}

	while (1)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			set_page(j);
			set_column(0x00);
			for (uint8_t i = 0; i < 128; i++)
			{
				data(0xFF);
				delay_us(10000);
			}
			set_column(0x00);
			for (uint8_t i = 0; i < 128; i++)
			{
				data(0x00);
				delay_us(10000);
			}
		}
	}


}
