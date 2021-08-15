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
    int i = 0;
    memory_block_t* tmp = &(free_memory.blocks [i]);
    synchronise (&frame_lock);
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