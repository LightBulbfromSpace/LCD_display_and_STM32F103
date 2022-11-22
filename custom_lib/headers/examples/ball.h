#ifndef __BALLH
#define __BALLH

#include <stm32f10x.h>

typedef struct
{
    uint8_t x;
    uint8_t y;
    int8_t dx;
    int8_t dy;
} base_point;


void draw_ball(uint8_t ball[], uint8_t line, uint8_t col);
void move_ball(base_point* p, uint8_t ball[]);

#endif /* __BALLH */