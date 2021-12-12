#include <exec/elf.h>
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
  // Yes.
  return true;
}

exec_entrypoint elf_load(const unsigned char *file, size_t size) {
  // TODO
  return 0;
}
