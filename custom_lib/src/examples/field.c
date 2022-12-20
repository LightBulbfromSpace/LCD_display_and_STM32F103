#include <field.h>
#include <common.h>
#include <display.h>
#include <spi.h>

void draw_frame(int left_offset)
{
    //draw_pixel(bp->x,bp->y);
    CS_LOW();
    set_page(0);
    set_column(left_offset);
    for (uint8_t i = 0; i < 128 - left_offset; i++)
    {
        data(0x01);
    }

    for (uint8_t i = 0; i < 8; i++)
    {
        set_page(i);
        set_column(left_offset);
        data(0xFF);
        set_column(127);
        data(0xFF);
    }

    set_column(left_offset + 1);
    for (uint8_t i = 0; i < 126 - left_offset; i++)
    {
        data(0x80);
    }
    CS_HIGH();
}

void set_frame_in_buff(uint8_t LCD_buff[8][98])
{
    for (uint8_t i = 0; i < 98; i++)
    {
        LCD_buff[0][i] |= 0x01;
        LCD_buff[7][i] |= 0x80;
    }

    for (uint8_t i = 0; i < 8; i++)
    {
        LCD_buff[i][0] = 0xFF;
        LCD_buff[i][97] = 0xFF;
    }
}