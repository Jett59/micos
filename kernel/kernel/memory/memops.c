#include <malloc.h>
#include <strings.h>

void* calloc(size_t number, size_t size, unsigned int alignment) {
    void* memory = malloc(number * size, alignment);
    for (int i = 0; i < number * size; i ++) {
        *((u8_t*)memory) = 0;
    }
    return memory;
}
