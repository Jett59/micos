#include <drivers/init.h>
#include <drivers/serial/serial.h>

void serial_init(void);

static DRIVER serial_driver = {.init = serial_init, .priority = 0};

void serial_init(void) {
  serial_driver.init = 0;
  if (query_com1()) {
    configure_com1();
    set_serial_enable();
  }
}
