#ifndef _FS_FS_H
#define _FS_FS_H

int list_directory(const char* directory, void (*callback)(const char* file));

int mkdir(const char* dir);

#endif