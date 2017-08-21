INCLUDEDIR=/home/kai/Zeon/include
CC=i686-elf-gcc
CFLAGS=-ffreestanding -g -O2 -isystem=$(INCLUDEDIR) -Wall -Wextra
LIBS=-nostdlib -lgcc

ZEON_OBJS=\
boot/boot.o \

OBJS=\
$(ZEON_OBJS) \

LD_LIST=\
$(OBJS) \
$(LIBS) \

.PHONY: all clean iso
.SUFFIXES: .c .o .S

all: zeon.kernel

zeon.kernel: $(OBJS) linker.ld
	$(CC) -T linker.ld -o $@ $(CFLAGS) $(LD_LIST)

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
	./buildiso.sh
