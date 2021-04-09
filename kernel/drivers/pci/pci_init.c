#include <pci/pci.h>
#include <drivers/init.h>
#include <stdio.h>

void pci_init (void);

static DRIVER pci_driver = {
    .init = pci_init,
    .priority = 1
};

void pci_init (void)
{
    pci_driver.init = 0;
    puts ("beginning pci scan");
    pci_probe_begin ();
}
