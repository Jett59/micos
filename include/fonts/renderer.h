#ifndef _FONT_RENDERER_H
#define _FONT_RENDERER_H

#include <stdint.h>

void initialise_font();
void render_character(int x, int y, u32_t code_point);

#endif