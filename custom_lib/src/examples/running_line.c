#include <stm32f10x.h>
#include <utils.h>
#include <spi.h>
#include <display.h>
#include <running_line.h>

void running_line()
{
    		for (uint8_t j = 0; j < 8; j++)
		{
			set_page(j);
			set_column(0x00);
			for (uint8_t i = 0; i < 132; i++)
			{
				data(0xFF);
				delay_us(10000);
			}
			set_column(0x00);
			for (uint8_t i = 0; i < 132; i++)
			{
				data(0x00);
				delay_us(10000);
			}
		}
}