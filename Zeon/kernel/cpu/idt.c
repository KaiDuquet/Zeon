#include <cpu/idt.h>
#include <string.h>

extern void idt_flush(uint32_t);
static void idt_set_gate(idt_entry_t *idt, uint32_t, uint16_t, uint8_t);

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void init_idt(void) {
	idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
	idt_ptr.base = (uint32_t) &idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entry_t) * 256);

	idt_set_gate(&idt_entries[0], (uint32_t) isr0, 0x08, 0x8E);
	idt_set_gate(&idt_entries[1], (uint32_t) isr1, 0x08, 0x8E);
	idt_set_gate(&idt_entries[2], (uint32_t) isr2, 0x08, 0x8E);
	idt_set_gate(&idt_entries[3], (uint32_t) isr3, 0x08, 0x8E);
	idt_set_gate(&idt_entries[4], (uint32_t) isr4, 0x08, 0x8E);
	idt_set_gate(&idt_entries[5], (uint32_t) isr5, 0x08, 0x8E);
	idt_set_gate(&idt_entries[6], (uint32_t) isr6, 0x08, 0x8E);
	idt_set_gate(&idt_entries[7], (uint32_t) isr7, 0x08, 0x8E);
	idt_set_gate(&idt_entries[8], (uint32_t) isr8, 0x08, 0x8E);
	idt_set_gate(&idt_entries[9], (uint32_t) isr9, 0x08, 0x8E);
	idt_set_gate(&idt_entries[10], (uint32_t) isr10, 0x08, 0x8E);
	idt_set_gate(&idt_entries[11], (uint32_t) isr11, 0x08, 0x8E);
	idt_set_gate(&idt_entries[12], (uint32_t) isr12, 0x08, 0x8E);
	idt_set_gate(&idt_entries[13], (uint32_t) isr13, 0x08, 0x8E);
	idt_set_gate(&idt_entries[14], (uint32_t) isr14, 0x08, 0x8E);
	idt_set_gate(&idt_entries[15], (uint32_t) isr15, 0x08, 0x8E);
	idt_set_gate(&idt_entries[16], (uint32_t) isr16, 0x08, 0x8E);
	idt_set_gate(&idt_entries[17], (uint32_t) isr17, 0x08, 0x8E);
	idt_set_gate(&idt_entries[18], (uint32_t) isr18, 0x08, 0x8E);
	idt_set_gate(&idt_entries[19], (uint32_t) isr19, 0x08, 0x8E);
	idt_set_gate(&idt_entries[20], (uint32_t) isr20, 0x08, 0x8E);
	idt_set_gate(&idt_entries[21], (uint32_t) isr21, 0x08, 0x8E);
	idt_set_gate(&idt_entries[22], (uint32_t) isr22, 0x08, 0x8E);
	idt_set_gate(&idt_entries[23], (uint32_t) isr23, 0x08, 0x8E);
	idt_set_gate(&idt_entries[24], (uint32_t) isr24, 0x08, 0x8E);
	idt_set_gate(&idt_entries[25], (uint32_t) isr25, 0x08, 0x8E);
	idt_set_gate(&idt_entries[26], (uint32_t) isr26, 0x08, 0x8E);
	idt_set_gate(&idt_entries[27], (uint32_t) isr27, 0x08, 0x8E);
	idt_set_gate(&idt_entries[28], (uint32_t) isr28, 0x08, 0x8E);
	idt_set_gate(&idt_entries[29], (uint32_t) isr29, 0x08, 0x8E);
	idt_set_gate(&idt_entries[30], (uint32_t) isr30, 0x08, 0x8E);
	idt_set_gate(&idt_entries[31], (uint32_t) isr31, 0x08, 0x8E);
	
	idt_flush((uint32_t) &idt_ptr);
}

static void idt_set_gate(idt_entry_t *idt, uint32_t base, uint16_t sel, uint8_t flags) {
	idt->base_low 	= base & 0xFFFF;
	idt->base_high 	= (base >> 16) & 0xFFFF;

	idt->sel 	= sel;
	idt->zero 	= 0;

	idt->flags 	= flags /* | 0x60 */;
}
