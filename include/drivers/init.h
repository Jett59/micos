#ifndef _DRIVERS_INIT_H
#define _DRIVERS_INIT_H  

typedef struct {
    void (*init)(void);
} driver_info;

#define DRIVER  driver_info __attribute__ ((section (".driver")))

void initialise_drivers ();

#endif