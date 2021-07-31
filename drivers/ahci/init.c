#include "fis.h"
#include <drivers/init.h>
#include <pci/drivers.h>
#include <stdio.h>
#include <memory.h>

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
    void* ahci_physical_address = (void*)pci_read_configuration_register(device->bus, device->dev, 0, 0x24);
    puts("Ahci: Address:");
    puthex64((u64_t)ahci_physical_address);
    ahci_memory_t* ahci_memory = map_physical_address_uncached(ahci_physical_address, sizeof (ahci_memory));
    if (!(ahci_memory->host_controll & 0x80000000)) {
        puts ("Ahci: Mode switch");
        ahci_memory->host_controll |= 0x80000000;
        if (ahci_memory->host_controll & 0x80000000) {
            puts ("Ahci: In ahci mode");
        }else {
            puts ("Ahci: Failed to set ahci mode");
            return -1;
        }
    }
    puts ("Ahci: Ports:");
    putnum64(ahci_memory->port_implemented, 2);
    return 0;
}

void ahci_init (void)
{
    ahci_driver.init = 0;
    register_pci_driver(ahci_check, ahci_bind);
}
