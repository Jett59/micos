#ifndef _DRIVERS_INIT_H
#define _DRIVERS_INIT_H  

#include <stdint.h>

typedef struct __attribute__ ((__packed__)) {
    void (*init)(void);
    u16_t priority;
} driver_info;

#define DRIVER  driver_info __attribute__ ((section (".driver")))

void initialise_drivers (u16_t priority);

#endif