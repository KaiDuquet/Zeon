#include <video/tty.h>
#include <cpu/gdt.h>
#include <cpu/idt.h>

void kmain(void) {
	
	vga_init();
	vga_puts("Initialized VGA Buffer successfully! Loading GDT...\n");
	init_gdt();
	vga_puts("Initialized and Loaded GDT Successfully! Loading IDT...\n");
	init_idt();
	vga_puts("Initialized and Loaded IDT Successfully!\n");
	asm volatile("int $0x0");
	for (;;);
}
