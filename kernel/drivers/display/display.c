#include <display.h>
#include <drivers/init.h>
#include <fonts/renderer.h>
#include <memory.h>

static frame_buffer_info_t frame_buffer;

void display_init(void);

static DRIVER display_driver = {.init = display_init, .priority = 0};

static video_mode vidmode;

void display_init(void) {
  display_driver.init = 0;
  frame_buffer = *get_frame_buffer();
  if (frame_buffer.buffer == 0) {
    return; // No display
  }
  frame_buffer.buffer =
      map_physical_address(frame_buffer.buffer, (u64_t)frame_buffer.width *
                                                    (u64_t)frame_buffer.pitch *
                                                    sizeof(frame_buffer_cell));
  initialise_font();
  vidmode.frame_buffer = frame_buffer.buffer;
  vidmode.width = frame_buffer.width;
  vidmode.height = frame_buffer.height;
  vidmode.pitch = frame_buffer.pitch;
}

void write_pixel(int x, int y, display_pixel pixel) {
  if (x >= 0 && x < frame_buffer.width && y >= 0 && y < frame_buffer.height) {
    *(frame_buffer.buffer + (y * frame_buffer.pitch + x)) = pixel;
  }
}
display_pixel get_pixel(int x, int y) {
  return *(frame_buffer.buffer + (y * frame_buffer.pitch + x));
}

video_mode *get_video_mode() { return &vidmode; }
