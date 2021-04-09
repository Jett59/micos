#ifndef _PCI_CONFIGURATION_REGISTERS_H
#define _PCI_CONFIGURATION_REGISTERS_H  

#include <pci/pci.h>

#define PCI_GET_ID(DEVICE,FUNCTION) PCI_GET_CONFIGURATION_REGISTER (DEVICE, FUNCTION, 0)
#define PCI_GET_STATUS(DEVICE, FUNCTION) (PCI_GET_CONFIGURATION_REGISTER (DEVICE, FUNCTION, 1) >> 16)
#define PCI_GET_COMMAND_REGISTER(DEVICE, FUNCTION) (PCI_GET_CONFIGURATION_REGISTER (DEVICE, FUNCTION, 1) & 0xFFFF)
#define PCI_SET_COMMAND_REGISTER(DEVICE, FUNCTION, DATA) PCI_SET_CONFIGURATION_REGISTER (DEVICE, FUNCTION, 1, ((PCI_GET_CONFIGURATION_REGISTER (DEVICE, FUNCTION, 1) >> 16) << 16) | DATA)
#define PCI_GET_BAR0(DEVICE, FUNCTION) PCI_GET_CONFIGURATION_REGISTER (DEVICE, FUNCTION, 4)
#define PCI_SET_BAR0(DEVICE, FUNCTION, DATTA) PCI_SET_CONFIGURATION_REGISTER (DEVICE, FUNCTION, DATA)

#endif