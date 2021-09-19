#include <display.h>
#include <error.h>
#include <fonts/renderer.h>

static display_pixel background = {
    .red = 0x08, .green = 0x88, .blue = 0x10, .alpha = 0xFF};
static display_pixel character_foreground = {
    .red = 0x00, .green = 0x00, .blue = 0x00, .alpha = 0x00};

void fatal_error(const char* message) {
  kill_all();
  video_mode vidmode = *get_video_mode();
  for (int x = 0; x < vidmode.width; x++) {
    for (int y = 0; y < vidmode.height; y++) {
      *(vidmode.frame_buffer + y * vidmode.pitch + x) = background;
    }
  }
  int columns = vidmode.width / get_character_width();
  int rows = vidmode.height / get_character_height();
  int start_x = columns / 2 - 3;
  char error[6] = "Error!";
  for (int i = 0; i < 6; i++) {
    render_character(start_x + i, 1, error[i], character_foreground,
                     background);
  }
  int x = 0;
  do {
    render_character(x, 3, *message, character_foreground, background);
    x++;
  } while (*(++message));
loop:
  goto loop;
}
