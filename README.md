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
* Binutils
#### Installing
##### Debian/Ubuntu
Run this command (as root):
```bash
apt-get install clang lld grub-efi grub-pc-bin xorriso make binutils
```
##### Alpine
Run this command (as root):
```bash
apk add clang lld make binutils xorriso grub-efi grub-bios
```
### Compiling
Compiling the project is as simple as:
```bash
mak e iso
```
From the root of the project. 
This creates build/Micos.iso, which is a bootable iso image of the operating system.  
