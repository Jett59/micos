#include <multiboot.h>
#include <frame_buffer.h>

static frame_buffer_info_t frame_buffer;

frame_buffer_info_t get_frame_buffer ()
{
    return frame_buffer;
}

extern u64_t multiboot_data_ptr;

void scan_mbi ()
{
    u64_t mbi_ptr = multiboot_data_ptr + 8; /*first tag*/
    while (((mbi_tag_t *)mbi_ptr)-> type) {
        multiboot_tag_t tag = * ((mbi_tag_t *)mbi_ptr);
        process_tag (tag);
        mbi_ptr += ((tag->size + MBI_ALIGNMENT - 1) / 8) * 8;
    }
}
void process_tag (mbi_tag_t tag) {
    return;
}
