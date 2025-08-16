#!/bin/bash
make
./isoScript.sh
qemu-system-x86_64 -cdrom image.iso
