#include <tss.h>

tss_t tss;

u8_t rsp0[8192];

void setup_tss() {
  tss.rsp0 = rsp0 + 8192;
  tss.io_port_base_offset = 104;
}
