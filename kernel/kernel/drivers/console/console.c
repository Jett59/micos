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

static display_pixel default_foreground = {
    .red = 0xFF,
    .green = 0xFF,
    .blue = 0xFF,
    .alpha = 0xFF
};
static display_pixel default_background = {};

static void check_position_is_in_bounds () {
    if (current_x >= characters_per_line) {
        current_x = 0;
        current_y ++;
    }
    if (current_y >= lines) {
        for (int line = 1; line < lines; line ++) {
            int previous_line_length = strlen32(screen_buffer + (line - 1) * (characters_per_line + 1));
            int current_line_length = strlen32(screen_buffer + line * (characters_per_line + 1));
                for (int x = current_line_length; x < previous_line_length; x ++) {
                    render_character(x, line - 1, ' ', default_foreground, default_background);
            }
            strcpy32(screen_buffer + (line - 1) * (characters_per_line + 1), screen_buffer + line * (characters_per_line + 1));
            for (int x = 0; x < current_line_length; x ++) {
                render_character(x, line - 1, screen_buffer[line * (characters_per_line + 1) + x], default_foreground, default_background);
            }
        }
        int final_line_length = strlen32(screen_buffer + (lines - 1) * (characters_per_line + 1));
        for (int x = 0; x <= final_line_length; x ++) {
            render_character(x, lines - 1, ' ', default_foreground, default_background);
        }
        screen_buffer[(lines - 1) * (characters_per_line + 1)] = 0;
        current_y = lines - 1;
        current_x = 0;
    }
}

void console_write_char(u32_t character) {
    if (lines == 0 || characters_per_line == 0) {
        vidmode = *get_video_mode();
        lines = vidmode.height / get_character_height ();
        characters_per_line = vidmode.width / (get_character_width () + 1);
        current_x = 0;
        current_y = 0;
        screen_buffer = calloc(lines * (characters_per_line + 1), sizeof(u32_t), 1);
    }
    if (character == '\n') {
        current_y ++;
        current_x = 0;
    }else if (character == 0x8) {
        if (current_x > 0) {
            current_x --;
            render_character(current_x, current_y, ' ', default_foreground, default_background);
            screen_buffer[current_y * characters_per_line + current_x] = 0;
        }
}else {
        render_character(current_x, current_y, character, default_foreground, default_background);
        strappend32(screen_buffer + current_y * characters_per_line, character);
        current_x ++;
    }
    check_position_is_in_bounds();
}
