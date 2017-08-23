#include <video/tty.h>

void kmain(void) {
	vga_init();
	vga_puts("Zeon booted successfully!\n");
	vga_puts("1567 in Hexadecimal: ");
	vga_writehex(1567);
	for (;;);
}
