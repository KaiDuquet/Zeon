INCLUDEDIR=/home/kai/Zeon/include
CC=i686-elf-gcc
CFLAGS=-ffreestanding -g -O2 -isystem $(INCLUDEDIR) -Wall -Wextra -Werror
LIBS=-nostdlib -lgcc

ZEON_OBJS=\
kernel/arch_86/boot.o \
kernel/arch_86/interrupt.o \
kernel/arch_86/gdt.o \
kernel/kernel.o \
kernel/io/tty.o \
kernel/cpu/gdt.o \
kernel/cpu/idt.o \
kernel/cpu/isr.o \
kernel/libc/string.o \

OBJS=\
kernel/arch_86/crti.o \
kernel/arch_86/crtbegin.o \
$(ZEON_OBJS) \
kernel/arch_86/crtend.o \
kernel/arch_86/crtn.o \

LD_LIST=\
kernel/arch_86/crti.o \
kernel/arch_86/crtbegin.o \
$(ZEON_OBJS) \
$(LIBS) \
kernel/arch_86/crtend.o \
kernel/arch_86/crtn.o \

.PHONY: all clean iso run
.SUFFIXES: .c .o .S

all: zeon.kernel

zeon.kernel: $(OBJS) linker.ld
	$(CC) -T linker.ld -o $@ $(CFLAGS) $(LD_LIST)

kernel/arch_86/crtbegin.o kernel/arch_86/crtend.o:
	OBJ=`$(CC) $(CFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

.S.o:
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f zeon.kernel zeon.iso
	rm -rf isodir
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

iso: zeon.kernel
	mkdir -p isodir/boot/grub
	cp zeon.kernel isodir/boot/zeon.kernel
	echo "menuentry \"Zeon OS\" {"		 > isodir/boot/grub/grub.cfg
	echo "	multiboot /boot/zeon.kernel"	>> isodir/boot/grub/grub.cfg
	echo "}"				>> isodir/boot/grub/grub.cfg
	grub-mkrescue -o zeon.iso isodir

run: iso
	qemu-system-i386 -cdrom zeon.iso
