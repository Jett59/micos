#ifndef _HAULT_H
#define _HAULT_H

static inline void cpu_hault() {
  __asm__ volatile(
      "pushfq;"
      "sti;"
      "hlt;"
      "popfq;");
}

#endif