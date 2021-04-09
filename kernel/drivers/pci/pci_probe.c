#include <pci/pci.h>
#include <stdio.h>

void pci_probe_begin ()
{
    for (u8_t dev = 0; dev < 32; dev ++) {
        u32_t dev_id = get_pci_config_word (0, dev, 0, 0);
        if (~ dev_id) {
            puts ("found pci device at:");
            puthex64 ((u64_t)dev_id);
            putchar ('\n');
        }
    }
}
