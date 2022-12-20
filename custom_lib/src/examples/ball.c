#include <stm32f10x.h>
#include <ball.h>
#include <utils.h>
#include <display.h>
#include <spi.h>
#include <string.h>

const uint8_t texture_ball[] = { 0x18, 0x76, 0x62, 0xF3, 0xFF, 0x7E, 0x7E, 0x18};

void create_ball(Ball_T *ball, base_point bp, uint8_t size) {
    ball->bp = bp;
    ball->size = size;
    memcpy(ball->texture, texture_ball, sizeof(texture_ball));
}

// invisible colums are considered
void draw_ball(Ball_T* ball)
{
    CS_LOW();
    uint8_t page = (ball->bp.y >> 3) & 0x07;
    uint8_t top_page_offset = ball->bp.y & 0x07;
    set_column(ball->bp.x);
    set_page(page);

    //first page
    for (uint8_t i = 0; i < 8; i++)
    {
        data((ball->texture[i] << top_page_offset ) & 0xFF); // Send data
    }
    set_column(ball->bp.x);

    // second page
    if (top_page_offset > 0)
    {
        set_page(page + 1);
        for (uint8_t i = 0; i < 8; i++)
        {
            data(ball->texture[i] >> (8 - top_page_offset));
        }
    }
    CS_HIGH();
}

void clear_area(Ball_T* ball)
{
    CS_LOW();
    uint8_t page = (ball->bp.y >> 3) & 0x07;
    uint8_t top_page_offset = ball->bp.y & 0x07;
    set_column(ball->bp.x);
    set_page(page);

    //first page
    for (uint8_t i = 0; i < 8; i++)
    {
        data(0x00); // Send data
    }
    set_column(ball->bp.x);

    // second page
    if (top_page_offset > 0)
    {
        set_page(page + 1);
        for (uint8_t i = 0; i < 8; i++)
        {
            data(0x00);
        }
    }
    CS_HIGH();
}

void move_ball(Ball_T* ball)
{
    delay_us(150000);
    clear_area(ball);
    
    ball->bp.x += ball->bp.dx;
    ball->bp.y += ball->bp.dy;

    if (ball->bp.y > 50 || ball->bp.y < 1)
    {
        ball->bp.dy = -ball->bp.dy;
    }
    
    if (ball->bp.x < 4 || ball->bp.x > 116)
    {
        ball->bp.dx = -ball->bp.dx;
    }

    draw_ball(ball);
}

void set_ball_in_buff(Ball_T* ball, uint8_t LCD_buff[8][98])
{
    uint8_t page = (ball->bp.y >> 3) & 0x07;
    uint8_t offset_from_top_of_page = ball->bp.y & 0x07;
    uint8_t i = 0;
    for (uint8_t col = ball->bp.x; col < ball->bp.x + ball->size; col++)
    {
        LCD_buff[page][col] |= (ball->texture[i++] << offset_from_top_of_page);
    }
    if (offset_from_top_of_page > 0)
    {
        i = 0;
        for (uint8_t col = ball->bp.x; col < ball->bp.x + ball->size; col++)
        {
            LCD_buff[page+1][col] |= (ball->texture[i++] >> (ball->size - offset_from_top_of_page));
        }
    }
}

void ball_clear(Ball_T *ball, uint8_t LCD_buff[8][98])
{
    uint8_t page = (ball->bp.y >> 3) & 0x07;
    uint8_t offset_from_top_of_page = ball->bp.y & 0x07;
    uint8_t i = 0;
    for (uint8_t col = ball->bp.x; col < ball->bp.x + ball->size; col++)
    {
        LCD_buff[page][col] &= (~ball->texture[i++] << offset_from_top_of_page);
    }
    if (offset_from_top_of_page > 0)
    {
        i = 0;
        for (uint8_t col = ball->bp.x; col < ball->bp.x + ball->size; col++)
        {
            LCD_buff[page+1][col] &= ~(ball->texture[i++] >> (ball->size - offset_from_top_of_page ));
        }
    }
}

void shift_ball_in_buff(Ball_T* ball, uint8_t LCD_buff[8][98])
{
    delay_us(150000);
    ball_clear(ball, LCD_buff);
    ball->bp.x += ball->bp.dx;
    ball->bp.y += ball->bp.dy;

    if (ball->bp.y < 6 || ball->bp.y > (60 - ball->size))
    {
        ball->bp.dy = -ball->bp.dy;
    }
    
    if (ball->bp.x < 7 || ball->bp.x > (95 - ball->size))
    {
        ball->bp.dx = -ball->bp.dx;
    }
    set_ball_in_buff(ball, LCD_buff);
}