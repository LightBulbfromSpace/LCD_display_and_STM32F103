#ifndef __BALLH
#define __BALLH

#include <stm32f10x.h>
#include <common.h>


typedef struct
{
    base_point bp;
    uint8_t size;
    uint8_t texture[10];
} Ball_T;

void create_ball(Ball_T *ball, base_point bp, uint8_t size);

void move_ball(Ball_T* ball);

void draw_ball(Ball_T* ball);

void set_ball_in_buff(Ball_T* ball, uint8_t LCD_buff[8][98]);
void shift_ball_in_buff(Ball_T* ball, uint8_t LCD_buff[8][98]);

#endif /* __BALLH */