#include <multiboot.h>
#include <frame_buffer.h>

static frame_buffer_info_t frame_buffer = {
    .buffer = 0,
    .width = 0,
    .height = 0
};

frame_buffer_info_t* get_frame_buffer ()
{
    return &frame_buffer;
}

extern u64_t multiboot_data_ptr;

void process_tag (mbi_tag_t*  tag)
{
    if (tag->type == MULTIBOOT_MBI_FRAME_BUFFER) {
        mbi_frame_buffer_tag_t * frame_buffer_ptr = (mbi_frame_buffer_tag_t *)tag;
        if (frame_buffer_ptr->pixel_bits == 32) {
        frame_buffer.buffer = (frame_buffer_cell *)frame_buffer_ptr->address;
        frame_buffer.width = frame_buffer_ptr->width;
        frame_buffer.height = frame_buffer_ptr->height;
        frame_buffer.pitch = frame_buffer_ptr->pitch / 4;
        }
    }
}

void scan_mbi ()
{
    u64_t mbi_ptr = multiboot_data_ptr + 8; /*first tag*/
    while (((mbi_tag_t *)mbi_ptr)-> type) {
        mbi_tag_t tag = * ((mbi_tag_t *)mbi_ptr);
        process_tag ((mbi_tag_t *)mbi_ptr);
        mbi_ptr += ((tag.size + MBI_ALIGNMENT - 1) / 8) * 8;
    }
}
