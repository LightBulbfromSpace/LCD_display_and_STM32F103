#include <stm32f10x.h>
#include <ball.h>
#include <display.h>
#include <spi.h>


// invisible colums are considered
void draw_ball(uint8_t ball[], uint8_t line, uint8_t col)
{
    set_page(0x00);
    set_start_line(line + 0x08);
    set_column(col + 0x04);
    
    for (uint8_t i = 0; i < 10; i++)
    {
        data(ball[i]);
    }
    
}