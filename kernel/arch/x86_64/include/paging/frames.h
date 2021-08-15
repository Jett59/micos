#ifndef _PAGING_FRAMES_H
#define _PAGING_FRAMES_H  

#include <stdint.h>

// Returns the index of the next free frame
u64_t allocate_frame();

// Adds the specified frame index to the pool of available frames
void return_frame (u64_t index);

// Reserve the specified range of frames (inclusive)
void reserve_frames (u64_t start_index, u64_t end_index);

#endif