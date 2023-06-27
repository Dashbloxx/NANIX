#include "kio.h"

int main(struct multiboot *mboot_ptr) {
	kclrscr();
	kprintf("Hello, world!");
	return 0xDEADBABA;
}
