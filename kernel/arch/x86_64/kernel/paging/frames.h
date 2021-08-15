#ifndef _PAGING_FRAMES_H
#define _PAGING_FRAMES_H  

#include <stdint.h>

// Returns the index of the next free frame
u64_t allocate_frame();

// Adds the specified frame index to the pool of available frames
void return_frame (u64_t index);

#endif