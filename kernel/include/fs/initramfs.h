#ifndef _FS_INITRAMFS_H
#define _FS_INITRAMFS_H  

#include <stdint.h>

// Gets the contents of the specified file in the initramfs, returning the size or 0 if the file could not be found, and putting a pointer to the data in data.
size_t initramfs_read(const unsigned char* initramfs, const size_t initramfs_size, const char* file_name, const unsigned char** data);

#endif