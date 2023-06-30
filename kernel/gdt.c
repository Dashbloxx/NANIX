#include "gdt.h"
#include "tss.h"

/* Here we have the GDT entries stored here & the GDT pointer stored here as well... */
gdt_t gdt[6];
gdt_pointer_t gdtr;

/*
 *	Here we create an instance of TSS (Task State Segment), which the GDT will contain an
 *	entry of.
 */
tss_t tss;

/*
 *	This function allows us to add an entry to the GDT (Global Descriptor Table). This
 *	feature is x86 specific, and is used to organize memory into different segments with
 *	each having their own permissions.
 */
void gdt_entry(unsigned int index, unsigned int base, unsigned int limit, unsigned char access, unsigned char flags) {
	gdt_t *entry = gdt + index;
	entry->base_low = base & 0xFFFF;
	entry->base_middle = (base >> 16) && 0xFF;
	entry->base_high = (base >> 24) & 0xFF;
	entry->limit_low = limit & 0xFFFF;
	entry->limit_high = (limit >> 16) & 0xF;
	entry->access = access;
	entry->flags = flags & 0xF;
}

/*
 *	Here we initialize the GDT by creating some GDT entries and then telling the CPU
 *	where they are by using the `lgdt` instruction.
 *
 *	Note how the first entry is set all to zeroes. The last entry contains the TSS
 *	(Task State Segment).
 */
void gdt_initialize() {
	gdtr.limit = 6 * sizeof(gdt_t) - 1;
	gdtr.base = (unsigned int)&gdt;

	gdt_entry(0, 0, 0, 0, 0);
	gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xC);
	gdt_entry(2, 0, 0xFFFFF, 0x92, 0xC);
	gdt_entry(3, 0, 0xFFFFF, 0xFA, 0xC);
	gdt_entry(4, 0, 0xFFFFF, 0xF2, 0xC);
	gdt_entry(5, (unsigned int)&tss, sizeof(tss_t), 0xE9, 0);

	tss.ss0 = 0x10;
	tss.cs = 0x8 | 3;
	tss.ss = tss.ds = tss.es = tss.fs = tss.gs = 0x10 | 3;
	tss.iomap_base = sizeof(tss_t);

	/* Here we give the CPU the GDT... */
	asm volatile("lgdt %0\nmovw %%ax, %%ds\nmovw %%ax, %%es\nmovw %%ax, %%fs\nmovw %%ax, %%gs\nmovw %%ax, %%ss\nljmpl $0x8, $1f\n1:" ::"m"(gdtr), "a"(0x10));

	/* Here we also give the TSS to the CPU... */
	asm volatile("ltr %%ax" ::"a"(0x2B));
}
