#ifndef _PCI_PCI_H
#define _PCI_PCI_H  

#include <stdint.h>

u16_t get_pci_config_word (u8_t bus, u8_t dev, u8_t func, u8_t offset);

#endif