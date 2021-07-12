#include <display.h>
#include <drivers/init.h>
#include <memory.h>
#include <fonts/renderer.h>

static frame_buffer_info_t frame_buffer;

void display_init(void);

static DRIVER display_driver = {
    .init = display_init,
    .priority = 0
};

void display_init (void)
{
    display_driver.init = 0;
    frame_buffer = *get_frame_buffer();
    frame_buffer.buffer = map_physical_address(frame_buffer.buffer, frame_buffer.width * frame_buffer.height * sizeof (frame_buffer_cell));
    initialise_font();
    for (int x = 0; x < 20; x ++) {
        for (int y = 0; y < 20; y ++) {
            render_character(x, y, (u32_t)'A');
        }
    }
}

void write_pixel(int x, int y, display_pixel pixel) {
    * (frame_buffer.buffer + (y * frame_buffer.width + x)) = pixel;
}
display_pixel get_pixel (int x, int y) {
    return * (frame_buffer.buffer + (y * frame_buffer.width + x));
}
