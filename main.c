#include <stdint.h>
#include <stm32f10x.h>
#include <utils.h>
#include <spi.h>
#include <display.h>
#include <stdbool.h>
#include <ball.h>


int __attribute((noreturn)) main(void) {
	
	SPI_Config();
	display_config();
	
	display_clear();

	// uint8_t LCD_Buff[128];				// 1024 or 1056 causes overflow (?)
	// display_buff_init(LCD_Buff, 128);
	// LCD_Buff[5] = 0xFE;
	// repaint(LCD_Buff);
	
	uint8_t ball[] = {0x00, 0x18, 0x76, 0x62, 0xF3, 0xFF, 0x7E, 0x7E, 0x18, 0x00};

	while (1)
	{
		set_column(56);
		for (uint8_t i = 0; i < 12; i++)
		{
			data(0x00);
		}
			
		for (uint8_t i = 0; i < 56; i++)
		{
			draw_ball(ball, i, i);
			delay_us(50000);
		}

		for (uint8_t i = 0; i < 56; i++)
		{
			draw_ball(ball, 55-i, 55-i);
			delay_us(50000);
		}
		
	}


}
