file build/Micos
source debugging/helper.gdb
target remote | qemu-system-x86_64 -S -gdb stdio -cdrom build/Micos.iso