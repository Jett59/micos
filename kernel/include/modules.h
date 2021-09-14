#ifndef _MODULES_H
#define _MODULES_H  

#include <stdint.h>

typedef struct {
    void* start;
    u64_t size;
    char name[0];
} boot_module_t;

#endif