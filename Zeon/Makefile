INCLUDEDIR=/home/kai/Zeon/include
CC=i686-elf-gcc
CFLAGS=-ffreestanding -g -O2 -isystem $(INCLUDEDIR) -Wall -Wextra -Werror
LIBS=-nostdlib -lgcc

ZEON_OBJS=\
kernel/boot/boot.o \
kernel/kernel.o \
kernel/io/tty.o \

OBJS=\
kernel/boot/crti.o \
kernel/boot/crtbegin.o \
$(ZEON_OBJS) \
kernel/boot/crtend.o \
kernel/boot/crtn.o \

LD_LIST=\
kernel/boot/crti.o \
kernel/boot/crtbegin.o \
$(ZEON_OBJS) \
$(LIBS) \
kernel/boot/crtend.o \
kernel/boot/crtn.o \

.PHONY: all clean iso run
.SUFFIXES: .c .o .S

all: zeon.kernel

zeon.kernel: $(OBJS) linker.ld
	$(CC) -T linker.ld -o $@ $(CFLAGS) $(LD_LIST)

kernel/boot/crtbegin.o kernel/boot/crtend.o:
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
