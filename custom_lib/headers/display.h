#include <stm32f10x.h>

void display_config();
void set_page(uint8_t page_addr);
void set_column(uint8_t col_addr);
void display_clear();
void dspl_NOP();
uint8_t display_buff_init(uint8_t size);