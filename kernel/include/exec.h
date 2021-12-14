#ifndef _EXEC_H
#define _EXEC_H

#include <exec/format.h>

typedef enum { EXEC_SUCCESS, EXEC_FORMAT_ERROR } exec_status;

exec_status exec_load(const unsigned char* file, size_t size,
                      exec_entrypoint* entrypoint);

#endif