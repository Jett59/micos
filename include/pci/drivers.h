#ifndef _PCI_DRIVERS-H
#define _PCI_DRIVERS_H  

#include <stdint.h>

#include <pci/pci.h>

void register_pci_driver(int(*condition)(common_pci_header*), int (*init)(pci_device_t*));

#endif