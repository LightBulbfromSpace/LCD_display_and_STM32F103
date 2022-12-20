#include <buffer.h>
#include <stdint.h>
#include <display.h>
#include <spi.h>

void clear_buffer(uint8_t LCD_buff[8][98])
{
    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 98; j++)
        {
            LCD_buff[i][j] = 0x00;
        } 
    }
}

void repaint_screen(uint8_t LCD_buff[8][98])
{
    CS_LOW();
    for (uint8_t i = 0; i < 8; i++)
    {
        set_page(i);
        set_column(30);
        for (uint8_t j = 0; j < 98; j++)
        {
            data(LCD_buff[i][j]);
        } 
    }
    CS_HIGH();
}