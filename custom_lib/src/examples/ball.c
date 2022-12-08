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
void draw_ball(uint8_t texture_ball[], uint8_t line, uint8_t col)
{
    //uint8_t size = sizeof(*ball);
    set_page(0x00);
    set_start_line(line + 0x08);
    set_column(col + 0x04);
    
    for (uint8_t i = 0; i < 10; i++)
    {
        data(texture_ball[i]);
    }
    
}

void move_ball(Ball_T* ball)
{
    uint8_t page = (ball->bp.y >> 3) & 0x07;
    uint8_t pos_in_col = ball->bp.y & 0x07;

    CS_LOW
    RS_CMD

    SPI1->DR = ball->bp.x & 0x0F;         // Set column
    SPI_write(0x10 | (ball->bp.x >> 4));  //

    SPI_write(0xB0 | page);         // Set page

    while (SPI1->SR & SPI_SR_BSY);

    RS_DATA
    for (uint8_t i = 0; i < 10; i++)
    {
        SPI_write((ball->texture[i] << pos_in_col) & 0xFF); // Send data
    }
    while (SPI1->SR & SPI_SR_BSY);
    
    RS_CMD
    SPI1->DR = ball->bp.x & 0x0F;         // Set column
    SPI_write(0x10 | (ball->bp.x >> 4));  //


    if (pos_in_col > 0)
    {
        SPI_write(0xB0 | page + 1);
        while (SPI1->SR & SPI_SR_BSY);

        RS_DATA
        for (uint8_t i = 0; i < 10; i++)
        {
            SPI_write(ball->texture[i] >> (8 - pos_in_col));
        }
    }
    else
    {
        if (page > 0)
        {
        SPI_write(0xB0 | page + (-1)*ball->bp.dy);    // Set page

        SPI_write((ball->bp.x + 3) & 0x0F);           // Set column
        SPI_write(0x10 | ((ball->bp.x + 3) >> 4));    //
        while (SPI1->SR & SPI_SR_BSY);

        RS_DATA
        for (uint8_t i = 0; i < 4; i++)
            SPI_write(0x00);
        }

    }
    while (SPI1->SR & SPI_SR_BSY);
    CS_HIGH

    ball->bp.x += ball->bp.dx;
    ball->bp.y += ball->bp.dy;

    if (ball->bp.y > 55 || ball->bp.y < 1)
    {
        ball->bp.y = -ball->bp.y;
    }
    
    if (ball->bp.x < 4 || ball->bp.x > 122)
    {
        ball->bp.x = -ball->bp.x;
    }

    delay_us(100000);
}
