#!/bin/bash
make
./isoScript.sh
qemu-system-x86_64 -serial stdio -cdrom image.iso
