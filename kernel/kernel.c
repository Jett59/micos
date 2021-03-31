#include <memory/pointers.h>

void * get_pointer (size_t address)
{
    return (void *) address;
}
size_t get_linear_address (void * ptr)
{
    return (size_t)ptr;
}