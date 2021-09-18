#ifndef _FS_FS_H
#define _FS_FS_H

void list_directory(const char* directory, void (*callback) (const char* file));

void mkdir(const char *dir);

#endif