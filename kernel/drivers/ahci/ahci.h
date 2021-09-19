#ifndef _DRIVERS_AHCI_AHCI_H
#define _DRIVERS_AHCI_AHCI_H

typedef enum {
  AHCI_DEVICE_NULL = 0,
  AHCI_DEVICE_SATA,
  AHCI_DEVICE_SATAPI
} ahci_device_type;

typedef struct {
  ahci_device_type type;
  int index;
} ahci_device_t;

extern ahci_device_t ahci_devices[];

#endif