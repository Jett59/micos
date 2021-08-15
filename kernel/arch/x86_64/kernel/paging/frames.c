#include <paging/frames.h>
#include <memory/map.h>
#include <error.h>
#include <lock.h>

static memory_map_t free_memory;

static void init () {
    free_memory = *get_available_memory();
    // Page align the blocks
    for (int i = 0; i < free_memory.number_of_blocks; i ++) {
        memory_block_t* memory_block = &(free_memory.blocks [i]);
        memory_block->length = memory_block->length / 4096 * 4096;
        memory_block->base = (void*)(((u64_t)memory_block->base + 4095) / 4096 * 4096);
    }
}

static lock_t frame_lock;

u64_t allocate_frame () {
    synchronise (&frame_lock);
    if (free_memory.number_of_blocks == 0) {
        init ();
    }
    int i = 0;
    memory_block_t* tmp = &(free_memory.blocks [i]);
    // Select a block to get the frame from
    while (tmp->length == 0) {
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
    tmp->base = (void*)(index * 4096);
    tmp->length = 4096;
    if (i >= free_memory.number_of_blocks) {
        free_memory.number_of_blocks = i + 1;
    }
    free_lock (&frame_lock);
}
