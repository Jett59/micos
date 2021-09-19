#include <malloc.h>
#include <strings.h>

void *calloc(size_t number, size_t size, unsigned int alignment) {
  void *memory = malloc(number * size, alignment);
  memset(memory, 0, size * number);
  return memory;
}
