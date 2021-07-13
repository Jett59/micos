#include <fonts/renderer.h>
#include <display.h>
#include <strings.h>

static int current_x = 0;
static int current_y = 0;

static int characters_per_line;
static int lines;

static video_mode vidmode;

static void check_position_is_in_bounds () {
    if (current_x >= characters_per_line) {
        current_x = 0;
        current_y ++;
    }
    if (current_y >= lines) {
        memcpy (vidmode.frame_buffer, vidmode.frame_buffer + vidmode.width * get_character_height(), (lines - 1) * get_character_height() * vidmode.width * sizeof (display_pixel));
         memset(vidmode.frame_buffer + (lines - 1) * get_character_height() * vidmode.width, 0x00, vidmode.width * get_character_height() * sizeof (display_pixel));
        current_y = lines - 1;
        current_x = 0;
    }
}

void console_write_char(u32_t character) {
    if (lines == 0 || characters_per_line == 0) {
        vidmode = *get_video_mode();
        lines = vidmode.height / get_character_height ();
        characters_per_line = vidmode.width / get_character_width ();
        current_x = 0;
        current_y = 0;
    }
    if (character == '\n') {
        current_y ++;
        current_x = 0;
    }else {
        render_character(current_x, current_y, character);
        current_x ++;
    }
    check_position_is_in_bounds();
}
