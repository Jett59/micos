#include <malloc.h>
#include <strings.h>

void *calloc(size_t number, size_t size) {
  void *memory = malloc(number * size);
  memset(memory, 0, size * number);
  return memory;
}
