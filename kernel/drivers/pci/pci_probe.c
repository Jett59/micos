#include <pci/pci.h>
#include <stdio.h>

void pci_probe_begin ()
{
    for (u8_t dev = 0; dev < 32; dev ++) {
        u32_t dev_id = get_pci_config_word (0, dev, 0, 0);
        if (~ dev_id) {
            puts ("found pci device with device id:");
            puthex64 ((u64_t)dev_id);
            putchar ('\n');
            register_pci_device ((pci_device_t){
                .bus = 0,
                .dev = dev,
                .vender_id = dev_id & 0xFFFF,
                .device_id = (dev_id >> 16) & 0xFFFF
            });
        }
    }
}
