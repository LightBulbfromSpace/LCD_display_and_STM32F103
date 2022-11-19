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
	cmd(0xA1);		// RAM address and SEG output correspondence (ADC selection)
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
    cmd(0xB0 | page_addr & 0x07);
}

void set_column(uint8_t col_addr)
{
    cmd(col_addr & 0x0F);
	cmd(0x10 | (col_addr >> 4));
}

void display_clear()
{
	CS_LOW
    for (uint8_t i = 0; i < 8; i++)
    {
		RS_CMD

		SPI_write(0xB0 | i & 0x07);		// Set page

		SPI_write(0x00);				// Set column
		SPI_write(0x10);				//
		while (SPI1->SR & SPI_SR_BSY);

        for(uint8_t j = 0; j < 132; j++)
        {
			RS_DATA
			SPI_write(0x00);
        }
    }
	CS_HIGH
}

void dspl_NOP()
{
    cmd(0xE3);
}


void display_buff_init(uint8_t buff[], uint16_t size)
{
	for (uint8_t i = 0; i < size; i++)
		buff[i] = 0;
}

// x in range [1:64], y in range [1:128]
void draw_pixel(uint8_t x, uint8_t y)
{
	y--;
	
	set_page((y >> 3) & 0x07);
	set_column(x & 0x7F);

	data(1 << (y & 0x07));
}


void set_pixel(uint8_t x, uint8_t y, uint8_t LCD_Buff[])
{
	LCD_Buff[(x & 0x7F) * (y >> 3) & 0x07] |= 1 << (y & 0x07);
}

void repaint(uint8_t LCD_Buff[])
{
	set_page(0x01); //(uint8_t)((i >> 7) & 0x07)
		set_column(0x01); //(uint8_t)(i & 0x7F)
		data(0xA3);
	for (uint16_t i = 0; i < 1024; i++)
	{
		
	}
}