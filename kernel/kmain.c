#include "kio.h"
#include "kheap.h"

int main(struct multiboot *mboot_ptr) {
	kclrscr();
	kprintf("Hello, world!\n");

	int marker;

	if(kheap_initialize(&marker, &marker + 4096 * 1024) == -1) {
		kprintf("Failed to initialize kernel heap...\n");
		goto __end__;
	}

__end__:
	return 0xDEADBABA;
}
