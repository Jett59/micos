#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H  

#include <stdint.h>

#define MULTIBOOT_MBI_FRAME_BUFFER 8
#define MULTIBOOT_MBI_MEMORY_MAP  6
#define MBI_ALIGNMENT  8

typedef struct __attribute__ ((__packed__)) {
    u32_t size;
    u32_t reserved;
} mbi_begin_t;

typedef struct __attribute__ ((__packed__)) {
    u32_t type;
    u32_t size;
} mbi_tag_t;

typedef struct __attribute__ ((__packed__)) {
    u32_t type;
    u32_t size;
    u64_t address;
    u32_t pitch;
    u32_t width;
    u32_t height;
    u8_t pixel_bits;
    u8_t frame_buffer_type;
    u8_t reserved;
    union {
        struct __attribute__ ((__packed__)) {
            u32_t number_of_colors;
            struct __attribute__ ((__packed__)) {
                u8_t red;
                u8_t green;
                u8_t blue;
            } colors [0];
        } indexed;
        struct __attribute__ ((__packed__)) {
            u8_t red_begin;
            u8_t red_mask_size;
            u8_t green_begin;
            u8_t green_mask;
            u8_t blue_begin;
            u8_t blue_mask;
        } rgb;
    } color_descriptor;
} mbi_frame_buffer_tag_t;

typedef struct __attribute__((__packed__)) {
    u32_t type;
    u32_t size;
    u32_t entry_size;
    u32_t version;
    struct __attribute__ ((__packed__)) {
        u64_t address;
        u64_t length;
        u32_t type;
        u32_t reserved;
    } memory_blocks [0];
} mbi_memory_map_tag_t;

#endif