#include <drivers/init.h>
#include <interrupts.h>

void rtc_timer_init (void);

static DRIVER rtc_timer_driver = {
    .init = rtc_timer_init,
    .priority = 2
};

void rtc_timer_handler (void);

void rtc_timer_init (void)
{
    register_interrupt_handler(rtc_timer_handler, 0x38);
    rtc_timer_driver.init = 0;
}