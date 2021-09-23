#include <display.h>
#include <fonts/renderer.h>
#include <malloc.h>
#include <strings.h>

#define get_start_of_line(line) \
  (screen_buffer + (line) * (characters_per_line + 1))
#define get_character_at(x, y) (*(get_start_of_line(y) + (x)))
#define set_character_at(x, y, character) \
  (*(get_start_of_line(y) + (x)) = (character))

#define get_line_length(line) strlen32(get_start_of_line(line))

static int current_x = 0;
static int current_y = 0;

static int characters_per_line;
static int lines;

static video_mode vidmode;

static u32_t *screen_buffer;

static display_pixel default_foreground = {
    .red = 0xFF, .green = 0xFF, .blue = 0xFF, .alpha = 0xFF};
static display_pixel default_background = {};

static void check_and_scroll() {
  if (current_y >= lines) {
    for (int line = 1; line < lines; line++) {
      int previous_line_length = get_line_length(line - 1);
      int current_line_length = get_line_length(line);
      strcpy32(get_start_of_line(line - 1), get_start_of_line(line));
      for (int x = 0; x < current_line_length || x < previous_line_length;
           x++) {
        u32_t current_character = get_character_at(x, line);
        render_character(x, line - 1,
                         x < current_line_length ? current_character : ' ',
                         default_foreground, default_background);
      }
    }
    int final_line_length = get_line_length(lines - 1);
    for (int x = 0; x <= final_line_length; x++) {
      render_character(x, lines - 1, ' ', default_foreground,
                       default_background);
    }
    set_character_at(0, lines - 1, 0);
    current_y = lines - 1;
    current_x = 0;
  }
}

static inline void new_line() {
  current_x = 0;
  current_y++;
  check_and_scroll();
  set_character_at(0, current_y, 0);
}

void console_write_char(u32_t character) {
  if (lines == 0 || characters_per_line == 0) {
    vidmode = *get_video_mode();
    lines = vidmode.height / get_character_height();
    characters_per_line = vidmode.width / (get_character_width() + 1);
    current_x = 0;
    current_y = 0;
    screen_buffer =
        malloc(lines * (characters_per_line + 1) * sizeof(u32_t));
    *screen_buffer = 0;
  }
  if (character == '\n') {
    new_line();
  } else if (character == 0x8) {
    if (current_x > 0) {
      current_x--;
      render_character(current_x, current_y, ' ', default_foreground,
                       default_background);
      set_character_at(current_x, current_y, 0);
    }
  } else {
    render_character(current_x, current_y, character, default_foreground,
                     default_background);
    set_character_at(current_x, current_y, character);
    set_character_at(current_x + 1, current_y, 0);
    current_x++;
    if (current_x >= characters_per_line) {
      new_line();
    }
  }
}
