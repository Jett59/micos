#include <drivers/serial/serial.h>
#include <drivers/init.h>

void serial_init (void);

static DRIVER serial_driver = {
    .init = serial_init,
    .priority = 0
};

void serial_init (void)
{
    if (query_com1 ()) {
        configure_com1 ();
        set_serial_enable ();
    }
}
