#include <frame_buffer.h>
#include <drivers/init.h>
#include <stdio.h>
#include <memory.h>

void display_init(void);

static DRIVER display_driver = {
    .init = display_init,
    .priority = 1
};

void display_init (void)
{
    display_driver.init = 0;
    puts ("Initialising frame buffer");
    frame_buffer_info_t frame_buffer = *get_frame_buffer();
    frame_buffer_cell cell;
    cell.red = 0;
    cell.blue = 0;
    cell.green = 0xff;
    cell.alpha = 0;
    puts ("Mapping frame buffer region");
    frame_buffer.buffer = map_physical_address(frame_buffer.buffer, frame_buffer.width * frame_buffer.height * sizeof (frame_buffer_cell));
    puts ("initial colour:");
    puthex64 ((*frame_buffer.buffer).blue);
    puts ("Initialising screen to background state");
    int x, y;
    for (y = 0; y < frame_buffer.height; y ++) {
        for (x = 0; x < frame_buffer.width; x ++) {
            * (frame_buffer.buffer + (y * frame_buffer.width + x)) = cell;
        }
    }
}
