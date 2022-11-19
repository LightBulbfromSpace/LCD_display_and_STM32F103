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

	//uint8_t LCD_Buff[1024];
	//display_buff_init(LCD_Buff, 1024);

	//set_pixel(1, 3, LCD_Buff);
	//set_pixel(1, 5, LCD_Buff);
	//LCD_Buff[100] = 0xA3;
	//repaint(LCD_Buff);
	set_page(0x01); //(uint8_t)((i >> 7) & 0x07)
	set_column(0x09); //(uint8_t)(i & 0x7F)
	data(0xA3);
	
	while (1)
	{
		//running_line();
		dspl_NOP();
	}


}
