#ifndef _MESSAGE_H
#define _MESSAGE_H  

#include <stdint.h>
#include <thread.h>

#define MESSAGE_BUFFER_LENGTH  64

typedef struct {
  thread_t from, to;
  u32_t opcode;
} message_header_t;

typedef union {
  void* ptr;
  u64_t u64;
  u32_t u32;
  u16_t u16;
  u8_t u8;
  u32_t u32s[2];
  u16_t u16s[4];
  u8_t u8s[8];
} message_payload_t;

typedef struct {
    message_header_t header;
    message_payload_t payload;
} message_t;

#endif