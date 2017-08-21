#!/bin/bash

mkdir -p isodir/boot/grub

cp zeon.kernel isodir/boot/zeon.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "Zeon OS" {
	multiboot /boot/zeon.kernel
}
EOF
grub-mkrescue -o zeon.iso isodir
