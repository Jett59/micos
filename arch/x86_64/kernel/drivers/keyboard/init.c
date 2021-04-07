#include <interrupts.h>
#include <drivers/init.h>

void keyboard_interrupt_handler (void);

void keyboard_init (void);

static DRIVER keyboard_driver = {
    .init = keyboard_init,
    .priority = 2
};

void keyboard_init (void)
{
    register_interrupt_handler (keyboard_interrupt_handler, 0x31);
    keyboard_driver.init = 0;
}
