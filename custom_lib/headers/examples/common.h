#include <stm32f10x.h>

#ifndef __BASEPOINT
#define __BASEPOINT
typedef struct
{
    uint8_t x;
    uint8_t y;
    int8_t dx;
    int8_t dy;
} base_point;

#endif