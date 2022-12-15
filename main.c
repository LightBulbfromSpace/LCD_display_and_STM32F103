#include <stdint.h>
#include <stm32f10x.h>
#include <utils.h>
#include <spi.h>
#include <display.h>
#include <stdbool.h>
#include <ball.h>
#include <string.h>
#include <running_line.h>
#include <racket.h>


int __attribute((noreturn)) main(void) {
	
	SPI_Config();
	display_config();
	
	display_clear();

	// uint8_t LCD_Buff[128];				// 1024 or 1056 causes overflow (?)
	// display_buff_init(LCD_Buff, 128);
	// LCD_Buff[5] = 0xFE;
	// repaint(LCD_Buff);

	Ball_T ball;
	Racket_T racket;
	base_point base = {10, 15, 5, 5};
	base_point base2 = {10, 10, 1, 1};
	create_racket(&racket, base2, 10, 5);
	create_ball(&ball, base);
	draw_racket(&racket);
	while (1) {
		move_ball(&ball);
	}
}
