#ifndef _PCI_PCI_H
#define _PCI_PCI_H  

#include <stdint.h>

typedef struct {
    u8_t bus;
    u8_t dev;
    u16_t vender_id;
    u16_t device_id;
} pci_device_t;

typedef struct __attribute__((__packed__)) {
    u16_t device_id;
    u16_t vender_id;
    u16_t status;
    u16_t command;
    u8_t class;
    u8_t subclass;
    u8_t prog_if;
    u8_t revision;
    u8_t bist; // built-in self test
    u8_t header_type;
    u8_t latency;
    u8_t cache_size;
} common_pci_header;

u32_t pci_read_configuration_register (u8_t bus, u8_t dev, u8_t func, u8_t register_offset);
u32_t pci_write_configuration_register (u8_t bus, u8_t dev, u8_t func, u8_t register_offset, u32_t data);

#define PCI_GET_CONFIGURATION_REGISTER(DEVICE, FUNCTION, REGISTER_INDEX)  pci_read_configuration_register (DEVICE.bus, DEVICE.dev, FUNCTION, REGISTER_INDEX * 4)
#define PCI_SET_CONFIGURATION_REGISTER(DEVICE, FUNCTION, REGISTER_INDEX, DATA) pci_write_configuration_register (DEVICE.bus, DEVICE.dev, FUNCTION, REGISTER_INDEX, DATA)

void pci_probe_begin ();

void init_pci_table ();
void register_pci_device (pci_device_t device);

pci_device_t search_pci_table (u16_t vender_id, u16_t device_id);

#endif