#include <racket.h>
#include <spi.h>

void draw_racket(Racket_T* racket)
{
    CS_LOW();
    uint8_t page = racket->bp.y >> 3;
    uint8_t col = racket->hight * racket->hight - 1;
    for (uint8_t i = 0; i < racket->length; i++)
    {
        data(col);
    }
    CS_HIGH();
}

void create_racket(Racket_T* racket, base_point bp, int lenght, int hight)
{
    racket->bp = bp;
    racket->length = (uint8_t)lenght;
    racket->hight = (uint8_t)hight;
}