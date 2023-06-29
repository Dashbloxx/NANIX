#include "kio.h"
#include "kheap.h"
#include "fs.h"
#include "def.h"
#include "str.h"
#include "multiboot.h"

mapped_memory_t mapped_memory;

int main(multiboot_header_t *multiboot_pointer) {
	kclrscr();
	kprintf("NANIX (C) %s, All Rights Reserved.\nBuild compiled during %s.\n", "2023", __DATE__);

	/*switch(kheap_initialize((void *)0, (void *)0)) {
	case -1:
		kprintf("Failed to initialize kernel heap...\n");
                goto __end__;
	default:
		kprintf("Successfully initialized kernel heap!\n");
	}

	switch(fs_initialize()) {
	case -1:
		kprintf("Failed to initialize filesystem...\n");
		goto __end__;
	default:
		kprintf("Successfully initialized the filesystem!\n");
	}*/

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
