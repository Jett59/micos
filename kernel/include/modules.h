#ifndef _MODULES_H
#define _MODULES_H

#include <stdint.h>

#define MAX_MODULES 4

typedef struct {
  void* start;
  u64_t size;
  char name[0];
} boot_module_t;

boot_module_t* get_boot_module(int number);

#endif