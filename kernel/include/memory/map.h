#ifndef _MEMORY_MAP_H
#define _MEMORY_MAP_H  

typedef struct {
    void* base;
    u64_t length;
} memory_block_t;

typedef struct {
    u32_t number_of_blocks;
    memory_block_t blocks [1024];
} memory_map_t;

memory_map_t* get_available_memory ();

#endif