#include <fs/initramfs.h>
#include <strings.h>

static inline size_t octal_to_binary(unsigned char *octal, size_t size) {
  size_t result = 0;
  for (size_t i = 0; i < size; i++) {
    result *= 8;
    result += octal[i] - '0';
  }
  return result;
}

size_t initramfs_read(const unsigned char *initramfs, size_t initramfs_size,
                      const char *file_name, const char **data) {
  // Preliminary checks: is this a valid tar file?
  if (initramfs_size < 512) {
    // Too small to be a tar file
    return 0;
  }
  if (memcmp(initramfs + 257, "ustar", 5)) {
    // No 'ustar' signature
    return 0;
  }
  size_t offset = 0;
  while (!memcmp(initramfs + offset + 257, "ustar", 5)) {
    size_t file_size = octal_to_binary(initramfs + offset + 124, 11);
    unsigned char file_type = initramfs[offset + 156];
    if (file_type == '0' || file_type == 0) {
      // Regular file
      if (!strcmp(file_name, initramfs + offset)) {
        // Found it!
        *data = initramfs + offset + 512;
        return file_size;
      }
    }
    offset += (file_size + 512 + 511) / 512 * 512;
  }
  // Didn't find it.
  return 0;
}
