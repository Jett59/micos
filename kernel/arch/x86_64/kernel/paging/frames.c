#include <paging/frames.h>
#include <memory/map.h>
#include <error.h>
#include <lock.h>
#include <strings.h>

static memory_map_t free_memory;

extern void kernel_physical_start;
extern void kernel_physical_end;

static lock_t frame_lock;

static void init () {
    memory_map_t* available_memory = get_available_memory ();
    memcpy (&free_memory, available_memory, available_memory->number_of_blocks * sizeof (memory_block_t) + (sizeof (memory_map_t) - sizeof (memory_block_t) * (1024 - available_memory->number_of_blocks)));
    // Page align the blocks
    for (int i = 0; i < free_memory.number_of_blocks; i ++) {
        memory_block_t* memory_block = &(free_memory.blocks [i]);
        memory_block->length = memory_block->length / 4096 * 4096;
        memory_block->base = (void*)(((u64_t)memory_block->base + 4095) / 4096 * 4096);
    }
    free_lock (&frame_lock);
    reserve_frames((u64_t)&kernel_physical_start / 4096, ((u64_t)&kernel_physical_end + 4095) / 4096);
    synchronise (&frame_lock);
}

u64_t allocate_frame () {
    synchronise (&frame_lock);
    if (free_memory.number_of_blocks == 0) {
        init ();
    }
    int i = 0;
    memory_block_t* tmp = &(free_memory.blocks [i]);
    // Select a block to get the frame from
    while (tmp->length == 0) {
        if (i >= 1024) {
            fatal_error ("Unable to find frame");
        }
        i ++;
        tmp = &(free_memory.blocks [i]);
    }
    tmp->length -= 4096;
    u64_t frame = ((u64_t)tmp->base + tmp->length) / 4096;
    free_lock (&frame_lock);
    return frame;
}

void return_frame (u64_t index) {
    synchronise (&frame_lock);
    int i = 0;
    memory_block_t* tmp = &(free_memory.blocks [i]);
    // Try to find a block which is consecutive with the frame
    for (i = 0; i < free_memory.number_of_blocks; i ++) {
        if ((u64_t)tmp->base / 4096 == index + 1) {
            tmp->base = (void*)((u64_t)tmp->base - 4096);
            tmp->length += 4096;
            free_lock (&frame_lock);
            return;
        }
        if (((u64_t)tmp->base + tmp->length) / 4096 == index - 1) {
            tmp->length += 4096;
            free_lock (&frame_lock);
            return;
        }
        i ++;
        tmp = &(free_memory.blocks [i]);
    }
    // The frame is not consecutive with any blocks
    i = 0;
    tmp = &(free_memory.blocks [i]);
    while (tmp->length != 0) {i++;}
    if (i >= 1024) {
        fatal_error ("Unable to return frame");
    }
    tmp->base = (void*)(index * 4096);
    tmp->length = 4096;
    if (i >= free_memory.number_of_blocks) {
        free_memory.number_of_blocks = i + 1;
    }
    free_lock (&frame_lock);
}

void reserve_frames (u64_t start_index, u64_t end_index) {
    synchronise (&frame_lock);
    for (int i = 0; i < free_memory.number_of_blocks; i ++) {
        memory_block_t* block = &(free_memory.blocks [i]);
        u64_t block_start = (u64_t)block->base / 4096;
        u64_t block_end = block_start + block->length / 4096;
        if (block_start >= start_index && block_end <= end_index) {
            block->length = 0;
        }else if (start_index <= block_start && end_index < block_end) {
            u64_t new_block_base = end_index * 4096;
            block->length -= new_block_base - block_start * 4096;
            block->base = (void*)new_block_base;
        }else if (start_index > block_start && end_index >= block_end) {
            block->length -= (start_index - block_start) * 4096;
        }else if (start_index >= block_start && end_index <= block_end) {
            block->length = 0;
            for (u64_t frame = block_start; frame <= block_end; frame ++) {
                __asm__("mov %0, %%rax;"
                "inside_internal_loop:" : : "g"(frame) : "rax");
                if (frame < start_index || frame > end_index) {
                    free_lock (&frame_lock);
                    return_frame (frame);
                    synchronise (&frame_lock);
                }
            }
        }
    }
    free_lock (&frame_lock);
}
