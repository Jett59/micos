#ifndef _PTRRANGE_H
#define _PTRRANGE_H  

#include <stdint.h>

#define IS_KERNEL_MODE_POINTER(PTR)  (((u64_t)PTR & (1ULL << 63ULL)) != 0)
#define IS_USER_MODE_POINTER(PTR)  (!IS_KERNEL_MODE_POINTER(PTR))

#endif