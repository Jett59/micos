#include <fs/vfs.h>
#include <fs/directory.h>
#include <malloc.h>

file_t *virtual_directory_list(file_t *file)
{
    return (file_t *)file->data;
}

file_t *virtual_directory_mkdir(file_t *file, const char *name)
{
    file_t *directory = calloc(1, sizeof(file_t), 1);
    directory->name = name;
    directory->type = FILE_DIRECTORY;
    directory->get_first_child = &virtual_directory_list;
    if (file->data)
    {
        int i = 0;
        file_t *tmp = (file_t*)file->data;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = directory;
    }
    else
    {
        file->data = directory;
    }
    return directory;
}
