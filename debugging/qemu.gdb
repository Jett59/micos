add-symbol-file build/Micos 0x100000
target remote | qemu-system-x86_64 -S -gdb stdio -cdrom build/Micos.iso