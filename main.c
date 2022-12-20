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
#include <field.h>
#include <buffer.h>


int __attribute((noreturn)) main(void) {
	
	SPI_Config();
	display_config();
	
	display_clear();

	uint8_t LCD_Buff[8][98]; // right part of screen, offset 30.

	Ball_T ball;
	base_point base_ball = {8, 10, 5, 5};
	create_ball(&ball, base_ball, 8);

	// Racket_T racket;
	// uint8_t heigth = 4;
	// uint8_t length = 15;
	// base_point base_racket = {68 - (length >> 1), heigth, 1, 1};
	// create_racket(&racket, base_racket, length, heigth);
	
	clear_buffer(LCD_Buff);
	set_frame_in_buff(LCD_Buff);
	while (1) {
		shift_ball_in_buff(&ball, LCD_Buff);
		repaint_screen(LCD_Buff);
		// draw_frame(30);
		// draw_racket(&racket);
		// move_ball(&ball);
	}
}
