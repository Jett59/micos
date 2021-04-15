#ifndef _FRAME_BUFFER_H
#define _FRAME_BUFFER_H  

#include <stdint.h>

typedef struct __attribute__ ((__packed__)) {
    u8_t red;
    u8_t green;
    u8_t blue;
    u8_t alpha;
} frame_buffer_cell;

typedef struct {
    frame_buffer_cell * buffer;
    u32_t width;
    u32_t height;
} frame_buffer_info_t;

frame_buffer_info_t get_frame_buffer ();

#endif