#include <exec.h>
#include <exec/elf.h>
#include <exec/format.h>

static exec_format_t exec_formats[] = {ELF_FORMAT};
static int num_exec_formats = sizeof(exec_formats) / sizeof(exec_format_t);

exec_status exec_load(const unsigned char* file, size_t size, exec_entrypoint* entrypoint) {
  for (int i = 0; i < num_exec_formats; i ++) {
      if (exec_formats[i].matches(file, size)) {
        *entrypoint = exec_formats[i].load(file, size);
        return EXEC_SUCCESS;
      }
  }
  return EXEC_FORMAT_ERROR;
  }
