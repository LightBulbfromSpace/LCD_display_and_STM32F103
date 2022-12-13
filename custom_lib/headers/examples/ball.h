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

typedef struct
{
    base_point bp;
    uint8_t texture[10];
} Ball_T;

void create_ball(Ball_T *ball, base_point bp);

void move_ball(Ball_T* ball);

void draw_ball(Ball_T* ball);

#endif /* __BALLH */