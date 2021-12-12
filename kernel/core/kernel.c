#include <memory/pointers.h>

#ifdef __x86_64
void *get_pointer(size_t address) { return (void *)address; }
size_t get_linear_address(void *ptr) { return (size_t)ptr; }
#endif
