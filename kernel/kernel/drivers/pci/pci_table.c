#include <pci/drivers.h>
#include <stdlib.h>

#include "pci/pci.h"

static size_t pci_table_size = 1024;
static size_t pci_entries = 0;
static pci_device_t *pci_table;

void init_pci_table() {
  pci_table = malloc(pci_table_size * sizeof(pci_device_t));
}

void register_pci_device(pci_device_t device) {
  *(pci_table + pci_entries) = device;
  pci_entries++;
}

void register_pci_driver(int (*condition)(common_pci_header *),
                         int (*init)(pci_device_t *)) {
  common_pci_header *pci_header = malloc(sizeof(common_pci_header));
  for (size_t i = 0; i < pci_entries; i++) {
    pci_device_t *device = pci_table + i;
    *((u32_t *)pci_header + 0) =
        pci_read_configuration_register(device->bus, device->dev, 0, 0);
    *((u32_t *)pci_header + 1) =
        pci_read_configuration_register(device->bus, device->dev, 0, 4);
    *((u32_t *)pci_header + 2) =
        pci_read_configuration_register(device->bus, device->dev, 0, 8);
    *((u32_t *)pci_header + 3) =
        pci_read_configuration_register(device->bus, device->dev, 0, 12);
    if (!condition(pci_header)) {
      init(device);
    }
  }
  free(pci_header);
}
