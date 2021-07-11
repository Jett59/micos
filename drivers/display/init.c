#include <frame_buffer.h>
#include <drivers/init.h>
#include <stdio.h>

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
    cell.blue = 0xff;
    cell.green = 0;
    cell.alpha = 0xff;
    puts ("Initialising screen to background state");
    for (int x = 0; x < frame_buffer.width; x ++) {
        for (int y = 0; y < frame_buffer.height; y ++) {
            * (frame_buffer.buffer + (y * frame_buffer.width + x)) = cell;
        }
    }
}
