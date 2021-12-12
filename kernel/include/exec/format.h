#ifndef _EXEC_FORMAT_H
#define _EXEC_FORMAT_H  

#include <stdbool.h>
#include <stdint.h>

typedef void (*exec_entrypoint)(void);

typedef struct {
  bool (*matches)(unsigned char* file, size_t size);
  // Returns the start address
  exec_entrypoint (*load)(unsigned char* file, size_t size);
} exec_format_t;

#endif