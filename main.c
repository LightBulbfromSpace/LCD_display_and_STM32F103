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

	uint8_t LCD_Buff[132];				// 1024 causes overflow (?)
	display_buff_init(LCD_Buff, 132);

	LCD_Buff[4] = 0xAF;
	repaint(LCD_Buff);
	
	while (1)
	{
		//running_line();
		dspl_NOP();
	}


}
