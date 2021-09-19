#include <fs/fs.h>
#include <fs/vfs.h>
#include <fs/directory.h>

#include <strings.h>

static file_t root = {
    .name = 0,
    .mkdir = &virtual_directory_mkdir,
    .get_first_child = &virtual_directory_list,
    .data = 0};

int mkdir(const char *directory)
{
    file_t *tmp = &root;
    if (*directory != '/')
    {
        return -1; // Not a valid path
    }
    int i = 0;
    int previous_i;
next_component:
    previous_i = i;
    do
    {
        i++;
    } while (directory[i] != '/' && directory[i] != 0);
    if (directory[i] == 0)
    {
        tmp->mkdir(tmp, directory + previous_i + 1);
        return 0;
    }
    else
    {
        if ((tmp = tmp->get_first_child(tmp)))
        {
            do
            {
                int status = strcmp(directory + previous_i + 1, tmp->name);
                if (status == '/') {
                    status = 0;
                }
                if (!status)
                {
                    goto next_component;
                }
            } while ((tmp = tmp->next));
            return -2; // No such file or directory
        }
        else
        {
            return -2; // No such file or directory
        }
    }
}

int list_directory(const char *directory, void (*callback)(const char *file))
{
    file_t *tmp = &root;
    if (*directory != '/')
    {
        return -1; // Malformed path
    }
    int i = 0;
    int previous_i;
next_component:
    previous_i = i;
    do
    {
        i++;
    } while (directory[i] != '/' && directory[i] != 0);
        if ((tmp = tmp->get_first_child(tmp)))
        {
            do
            {
                int status = strcmp(directory + previous_i + 1, tmp->name);
                if (status == '/') {
                    status = 0;
                }
                if (!status)
                {
                    if (directory[i]) {
                        goto next_component;
                    }else {
                        goto call_callback;
                    }
                }
            } while ((tmp = tmp->next));
            return -2; // No such file or directory
        }
        else
        {
            return -2; // No such file or directory
        }
        call_callback:
        if ((tmp = tmp->get_first_child(tmp)))
        {
            do
            {
                callback(tmp->name);
            } while ((tmp = tmp->next));
        }
        return 0;
}
