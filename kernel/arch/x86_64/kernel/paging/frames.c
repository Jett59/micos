#include <error.h>
#include <lock.h>
#include <memory/map.h>
#include <paging/frames.h>
#include <strings.h>

static memory_map_t free_memory = {.number_of_blocks = 0};

extern void kernel_physical_start;
extern void kernel_physical_end;

static lock_t frame_lock;

static void init() {
  memset(&free_memory, 0, sizeof(memory_map_t));
  memory_map_t *available_memory = get_available_memory();
  free_memory.number_of_blocks = available_memory->number_of_blocks;
  for (int i = 0; i < free_memory.number_of_blocks; i++) {
    free_memory.blocks[i] = available_memory->blocks[i];
    memory_block_t *memory_block = &(free_memory.blocks[i]);
    memory_block->length = memory_block->length / 4096 * 4096;
    memory_block->base =
        (void *)(((u64_t)memory_block->base + 4095) / 4096 * 4096);
  }
  free_lock(&frame_lock);
  reserve_frames((u64_t)&kernel_physical_start / 4096,
                 ((u64_t)&kernel_physical_end + 4095) / 4096);
  synchronise(&frame_lock);
}

u64_t allocate_frames(u64_t number_of_frames) {
  synchronise(&frame_lock);
  if (free_memory.number_of_blocks == 0) {
    init();
  }
  int i = 0;
  memory_block_t *tmp = &(free_memory.blocks[i]);
  // Select a block to get the frame from
  while (tmp->length < number_of_frames * 4096 &&
         i < free_memory.number_of_blocks) {
    i++;
    tmp = &(free_memory.blocks[i]);
  }
  if (i >= free_memory.number_of_blocks) {
    fatal_error("Could not locate a frame");
  }
  u64_t frames = (u64_t)tmp->base / 4096;
  tmp->base = (void *)((u64_t)tmp->base + number_of_frames * 4096);
  tmp->length -= number_of_frames * 4096;
  free_lock(&frame_lock);
  return frames;
}

u64_t allocate_frame() { return allocate_frames(1); }

void return_frames(u64_t index, u64_t number_of_frames) {
  synchronise(&frame_lock);
  if (free_memory.number_of_blocks == 0) {
    init();
  }
  int i = 0;
  memory_block_t *tmp = &(free_memory.blocks[i]);
  // Try to find a block which is consecutive with the frame
  for (i = 0; i < free_memory.number_of_blocks; i++) {
    tmp = &(free_memory.blocks[i]);
    if ((u64_t)tmp->base / 4096 == index + number_of_frames + 1) {
      tmp->base = (void *)(index * 4096);
      tmp->length += 4096 * number_of_frames;
      free_lock(&frame_lock);
      return;
    }
    if (((u64_t)tmp->base + tmp->length) / 4096 == index - 1) {
      tmp->length += 4096 * number_of_frames;
      free_lock(&frame_lock);
      return;
    }
  }
  // The frame is not consecutive with any blocks
  i = 0;
  tmp = &(free_memory.blocks[i]);
  while (tmp->length != 0 && i < free_memory.number_of_blocks) {
    i++;
  }
  if (i >= 1024) {
    fatal_error("Unable to return frame");
  }
  tmp->base = (void *)(index * 4096);
  tmp->length = 4096 * number_of_frames;
  if (i >= free_memory.number_of_blocks) {
    free_memory.number_of_blocks = i + 1;
  }
  free_lock(&frame_lock);
}

void return_frame(u64_t index) { return_frames(index, 1); }

void reserve_frames(u64_t start_index, u64_t end_index) {
  if (start_index > end_index) {
    fatal_error("Start block index > end index");
  }
  synchronise(&frame_lock);
  if (free_memory.number_of_blocks == 0) {
    init();
  }
  for (int i = 0; i < free_memory.number_of_blocks; i++) {
    memory_block_t *block = &(free_memory.blocks[i]);
    u64_t block_start = (u64_t)block->base / 4096;
    u64_t block_end = block_start + block->length / 4096;
  if (block_start * 4096 != (u64_t)block->base) {
      fatal_error("Block base is not aligned");
    }
    if ((block_end - block_start) * 4096 != block->length) {
      fatal_error("Block length is not page aligned");
    }
    if (block_start >= start_index && block_end <= end_index) {
      block->length = 0;
    } else if (start_index <= block_start && end_index < block_end &&
               end_index >= block_start) {
      block->length = (block_end - end_index) * 4096;
      block->base = (void *)(end_index * 4096);
    } else if (start_index > block_start && start_index <= block_end &&
               end_index >= block_end) {
      block->length = (block_end - start_index) * 4096;
    } else if (start_index >= block_start && end_index <= block_end) {
      block->length = 0;
      free_lock(&frame_lock);
      return_frames(block_start, start_index - block_start);
      return_frames(end_index, block_end - end_index);
      synchronise(&frame_lock);
    }
  }
  free_lock(&frame_lock);
}
