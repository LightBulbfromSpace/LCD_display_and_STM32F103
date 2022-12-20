#include <racket.h>
#include <spi.h>
#include <display.h>

void draw_racket(Racket_T* racket)
{
    CS_LOW();
    uint8_t page = (racket->bp.y >> 3) & 0x07;
    set_page(page);
    uint8_t col_data = set_n_LSB(racket->hight);
    set_column(racket->bp.x);
    for (uint8_t i = 0; i < racket->length; i++)
    {
        data(col_data);
    }
    CS_HIGH();
}

void create_racket(Racket_T* racket, base_point bp, int lenght, int hight)
{
    racket->bp = bp;
    racket->length = (uint8_t)lenght;
    racket->hight = (uint8_t)hight;
}

uint8_t set_n_LSB(uint8_t n)
{
    uint8_t res = 0;
    for (uint8_t i = 0; i < n; i++)
    {
        res = (res << 1) | 0x01;
    }
    return res;
}