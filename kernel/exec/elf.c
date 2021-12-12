#include <exec/elf.h>
#include <paging/alloc.h>
#include <ptrrange.h>
#include <strings.h>

bool elf_matches(const unsigned char *file, size_t size) {
  // Is it an ELF file?
  if (size < sizeof(elf_header_t)) {
    return false;
  }
  if (memcmp(file, "\177ELF", 4) != 0) {
    return false;
  }
  // Yes, but is it native?
  elf_header_t *header = (elf_header_t *)file;
  if (header->common_header.bitness != ELF_NATIVE_BITNESS) {
    return false;
  }
  if (header->common_header.endianness != ELF_NATIVE_ENDIANNESS) {
    return false;
  }
  if (header->common_header.instruction_set != ELF_NATIVE_INSTRUCTION_SET) {
    return false;
  }
  // Yes, but is it an executable?
  if (header->common_header.type != ELF_EXECUTABLE) {
    return false;
  }
  // Yes.
  return true;
}

exec_entrypoint elf_load(const unsigned char *file, size_t size) {
  elf_header_t *header = (elf_header_t *)file;
  const unsigned char *program_header_base = file + header->program_header_offset;
  for (u16_t i = 0; i < header->num_program_header_entries; i++) {
    elf_program_header_entry_t *program_header_entry =
        (elf_program_header_entry_t *)(program_header_base +
                                       i * header->program_header_entry_size);
    if (program_header_entry->type == ELF_LOADABLE) {
      if (!IS_KERNEL_MODE_POINTER(program_header_entry->virtual_address) &&
          !IS_KERNEL_MODE_POINTER(
              ((unsigned char *)program_header_entry->virtual_address) +
              program_header_entry->size_in_memory)) {
        if (program_header_entry->file_offset +
                program_header_entry->size_in_file <
            size) {
          void *section_address = program_header_entry->virtual_address;
          allocate_pages(section_address,
                         (program_header_entry->size_in_memory + PAGE_SIZE - 1) / PAGE_SIZE,
                         PAGE_WRITABLE | PAGE_USER);
          memcpy(section_address, file + program_header_entry->file_offset,
                 program_header_entry->size_in_file);
                 if (program_header_entry->size_in_memory > program_header_entry->size_in_file) {
          memset((unsigned char *)section_address +
                     program_header_entry->size_in_file,
                 0,
                 program_header_entry->size_in_memory -
                     program_header_entry->size_in_file);
                 }
        }
      }
    }
  }
  return header->entrypoint;
}
