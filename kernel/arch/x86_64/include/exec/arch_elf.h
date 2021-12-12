#ifndef _EXEC_ARCH_ELF_H
#define _EXEC_ARCH_ELF_H  

// 64 bit = 2 in the ELF header
#define ELF_NATIVE_BITNESS  2
// Little endian = 1 in the ELF header
#define ELF_NATIVE_ENDIANNESS  1
// AMD64 = 0x3E in the ELF header
#define ELF_NATIVE_INSTRUCTION_SET  0x3E

// Set which ELF structure to use
#define ELF_USE_ELF64  1

#endif