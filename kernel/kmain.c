#include "kio.h"
#include "def.h"
#include "str.h"
#include "multiboot.h"
#include "gdt.h"
#include "serial.h"

mapped_memory_t mapped_memory;

int main(multiboot_header_t *multiboot_pointer) {
	kclrscr();
	kprintf("NANIX (C) %s, All Rights Reserved.\nCompiled during %s.\n", "2023", __DATE__);

	/*
	 *	Initialize the GDT (Global Descriptor Table), which is an x86-specific thing
	 *	which allows us to place specific permission properties to different segments
	 *	of memory...
	 */
	gdt_initialize();

	switch(serial_initialize(com1)) {
	case -1:
		kprintf("Failed to initialize serial driver...\n");
		goto __end__;
	default:
		kprintf("Successfully initialized serial driver...\n");
	}

	/*
	 *	Let's set the initrd values of mapped_memory, which is a
	 *	struct that describes to us the different segments in memory
	 *	and what they're for...
	 */
	mapped_memory.initrd_location = *((unsigned int *)multiboot_pointer->mods_address);
	mapped_memory.initrd_end = *(unsigned int *)(multiboot_pointer->mods_address + 4);

__end__:
	return 0xDEADBABA;
}
