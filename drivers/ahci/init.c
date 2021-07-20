#include "fis.h"
#include <drivers/init.h>
#include <pci/drivers.h>
#include <stdio.h>

void ahci_init (void);

static DRIVER ahci_driver = {
    .init = ahci_init,
    .priority = 2
};

static int ahci_check (common_pci_header* header)
{
    if (header->class == 1 && header->subclass == 6) {
        return 0;
    }
    return 1;
}

static int ahci_bind (pci_device_t* device) 
{
    puts ("Ahci: Bind");
    void* ahci_memory = (void*)pci_read_configuration_register(device->bus, device->dev, 0, 0x24);
    puts("Ahci: Address:");
    puthex64((u64_t)ahci_memory);
    return 0;
}

void ahci_init (void)
{
    ahci_driver.init = 0;
    register_pci_driver(ahci_check, ahci_bind);
}
