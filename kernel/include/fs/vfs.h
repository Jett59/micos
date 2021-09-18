#ifndef _FS_VFS_H
#define _FS_VFS_H  

#include <stdint.h>

typedef enum {
    FILE_DIRECTORY,
    FILE_DEVICE
} file_type;

typedef struct {
    const char* name;
    const file_type type;
    size_t (*read) (const file_t* file, size_t* offset, size_t len, void* data);
    size_t (*write) (const file_t* file, size_t* offset, size_t len, void* data);
    const char* const* (*list) ();
} file_t;

#endif