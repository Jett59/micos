#include <fonts/renderer.h>
#include <display.h>
#include <strings.h>

static int current_x;
static int current_y;

static int characters_per_line;
static int lines;

static video_mode vidmode;

static void check_position_is_in_bounds () {
    if (current_x >= characters_per_line) {
        current_x = 0;
        current_y ++;
    }
    if (current_y >= lines) {
        memcpy (vidmode.frame_buffer + vidmode.width, vidmode.frame_buffer, (vidmode.height - 1) * vidmode.width * sizeof (display_pixel));
        memset (vidmode.frame_buffer + (vidmode.height - 1) * vidmode.width, 0x00, vidmode.height * sizeof (display_pixel));
    }
}

void console_write_char(u32_t character) {
    if (lines == 0 || characters_per_line == 0) {
        vidmode = get_video_mode();
        lines = vidmode.height / get_character_height ();
        characters_per_line = vidmode.width / get_character_width ();
    }
    check_position_is_in_bounds();
    if (character == '\n') {
        current_y ++;
        current_x = 0;
    }else {
        render_character(current_x, current_y, character);
        current_x ++;
    }
}
