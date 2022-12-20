#include <stm32f10x.h>
#include <common.h>

typedef struct
{
    base_point bp;
    uint8_t length;
    uint8_t hight;
} Racket_T;

void draw_racket(Racket_T* racket);
void create_racket(Racket_T* racket, base_point bp, int lenght, int hight);
uint8_t set_n_LSB(uint8_t n);