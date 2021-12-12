#include <drivers/init.h>
#include <pci/pci.h>

void pci_init(void);

static DRIVER pci_driver = {.init = pci_init, .priority = 1};

void pci_init(void) {
  pci_driver.init = 0;
  init_pci_table();
  pci_probe_begin();
}
