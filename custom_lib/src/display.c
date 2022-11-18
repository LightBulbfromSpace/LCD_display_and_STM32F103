#include <stm32f10x.h>
#include <display.h>
#include <utils.h>
#include <spi.h>

void display_config()
{
    CS_LOW
	RESET_ON
	delay_us(3000);
	RESET_OFF
	delay_us(300);
	
	cmd(0xA2);		// LCD drive voltage bias ratio: 1/9 bias
	cmd(0xA0);		// RAM address and SEG output correspondence (ADC selection)
	cmd(0xC0);		// Common output mode selection (normal)
	
	//what for these 2 commands?
	//cmd(0x81);		// Electronic volume mode set
	//cmd(0x07);		// Electronic register set (elect. volume value = 0x07 - middle)

	cmd(0x25);		// Voltage regulator internal resistor ratio set (brightness control)
	cmd(0x2F);		// Power control set (ratio = 0.5)
	cmd(0xA6);		// LCD display normal color
	cmd(0x40);		// Set start line
	
	
	cmd(0xAF);		// Display ON
}

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

void display_clear()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        set_page(i);
        set_column(0x00);
        for(uint8_t j = 0; j < 132; j++)
        {
            data(0x00);
        }
    }
}

void dspl_NOP()
{
    cmd(0xE3);
}


// 
void display_buff_init(uint8_t buff[], uint16_t size)
{
	for (uint8_t i = 0; i < size; i++)
		buff[i] = 0;
}