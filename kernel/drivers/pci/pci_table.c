#include <pci/pci.h>
#include <stdlib.h>

static size_t pci_table_size = 1024;
static size_t pci_entries = 0;
static pci_device_t * pci_table;

void init_pci_table ()
{
    pci_table = malloc (pci_table_size * sizeof (pci_device_t));
}

void register_pci_device (pci_device_t device)
{
    * (pci_table + pci_entries) = device;
    pci_entries ++;
}
