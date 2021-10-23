#include <malloc.h>
#include <strings.h>

void *calloc(size_t number, size_t size) {
  void *memory = malloc(number * size);
  memset(memory, 0, size * number);
  return memory;
}

int memcmp(const void *a, const void *b, size_t size) {
  const char *a_ptr = (const char *)a;
  const char *b_ptr = (const char *)b;
  for (int i = 0; i < size; i++) {
    if (a_ptr[i] != b_ptr[i]) {
      return a_ptr[i] - b_ptr[i];
    }
  }
  return 0;
}
