#include <fs/directory.h>
#include <fs/vfs.h>
#include <malloc.h>

file_t *virtual_directory_list(file_t *file) { return (file_t *)file->data; }

file_t *virtual_directory_mkdir(file_t *file, const char *name) {
  file_t *directory = calloc(1, sizeof(file_t));
  directory->name = name;
  directory->type = FILE_DIRECTORY;
  directory->get_first_child = &virtual_directory_list;
  directory->mkdir = &virtual_directory_mkdir;
  if (file->data) {
    int i = 0;
    file_t *tmp = (file_t *)file->data;
    while (tmp->next) {
      tmp = tmp->next;
    }
    tmp->next = directory;
    directory->previous = tmp;
  } else {
    file->data = directory;
  }
  return directory;
}
