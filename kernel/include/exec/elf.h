#ifndef _EXEC_ELF_H
#define _ELF_EXEC_H  

#include <exec/arch_elf.h>
#include <exec/format.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct __attribute__((__packed__)) {
  unsigned char magic[4]; // \177, 'E', 'L', 'F'
  u8_t bitness; // 1 = 32 bit, 2 = 64 bit
  u8_t endianness; // 1 = little endian, 2 = big endian
  u8_t header_version;
  u8_t abi;
  u64_t padding; // Unused
  u16_t type; // 1 = relocatable, 2 = executable, 3 = shared, 4 = core dump
  u16_t instruction_set;
  u32_t elf_version;
} elf_common_header_t;

#ifdef ELF_USE_ELF64
typedef struct __attribute__((__packed__)) {
  elf_common_header_t common_header;
  void* entrypoint;
  u64_t program_header_offset;
  u64_t section_header_offset;
  u32_t flags;
  u16_t header_size;
  u16_t program_header_entry_size;
  u16_t num_program_header_entries;
  u16_t section_header_entry_size;
  u16_t num_section_header_entries;
  u16_t section_name_section_index;
} elf_header_t;
#else
#ifdef ELF_USE_ELF32
#error ELF32 structure not currently supported
#else
#error Either ELF_USE_ELF32 or ELF_USE_ELF64 must be defined
#endif
#endif

bool elf_matches(unsigned char* file, size_t size);

exec_entrypoint elf_load(unsigned char* file, size_t size);

#define ELF_FORMAT  ((exec_format_t){.matches = elf_matches, .load = elf_load})

#endif