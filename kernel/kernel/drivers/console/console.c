#include <fonts/renderer.h>
#include <display.h>
#include <strings.h>
#include <malloc.h>

static int current_x = 0;
static int current_y = 0;

static int characters_per_line;
static int lines;

static video_mode vidmode;

static u32_t* screen_buffer;

static void check_position_is_in_bounds () {
    if (current_x >= characters_per_line) {
        current_x = 0;
        current_y ++;
    }
    if (current_y >= lines) {
        memcpy (vidmode.frame_buffer, vidmode.frame_buffer + vidmode.pitch * get_character_height(), (lines - 1) * get_character_height() * vidmode.pitch * sizeof (display_pixel));
         memset(vidmode.frame_buffer + vidmode.pitch * get_character_height() * (lines - 1), 0x00, vidmode.pitch * get_character_height() * sizeof (display_pixel));
        current_y = lines - 1;
        current_x = 0;
    }
}

static display_pixel default_foreground = {
    .red = 0xFF,
    .green = 0xFF,
    .blue = 0xFF,
    .alpha = 0xFF
};
static display_pixel default_background = {};

void console_write_char(u32_t character) {
    if (lines == 0 || characters_per_line == 0) {
        vidmode = *get_video_mode();
        lines = vidmode.height / get_character_height ();
        characters_per_line = vidmode.width / (get_character_width () + 1);
        current_x = 0;
        current_y = 0;
        screen_buffer = calloc(lines * characters_per_line, sizeof(u32_t), 1);
    }
    if (character == '\n') {
        current_y ++;
        current_x = 0;
    }else if (character == 0x8) {
        if (current_x > 0) {
            current_x --;
            render_character(current_x, current_y, ' ', default_foreground, default_background);
        }
}else {
        render_character(current_x, current_y, character, default_foreground, default_background);
        current_x ++;
    }
    check_position_is_in_bounds();
}
