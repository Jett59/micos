#ifndef _FONT_RENDERER_H
#define _FONT_RENDERER_H

#include <stdint.h>

#include <display.h>

void initialise_font();
void render_character(int x, int y, u32_t code_point, display_pixel foreground, display_pixel background);

int get_character_width ();
int get_character_height ();

#endif