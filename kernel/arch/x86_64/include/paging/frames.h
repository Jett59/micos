#ifndef _PAGING_FRAMES_H
#define _PAGING_FRAMES_H

#include <stdint.h>

// Returns the index of the next free frame
u64_t allocate_frame();

// Same as above, except with multiple sequential frames
u64_t allocate_frames(u64_t number_of_frames);

// Adds the specified frame index to the pool of available frames
void return_frame(u64_t index);

// Same as above, except with multiple sequential frames
void return_frames(u64_t start_index, u64_t number_of_frames);

// Reserve the specified range of frames (inclusive)
void reserve_frames(u64_t start_index, u64_t end_index);

#endif