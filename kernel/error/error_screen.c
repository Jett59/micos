#include <display.h>
#include <error.h>
#include <fonts/renderer.h>

static display_pixel background = {
    .red = 0x10,
    .green = 0x88,
    .blue = 0x18,
    .alpha = 0xFF
};
static display_pixel character_foreground = {
    .red = 0x00,
    .green = 0x00,
    .blue = 0x00,
    .alpha = 0x00
};

void fatal_error(const char* message)
{
    video_mode vidmode = *get_video_mode();
    for (int i = 0; i < vidmode.width * vidmode.height; i ++) {
        * (vidmode.frame_buffer + i) = background;
    }
    int columns = vidmode.width / get_character_width();
    int rows = vidmode.height / get_character_height();
    int start_x = columns / 2 - 3;
    char error [6] = "Error!";
    for (int i = 0; i < 6; i ++) {
        render_character(start_x + i, 1, error[i], character_foreground, background);
    }
    int x = 0;
    do {
        render_character(x, 3, *message, character_foreground, background);
        x ++;
    }while (*(++message));
}
