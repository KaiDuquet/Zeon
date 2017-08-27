#include <cpu/gdt.h>

extern void gdt_flush(uint32_t);
static void gdt_set_gate(gdt_entry_t *desc, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

void init_gdt(void) {
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base = (uint32_t) &gdt_entries;

	gdt_set_gate(&gdt_entries[0], 0, 0, 0, 0);
	gdt_set_gate(&gdt_entries[1], 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(&gdt_entries[2], 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(&gdt_entries[3], 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(&gdt_entries[4], 0, 0XFFFFFFFF, 0xF2, 0xCF);

	gdt_flush((uint32_t) &gdt_ptr);
}

static void gdt_set_gate(gdt_entry_t *desc, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
	desc->base_low 		= (base & 0xFFFF);
	desc->base_middle 	= (base >> 16) & 0xFF;
	desc->base_high 	= (base >> 24) & 0xFF;
	
	desc->limit_low 	= (limit & 0xFFFF);
	desc->granularity 	= (limit >> 16) & 0x0F;

	desc->granularity 	|= gran & 0xF0;
	desc->access 		= access;
}
