#include <stm32f10x.h>

void display_config();
void set_page(uint8_t page_addr);
void set_column(uint8_t col_addr);
void display_clear();
void dspl_NOP();
void display_buff_init(uint8_t buff[], uint16_t size);
void set_pixel(uint8_t x, uint8_t y, uint8_t LCD_Buff[]);
void repaint(uint8_t LCD_Buff[]);