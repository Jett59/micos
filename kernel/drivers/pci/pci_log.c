#include <pci/drivers.h>
#include <drivers/init.h>
#include <stdio.h>

void pci_log(void);

static DRIVER pci_logger = {
    .init = pci_log,
    .priority = 2
};

static int print_pci_info(common_pci_header* header) {
    puts ("pci device id:");
    puthex64(header->device_id);
    puts("vendor:");
    puthex64(header->vendor_id);
    puts ("Class:");
    puthex64(header->class);
    puts ("subclass:");
    puthex64(header->subclass);
    return 1;
}

void pci_log (void) {
    pci_logger.init = 0;
    register_pci_driver(print_pci_info, 0);
}
