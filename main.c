#include <stdint.h>
#include <stm32f10x.h>
#include <utils.h>
#include <spi.h>
#include <display.h>
#include <stdbool.h>
#include <ball.h>
#include <string.h>
#include <running_line.h>


int __attribute((noreturn)) main(void) {
	
	SPI_Config();
	display_config();
	
	display_clear();

	// uint8_t LCD_Buff[128];				// 1024 or 1056 causes overflow (?)
	// display_buff_init(LCD_Buff, 128);
	// LCD_Buff[5] = 0xFE;
	// repaint(LCD_Buff);

	Ball_T ball;
	base_point base = {10, 10, 1, 1};
	create_ball(&ball, base);
	
	set_start_line(0);

	while (1)
	{
		move_ball(&ball);
		//running_line();
		//draw_ball(texture_ball, 0, 0);
	}
}
