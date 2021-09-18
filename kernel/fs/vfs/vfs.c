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
        tmp->mkdir(tmp, directory + previous_i);
        return 0;
    }
    else
    {
        int component_length = 0;
        while (directory[previous_i + 1 + component_length++] != '/');
        component_length--;
        if ((tmp = tmp->get_first_child(tmp)))
        {
            do
            {
                int status = 1;
                for (int i = 0; i < component_length; i ++) {
                    if (directory[previous_i + 1 + component_length] != tmp->name [i]) {
                        status = 0;
                        break;
                    }
                }
                if (status) {
                    goto next_component;
                }
            }while ((tmp = tmp->next));
            return -2; // No such file or directory
        }
        else
        {
            return -2; // No such file or directory
        }
    }
}
