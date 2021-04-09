#include <io.h>
#include <pci/pci.h>

u32_t pci_read_configuration_register (u8_t bus, u8_t dev, u8_t func, u8_t register_offset)
{
    u32_t bus_32 = (u32_t)bus;
    u32_t dev_32 = (u32_t)dev;
    u32_t func_32 = (u32_t)func;

    u32_t pci_address = (bus_32 << 16) | (dev_32 << 11) |
    (func_32 << 8) | (register_offset & 0xFC) | (u32_t)0x80000000; // bus = pci bus, dev = device, func = device function, offset = offset into the pci configuration space, 0x80000000 = control bit set
    outl (pci_address, 0xCF8); // give the address to the pci controller
    io_delay ();
    return inl (0xCFC); // read back the result
}
u32_t pci_write_configuration_register (u8_t bus, u8_t dev, u8_t func, u8_t register_offset, u32_t data)
{
    u32_t bus_32 = (u32_t)bus;
    u32_t dev_32 = (u32_t)dev;
    u32_t func_32 = (u32_t)func;

    u32_t address = (bus_32 << 16) | (dev_32 << 11) |
    (func << 8) | (register_offset & 0xFC) | (u32_t)0x80000000;
    outl (address, 0xCF8); // put the address in
    io_delay ();
    outl (data, 0xCFC); // actually write the data
    return inl (0xCFC); // return the new contents of the register
}
