#include <pci/drivers.h>
#include <drivers/init.h>
#include <stdio.h>

void pci_log(void);

static DRIVER pci_logger = {
    .init = pci_log,
    .priority = 2
};

static int handle_pci_device(common_pci_header* header) {
    if (header->class == 0x1) {
        puts ("Hard drive:");
        switch (header->subclass) {
            case 0x0:
            puts ("Scsi!");
            puthex64(header->vendor_id);
            puthex64(header->device_id);
            break;
            case 0x1:
            puts ("Ide!");
            puthex64(header->vendor_id);
            puthex64(header->device_id);
            break;
            case 0x6:
            puts ("Sata!");
            puthex64(header->vendor_id);
            puthex64(header->device_id);
            break;
            default:
            puts("Unknown...");
            puthex64(header->vendor_id);
            puthex64(header->device_id);
            puthex64(header->subclass);
            break;
        }
    }
    return 1;
}

void pci_log (void) {
    pci_logger.init = 0;
    register_pci_driver(handle_pci_device, 0);
}
