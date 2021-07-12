#include <frame_buffer.h>
#include <drivers/init.h>
#include <memory.h>

void display_init(void);

static DRIVER display_driver = {
    .init = display_init,
    .priority = 0
};

void display_init (void)
{
    display_driver.init = 0;
    frame_buffer_info_t frame_buffer = *get_frame_buffer();
    frame_buffer_cell cell;
    cell.red = 0;
    cell.blue = 0;
    cell.green = 0xff;
    cell.alpha = 0;
    frame_buffer.buffer = map_physical_address(frame_buffer.buffer, frame_buffer.width * frame_buffer.height * sizeof (frame_buffer_cell));
    int x, y;
    for (y = 0; y < frame_buffer.height; y ++) {
        for (x = 0; x < frame_buffer.width; x ++) {
            * (frame_buffer.buffer + (y * frame_buffer.width + x)) = cell;
        }
    }
}
