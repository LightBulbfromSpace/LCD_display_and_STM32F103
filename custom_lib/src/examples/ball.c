#include <stm32f10x.h>
#include <ball.h>
#include <utils.h>
#include <display.h>
#include <spi.h>

uint8_t ball[] = {0x00, 0x18, 0x76, 0x62, 0xF3, 0xFF, 0x7E, 0x7E, 0x18, 0x00};

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

    CS_LOW
    RS_CMD

    SPI1->DR = p->x & 0x0F;         // Set column
    SPI_write(0x10 | (p->x >> 4));  //

    SPI_write(0xB0 | page);         // Set page

    while (SPI1->SR & SPI_SR_BSY);

    RS_DATA
    for (uint8_t i = 0; i < 10; i++)
    {
        SPI_write((ball[i] << pos_in_col) & 0xFF); // Send data
    }
    while (SPI1->SR & SPI_SR_BSY);
    
    RS_CMD
    SPI1->DR = p->x & 0x0F;         // Set column
    SPI_write(0x10 | (p->x >> 4));  //


    if (pos_in_col > 0)
    {
        SPI_write(0xB0 | page + 1);
        while (SPI1->SR & SPI_SR_BSY);

        RS_DATA
        for (uint8_t i = 0; i < 10; i++)
        {
            SPI_write(ball[i] >> (8 - pos_in_col));
        }
    }
    else
    {
        if (page > 0)
        {
        SPI_write(0xB0 | page + (-1)*p->dy);    // Set page

        SPI_write((p->x + 3) & 0x0F);           // Set column
        SPI_write(0x10 | ((p->x + 3) >> 4));    //
        while (SPI1->SR & SPI_SR_BSY);

        RS_DATA
        for (uint8_t i = 0; i < 4; i++)
            SPI_write(0x00);
        }

    }
    while (SPI1->SR & SPI_SR_BSY);
    CS_HIGH

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
