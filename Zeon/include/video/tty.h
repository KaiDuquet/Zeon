#ifndef _KERN_TTY_H
#define _KERN_TTY_H

#include <stddef.h>
#include <stdint.h>

enum vga_color {
	VGA_BLACK		= 0,
	VGA_BLUE		= 1,
	VGA_GREEN		= 2,
	VGA_CYAN		= 3,
	VGA_RED			= 4,
	VGA_MAGENTA		= 5,
	VGA_BROWN		= 6,
	VGA_LIGHT_GREY		= 7,
	VGA_DARK_GREY		= 8,
	VGA_LIGHT_BLUE		= 9,
	VGA_LIGHT_GREEN 	= 10,
	VGA_LIGHT_CYAN		= 11,
	VGA_LIGHT_RED		= 12,
	VGA_LIGHT_MAGENTA 	= 13,
	VGA_LIGHT_BROWN		= 14,
	VGA_WHITE		= 15
};

void vga_init(void);
void vga_putchar(char c);
void vga_puts(const char *data);
void vga_writehex(uint32_t num);
void vga_writedec(uint32_t num);
// void vga_writedigit(uint8_t digit);
// void vga_scroll(void);
void vga_clear(void);
// void vga_movecsr(void);

#endif
