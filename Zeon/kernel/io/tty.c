#include <video/tty.h>
#include <io/io.h>

static uint16_t *const VGA_MEM = (uint16_t*) 0xB8000;

static size_t vga_x;
static size_t vga_y;
static uint8_t vga_color;
static uint16_t *vga_buf;

uint8_t vga_mkcolor(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t vga_mkentry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

void vga_scroll(void) {
	uint8_t attrib = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attrib << 8);

	if (vga_y >= 25) {
		int i;
		for (i = 0; i < 24 * 80; i++) {
			vga_buf[i] = vga_buf[i + 80];
		}

		for (i = 24 * 80; i < 25 * 80; i++) {
			vga_buf[i] = blank;
		}
		vga_y = 24;
	}
}

void vga_movecsr(void) {
	uint16_t i = vga_y * 80 + vga_x;

	outb(0x3D4, 14);
	outb(0x3D5, i >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, i);
}

void vga_writedigit(uint8_t digit) {
	vga_putchar('0' + digit);
}

void vga_writedec(uint32_t num) {
	if (num == 0) {
		vga_writedigit(0);
		return;
	}
	
	uint32_t rev = 0;
	while (num > 0) {
		rev = rev * 10 + num % 10;
		num /= 10;
	}

	while (rev > 0) {
		vga_writedigit(rev % 10);
		rev /= 10;
	}
}

void vga_writehex(uint32_t num) {
	char *ref = "0123456789ABCDEF";
	char buf[10];
	buf[9] = 0;
	uint8_t i = 8;
	while (num > 0) {
		buf[i--] = ref[num % 16];
		num /= 16;
	}
	vga_puts("0x");
	vga_puts(&buf[i + 1]);
}

void vga_putchar(char c) {
	
	if (c == '\n') {
		vga_x = 0;
		vga_y ++;
	} 
	else if (c == '\r') { 
		vga_x = 0;
	}
	else if (c == 0x08 && vga_x) {
       		vga_x--;
   	}
	else if (c == 0x09) {
       		vga_x = (vga_x+8) & ~(8-1);
   	}
	else {
		unsigned char uc = c;
		vga_buf[(size_t)(vga_y * 80 + vga_x)] = vga_mkentry(uc, vga_color);
		vga_x++;
	}

	if (vga_x > 80) {
		vga_x = 0;
		vga_y ++;
	}

	vga_scroll();
	vga_movecsr();
}

void vga_puts(const char *str) {
    	int i = 0;
	while (str[i]) {
		vga_putchar(str[i++]);
	}
}

void vga_clear(void) {
	uint8_t attrib = (0 << 4) | (15 & 0x0F);
	uint16_t blank = 0x20 | (attrib << 8);

	for (int i = 0; i < 80 * 25; i++) {
		vga_buf[i] = blank;
	}

	vga_x = 0;
	vga_y = 0;
	vga_movecsr();
}

void vga_init(void) {
	vga_x = 0;
	vga_y = 0;
	vga_color = vga_mkcolor(VGA_LIGHT_GREY, VGA_BLACK);
	vga_buf = VGA_MEM;
	vga_clear();
}

/* Port I/O (Assembly in/out) */

void outb(uint16_t port, uint8_t v) {
	asm volatile("outb %1, %0" : : "Nd" (port), "a" (v));
}

uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "Nd" (port));
	return ret;
}

void outw(uint16_t port, uint16_t v) {
	asm volatile("outw %1, %0" : : "Nd" (port), "a" (v));
}

uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile("inw %1, %0" : "=a" (ret) : "Nd" (port));
	return ret;
}

void outl(uint16_t port, uint32_t v) {
	asm volatile("outl %1, %0" : : "Nd" (port), "a" (v));
}

uint32_t inl(uint16_t port) {
	uint32_t ret;
	asm volatile("inl %1, %0" : "=a" (ret) : "Nd" (port));
	return ret;
}
