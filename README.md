# micos
A simple toy operating system.
## Building
### Dependencies
Micos depends on the following tools:
* Clang
* Lld
* Grub (pc and EFI binaries)
* xorriso
* Make
#### Installing
##### Debian/Ubuntu
Run this command:
```bash
sudo apt-get install -y clang lld grub-efi grub-pc-bin xorriso make
```
### Compiling
Compiling the project is as simple as:
```bash
make iso
```
From the root of the project. 
This creates a few files under the build directory. The most important ones are:
* Micos.iso. This is a bootable cdrom image with both bios and uefi support.
* Micos. This is the raw kernel file.
