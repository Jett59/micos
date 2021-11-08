#ifndef _TSS_H
#define _TSS_H  

#include <stdint.h>

typedef struct __attribute__((__packed__)) {
  u32_t reserved0;
  void* rsp0;
  void* rsp1;
  void* rsp2;
  u32_t reserved1[2];
  void* ist1;
  void* ist2;
  void* ist3;
  void* ist4;
  void* ist5;
  void* ist6;
  void* ist7;
  u32_t reserved2[2];
  u16_t reserved3;
  u16_t io_port_base_offset;
} tss_t;

#endif