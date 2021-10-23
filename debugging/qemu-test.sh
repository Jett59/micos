#! /bin/sh

make clean
make iso
timeout 20s qemu-system-x86_64 -cdrom build/Micos.iso -serial stdio -display none > qemu-test.log
