#include <stdint.h>
#include <utils.h>
#include <spi.h>
#include <display.h>
#include <examples.h>
#include <stm32f10x.h>
#include <stdbool.h>


int __attribute((noreturn)) main(void) {
	
	SPI_Config();
	display_config();
	
	display_clear();

	//uint8_t LCD_Buff[] = display_buff_init(1024);

	while (1)
	{
		running_line();
	}


}
