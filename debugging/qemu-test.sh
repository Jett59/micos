#! /bin/sh

set +e

timeout 20s qemu-system-x86_64 -cdrom build/Micos.iso -serial stdio -display none > qemu-test.log

set -e

grep Welcome qemu-test.log
grep Done qemu-test.log
