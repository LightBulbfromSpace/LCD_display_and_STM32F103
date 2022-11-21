#include <stm32f10x.h>
#include <ball.h>
#include <utils.h>
#include <display.h>
#include <spi.h>

// invisible colums are considered
void draw_ball(uint8_t ball[], uint8_t line, uint8_t col)
{
    //uint8_t size = sizeof(*ball);
    set_page(0x00);
    set_start_line(line + 0x08);
    set_column(col + 0x04);
    
    for (uint8_t i = 0; i < 10; i++)
    {
        data(ball[i]);
    }
    
}

void move_ball(base_point* p, uint8_t ball[])
{
    uint8_t page = (p->y >> 3) & 0x07;
    uint8_t pos_in_col = p->y & 0x07;

    set_column(p->x);
    set_page(page);

    for (uint8_t i = 0; i < 10; i++)
    {
        data((ball[i] << pos_in_col) & 0xFF);
    }
    
    set_column(p->x);


    if (pos_in_col > 0)
    {
        set_page(page + 1);
        for (uint8_t i = 0; i < 10; i++)
        {
            data(ball[i] >> (8 - pos_in_col));
        }
    }
    else
    {
        set_page(page + (-1)*p->dy);
        set_column(p->x + 3);
        for (uint8_t i = 0; i < 4; i++)
            data(0x00);
    }
    

    p->x += p->dx;
    p->y += p->dy;

    if (p->y > 55 || p->y < 1)
    {
        p->dy = -p->dy;
    }
    
    if (p->x < 4 || p->x > 122)
    {
        p->dx = -p->dx;
    }
    delay_us(100000);
}
