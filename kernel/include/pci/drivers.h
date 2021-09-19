#ifndef _PCI_DRIVERS_H
#define _PCI_DRIVERS_H

#include <pci/pci.h>
#include <stdint.h>

void register_pci_driver(int (*condition)(common_pci_header*),
                         int (*init)(pci_device_t*));

#endif