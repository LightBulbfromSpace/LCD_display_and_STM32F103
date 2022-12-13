#include <stm32f10x.h>
#include <ball.h>
#include <utils.h>
#include <display.h>
#include <spi.h>
#include <string.h>

const uint8_t texture_ball[] = {0x00, 0x18, 0x76, 0x62, 0xF3, 0xFF, 0x7E, 0x7E, 0x18, 0x00};

void create_ball(Ball_T *ball, base_point bp) {
    ball->bp = bp;
    memcpy(ball->texture, texture_ball, sizeof(texture_ball));
}

// invisible colums are considered
void draw_ball(Ball_T* ball)
{
    uint8_t page = (ball->bp.y >> 3) & 0x07;
    set_column(ball->bp.x);
    set_page(page);
    int top_page_offset = ball->bp.y & 0x07;
    //first page
    for (uint8_t i = 0; i < sizeof(ball->texture)/sizeof(uint8_t); i++)
    {
        data((ball->texture[i] << top_page_offset ) & 0xFF); // Send data
    }
    set_column(ball->bp.x);
    // second page
    if (ball->bp.y > 0)
    {
        if (top_page_offset > 0)
        {
            set_page(page + 1);
            for (uint8_t i = 0; i < sizeof(ball->texture)/sizeof(uint8_t); i++)
            {
                data(ball->texture[i] >> (8 - top_page_offset));
            }
        }
        else
        {
            if (page > 0)
            {
            set_page(page + (-1)*ball->bp.dy);
            set_column(ball->bp.x + 3);
            for (uint8_t i = 0; i < 4; i++)
                data(0x00);
            }

        }
    }
}

void move_ball(Ball_T* ball)
{
    /*set_start_line(0x00);
    uint8_t page = (ball->bp.y >> 3) & 0x07;

    set_column(ball->bp.x);

    set_page(page);
    for (uint8_t i = 0; i < sizeof(ball->texture)/sizeof(uint8_t); i++)
    {
        data((ball->texture[i] << ball->bp.y) & 0xFF); // Send data
    }
    set_column(ball->bp.x);


    if (ball->bp.y > 0)
    {
        set_page(page + 1);
        for (uint8_t i = 0; i < sizeof(ball->texture)/sizeof(uint8_t); i++)
        {
            data(ball->texture[i] >> (8 - ball->bp.y));
        }
    }
    else
    {
        if (page > 0)
        {
        set_page(page + (-1)*ball->bp.dy);
        set_column(ball->bp.x + 3);
        for (uint8_t i = 0; i < 4; i++)
            data(0x00);
        }

    }*/
    draw_ball(ball);

    ball->bp.x += ball->bp.dx;
    ball->bp.y += ball->bp.dy;

    if (ball->bp.y > 55 || ball->bp.y < 1)
    {
        ball->bp.dy = -ball->bp.dy;
    }
    
    if (ball->bp.x < 4 || ball->bp.x > 122)
    {
        ball->bp.dx = -ball->bp.dx;
    }

    delay_us(2000000);
}
