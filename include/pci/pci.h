#ifndef _PCI_PCI_H
#define _PCI_PCI_H  

#include <stdint.h>

typedef struct {
    u8_t bus;
    u8_t dev;
    u16_t vender_id;
    u16_t device_id;
} pci_device_t;

u32_t pci_read_configuration_register (u8_t bus, u8_t dev, u8_t func, u8_t register_offset);
u32_t pci_write_configuration_register (u8_t bus, u8_t dev, u8_t func, u8_t register_offset, u32_t data);

void pci_probe_begin ();

void init_pci_table ();
void register_pci_device (pci_device_t device);

#endif