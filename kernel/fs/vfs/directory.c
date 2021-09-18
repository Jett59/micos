#include <fs/vfs.h>
#include <fs/directory.h>

const file_t* virtual_directory_list(const file_t* file) {
    return (const file_t*)file->data;
}
