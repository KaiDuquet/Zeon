#include <cpu/isr.h>
#include <video/tty.h>

void isr_handler(registers_t regs) {
	vga_puts("Recieved Interrupt: ");
	vga_writedec(regs.int_no);
	vga_puts("\n");
}
