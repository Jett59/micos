#! /bin/sh

set +e

timeout 20s qemu-system-x86_64 -cdrom build/Micos.iso -serial stdio -display none > qemu-test.log

set -e

cat qemu-test.log | grep Welcome
cat qemu-test.log | grep Done
