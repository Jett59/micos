#include <fs/vfs.h>
#include <fs/directory.h>
#include <malloc.h>

file_t* virtual_directory_list(file_t* file) {
    return (file_t*)file->data;
}

file_t* virtual_directory_mkdir(file_t* file, const char* name) {
    file_t* directory = calloc(1, sizeof(file_t), 1);
    directory->data = calloc(1, sizeof(file_t), 1);
    directory->name = name;
    directory->type = FILE_DIRECTORY;
    directory->get_first_child = &virtual_directory_list;
    file->data = directory;
    return directory;
}
