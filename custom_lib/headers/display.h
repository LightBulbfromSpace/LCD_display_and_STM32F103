#include <stm32f10x.h>

void display_config();
void set_page(uint8_t page_addr);
void set_column(uint8_t col_addr);
void clear();
void dspl_NOP();