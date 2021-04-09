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

pci_device_t search_pci_table (u16_t vender_id, u16_t device_id)
{
    for (size_t i = 0; i < pci_entries; i++) {
        pci_device_t entry = * (pci_table + i);
        if (entry.vender_id == vender_id) {
            if (entry.device_id == device_id) {
                return entry;
            }
        }
    }
    return (pci_device_t) {
        .bus = 0,
        .dev = 0,
        .vender_id = 0xFFFF,
        .device_id = 0xFFFF
    };
}
