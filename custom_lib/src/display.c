#include <stm32f10x.h>
#include <display.h>
#include <spi.h>

void set_page(uint8_t page_addr)
{
    page_addr &= 0x07;
    cmd(0xB0 | page_addr);
}

void set_column(uint8_t col_addr)
{
    cmd(col_addr & 0x0F);
	cmd(0x10 | (col_addr >> 4));
}