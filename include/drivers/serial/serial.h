#ifndef _DRIVERS_SERIAL_SERIAL_H
#define _DRIVERS_SERIAL_SERIAL_H

#include <stdint.h>

int query_com1 ();
void configure_com1 ();

void set_serial_enable ();

void write_to_serial (u8_t val);

#endif