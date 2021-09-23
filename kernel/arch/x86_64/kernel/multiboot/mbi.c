#include <frame_buffer.h>
#include <malloc.h>
#include <memory.h>
#include <memory/map.h>
#include <modules.h>
#include <multiboot.h>
#include <strings.h>

static frame_buffer_info_t frame_buffer = {
    .buffer = 0, .width = 0, .height = 0};

frame_buffer_info_t *get_frame_buffer() { return &frame_buffer; }

static memory_map_t available_memory = {.number_of_blocks = 0};

memory_map_t *get_available_memory() { return &available_memory; }

static int number_of_modules = 0;

static u64_t module_offsets[MAX_MODULES];

static boot_module_t *boot_modules[MAX_MODULES] = {0};

boot_module_t *get_boot_module(int number) { return boot_modules[number]; }

extern u64_t multiboot_data_ptr;

void process_tag(mbi_tag_t *tag) {
  if (tag->type == MULTIBOOT_MBI_FRAME_BUFFER) {
    mbi_frame_buffer_tag_t *frame_buffer_ptr = (mbi_frame_buffer_tag_t *)tag;
    if (frame_buffer_ptr->pixel_bits == 32) {
      frame_buffer.buffer = (frame_buffer_cell *)frame_buffer_ptr->address;
      frame_buffer.width = frame_buffer_ptr->width;
      frame_buffer.height = frame_buffer_ptr->height;
      frame_buffer.pitch = frame_buffer_ptr->pitch / 4;
    }
  } else if (tag->type == MULTIBOOT_MBI_MEMORY_MAP) {
    mbi_memory_map_tag_t *memory_map_tag = (mbi_memory_map_tag_t *)tag;
    if (memory_map_tag->entry_size ==
        sizeof(memory_map_tag->memory_blocks[0])) {
      u32_t number_of_entries =
          (memory_map_tag->size - sizeof(mbi_memory_map_tag_t)) /
          memory_map_tag->entry_size;
      for (u32_t i = 0; i < number_of_entries; i++) {
        if (memory_map_tag->memory_blocks[i].type == 1) {
          memory_block_t memory_block;
          memory_block.base = (void *)memory_map_tag->memory_blocks[i].address;
          memory_block.length = memory_map_tag->memory_blocks[i].length;
          available_memory.blocks[available_memory.number_of_blocks] =
              memory_block;
          available_memory.number_of_blocks++;
        }
      }
    }
  } else if (tag->type == MULTIBOOT_MBI_BOOT_MODULE) {
    if (number_of_modules >= MAX_MODULES) {
      return;
    }
    module_offsets[number_of_modules++] = (u64_t)tag - multiboot_data_ptr;
  }
}

void scan_mbi() {
  u64_t mbi_ptr = multiboot_data_ptr;
  mbi_ptr += 8;
  while (((mbi_tag_t *)mbi_ptr)->type) {
    mbi_tag_t tag = *((mbi_tag_t *)mbi_ptr);
    process_tag((mbi_tag_t *)mbi_ptr);
    mbi_ptr += ((tag.size + MBI_ALIGNMENT - 1) / 8) * 8;
  }
  mbi_ptr = (u64_t)map_physical_address((void *)multiboot_data_ptr,
                                        *((u32_t *)multiboot_data_ptr));
  for (int i = 0; i < number_of_modules; i++) {
    mbi_boot_module_tag_t *module_tag =
        (mbi_boot_module_tag_t *)(mbi_ptr + module_offsets[i]);
    u32_t size = module_tag->end - module_tag->start;
    void *module_data = map_physical_address((void *)module_tag->start, size);
    int name_size = strlen(module_tag->name);
    boot_module_t *module = malloc(sizeof(boot_module_t) + name_size + 1);
    strcpy(module->name, module_tag->name);
    module->size = size;
    module->start = module_data;
    boot_modules[i] = module;
  }
}
