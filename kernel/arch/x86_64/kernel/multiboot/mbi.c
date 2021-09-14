#include <multiboot.h>
#include <frame_buffer.h>
#include <memory/map.h>
#include <memory.h>

static frame_buffer_info_t frame_buffer = {
    .buffer = 0,
    .width = 0,
    .height = 0};

frame_buffer_info_t *get_frame_buffer()
{
    return &frame_buffer;
}

static memory_map_t available_memory = {
    .number_of_blocks = 0};

memory_map_t *get_available_memory()
{
    return &available_memory;
}

extern u64_t multiboot_data_ptr;

void process_tag(mbi_tag_t *tag)
{
    if (tag->type == MULTIBOOT_MBI_FRAME_BUFFER)
    {
        mbi_frame_buffer_tag_t *frame_buffer_ptr = (mbi_frame_buffer_tag_t *)tag;
        if (frame_buffer_ptr->pixel_bits == 32)
        {
            frame_buffer.buffer = (frame_buffer_cell *)frame_buffer_ptr->address;
            frame_buffer.width = frame_buffer_ptr->width;
            frame_buffer.height = frame_buffer_ptr->height;
            frame_buffer.pitch = frame_buffer_ptr->pitch / 4;
        }
    }
    else if (tag->type == MULTIBOOT_MBI_MEMORY_MAP)
    {
        mbi_memory_map_tag_t *memory_map_tag = (mbi_memory_map_tag_t *)tag;
        if (memory_map_tag->entry_size == sizeof(memory_map_tag->memory_blocks[0]))
        {
            u32_t number_of_entries = (memory_map_tag->size - sizeof(mbi_memory_map_tag_t)) / memory_map_tag->entry_size;
            for (u32_t i = 0; i < number_of_entries; i++)
            {
                if (memory_map_tag->memory_blocks[i].type == 1)
                {
                    memory_block_t memory_block;
                    memory_block.base = (void *)memory_map_tag->memory_blocks[i].address;
                    memory_block.length = memory_map_tag->memory_blocks[i].length;
                    available_memory.blocks[available_memory.number_of_blocks] = memory_block;
                    available_memory.number_of_blocks++;
                }
            }
        }
    }
}

void scan_mbi()
{
    u64_t mbi_ptr = multiboot_data_ptr;
    mbi_ptr+=8;
    while (((mbi_tag_t *)mbi_ptr)->type)
    {
        mbi_tag_t tag = *((mbi_tag_t *)mbi_ptr);
        process_tag((mbi_tag_t *)mbi_ptr);
        mbi_ptr += ((tag.size + MBI_ALIGNMENT - 1) / 8) * 8;
    }
    mbi_ptr = (u64_t)map_physical_address((void*)mbi_ptr, *((u32_t*)mbi_ptr));
}
