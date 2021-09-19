#ifndef _FS_VFS_H
#define _FS_VFS_H

#include <stdint.h>

typedef enum { FILE_DIRECTORY, FILE_DEVICE } file_type;

typedef struct file_t {
  const char *name;
  file_type type;
  void *data;  // arbitrary data for the file
  size_t (*read)(const struct file_t *file, size_t *offset, size_t len,
                 void *data);
  size_t (*write)(const struct file_t *file, size_t *offset, size_t len,
                  void *data);
  struct file_t *(*get_first_child)(struct file_t *file);
  struct file_t *(*mkdir)(struct file_t *file, const char *name);
  struct file_t *previous;
  struct file_t *next;
} file_t;

#endif