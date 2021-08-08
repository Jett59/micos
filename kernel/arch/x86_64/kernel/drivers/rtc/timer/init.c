#include <drivers/init.h>
#include <interrupts.h>
#include <io.h>

void rtc_timer_init (void);

static DRIVER rtc_timer_driver = {
    .init = rtc_timer_init,
    .priority = 2
};

void rtc_timer_handler (void);

void rtc_timer_init (void)
{
    register_interrupt_handler(rtc_timer_handler, 0x38);
    outb (0x8B, 0x70);
    u8_t previous = inb (0x71);
    outb (0x8B, 0x70);
    outb (previous | 0x40, 0x71);
    outb (0x8C, 0x70);
    inb (0x71);  // Read status register C in case the chip is still waiting to send another interrupt
    rtc_timer_driver.init = 0;
}
