#ifndef _DRIVERS_AHCI_FIS_H
#define _DRIVERS_AHCI_FIS_H

#include <stdint.h>

typedef enum
{
    FIS_TYPE_REG_HOST_TO_DEVICE = 0x27, // Host to device
    FIS_TYPE_REG_DEVICE_TO_HOST = 0x34, // Device to host
    FIS_TYPE_DMA_ACTIVATE = 0x39, // Device to host
    FIS_TYPE_DMA_SETUP = 0x41, // Bidirectional
    FIS_TYPE_DATA = 0x46, // Bidirectional
    FIS_TYPE_BIST = 0x58, // Bidirectional
    FIS_TYPE_PIO_SETUP = 0x5F, // Device to host
    FIS_TYPE_DEV_BITS = 0xA1 // Device to host (set device bits)
} fis_type;

typedef struct __attribute__((__packed__)) {
    u8_t fis_type; // FIS_TYPE_REG_HOST_TO_DEVICE

    u8_t port_multiplier:4;
    u8_t reserved0:3;
    u8_t command_control:1; // 1: Command, 0: Control

    u8_t command; // Command register
    u8_t feature_low;	// Feature register, 7:0

    u8_t lba0; // LBA low register, 7:0
    u8_t lba1; // LBA mid register, 15:8
    u8_t lba2; // LBA high register, 23:16
    u8_t device; // Device register

    u8_t lba3; // LBA register, 31:24
    u8_t lba4; // LBA register, 39:32
    u8_t lba5; // LBA register, 47:40
    u8_t feature_high; // Feature register, 15:8

    u16_t count;
    u8_t isochronous_command_completion;
    u8_t controll;

    u32_t reserved1;
} fis_register_host_to_device;

typedef struct __attribute__((__packed__)) {
    u8_t fis_type; // FIS_TYPE_REG_DEVICE_TO_HOST

    u8_t port_multiplier:4;
    u8_t reserved0:2;
    u8_t i:1;
    u8_t rsv1:1;

    u8_t status;
    u8_t error;

    u8_t lba0;
    u8_t lba1;
    u8_t lba2;
    u8_t device;

    u8_t lba3;
    u8_t lba4;
    u8_t lba5;
    u8_t reserved2;

    u16_t count;
    u16_t reserved3;

    u32_t reserved4;
} fis_register_device_to_host;

typedef struct __attribute__((__packed__)) {
    u8_t fis_type; // FIS_TYPE_DATA

    u8_t port_multiplier:4;
    u8_t reserved0:4;

    u16_t reserved1;

    u32_t data[1]; // Payload
} fis_data;

typedef struct __attribute__((__packed__)) {
    u8_t fis_type; // FIS_TYPE_PIO_SETUP

    u8_t port_multiplier:4;
    u8_t reserved0:1;
    u8_t direction:1; // Data transfer direction, 1 - device to host
    u8_t interrupt:1;
    u8_t reserved1:1;

    u8_t status;
    u8_t error;

    u8_t lba0;
    u8_t lba1;
    u8_t lba2;
    u8_t device;

    u8_t lba3;
    u8_t lba4;
    u8_t lba5;
    u8_t reserved2;

    u16_t count;
    u8_t reserved3;
    u8_t new_status;

    u16_t transfer_count;
    u16_t reserved4;
} fis_pio_setup;

typedef struct __attribute__((__packed__)) {
    u8_t fis_type; // FIS_TYPE_DMA_SETUP

    u8_t port_multiplier:4;
    u8_t reserved0:1;
    u8_t direction:1;		// 1 - device to host
    u8_t interrupt:1;
    u8_t auto_activate:1; // Is dma activate fis needed?

    u16_t reserved1;

    u64_t dma_buffer_id;

    u32_t reserved2;

    u32_t dma_buffer_offset; //Byte offset into buffer. First 2 bits must be 0

    u32_t transfer_count; // Number of bytes to transfer. Bit 0 must be 0

    u32_t reserved3;
} fis_dma_setup;

typedef volatile struct __attribute__((__packed__))
{
    u64_t command_list;
    u64_t fis_base;
    u32_t interrupt_status;
    u32_t interrupt_enable;
    u32_t command;
    u32_t reserved0;
    u32_t task_file_data;
    u32_t signature;
    u32_t status;
    u32_t controll;
    u32_t error;
    u32_t active;
    u32_t command_issue;
    u32_t notification;
    u32_t fis_based_switch;
    u32_t reserved1[11];   
    u32_t vendor[4];    // vendor specific
} ahci_port;

typedef volatile struct __attribute__((__packed__))
{
    u32_t capabilities;
    u32_t host_controll;
    u32_t interrupt_status;
    u32_t port_implemented;
    u32_t version;
    u32_t command_completion_controll;
    u32_t command_completion_port;
    u32_t enclosure_management_location;
    u32_t enclosure_management_controll;
    u32_t extended_capabilities;
    u32_t bios_handoff;    // Bios/os handoff and status

    u8_t reserved[126];

    u8_t vendor[96];

    ahci_port	ports[32]; // maximum 32
} ahci_memory_t;

#endif