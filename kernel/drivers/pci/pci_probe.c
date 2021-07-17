#include <pci/pci.h>

void pci_probe_begin ()
{
    for (u8_t dev = 0; dev < 32; dev ++) {
        u32_t dev_id = pci_read_configuration_register (0, dev, 0, 0);
        if (~ dev_id) {
            register_pci_device ((pci_device_t){
                .bus = 0,
                .dev = dev,
                .vendor_id = dev_id & 0xFFFF,
                .device_id = (dev_id >> 16) & 0xFFFF
            });
        }
    }
}
