#ifndef _DISPLAY_H
#define _DISPLAY_H  

#include <frame_buffer.h>

typedef frame_buffer_cell display_pixel;

void write_pixel(int x, int y, display_pixel pixel);
display_pixel read_pixel (int x, int y);

#endif