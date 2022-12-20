#include <stdint.h>

#ifndef __STATIC_BASEPOINT
#define __STATIC_BASEPOINT

typedef struct {
    int x;
    int y;
}static_basepoint;

#endif

void draw_frame(int left_offset);
void set_frame_in_buff(uint8_t LCD_buff[8][98]);