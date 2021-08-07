#include <drivers/init.h>
#include <interrupts.h>

void handle_timer_interrupt (void);

void timer_init (void);

static DRIVER timer_driver = {
    .init = timer_init,
    .priority = 1
};

void timer_init (void)
{
    register_interrupt_handler (handle_timer_interrupt, 0x30);
    timer_driver.init = 0;
}
