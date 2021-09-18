#ifndef _FS_DEVICE_H
#define _FS_DEVICE_H

#include <fs/vfs.h>

file_t *virtual_directory_list(file_t *file);
file_t *virtual_directory_mkdir(file_t *file, const char *name);

#endif