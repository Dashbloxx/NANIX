#include "serial.h"
#include "ioport.h"

int serial_initialize(serial_port_t port) {
	outb(port + 1, 0x00);
	outb(port + 3, 0x80);
	outb(port + 0, 0x03);
	outb(port + 1, 0x00);
	outb(port + 3, 0x03);
	outb(port + 2, 0xC7);
	outb(port + 4, 0x0B);
	outb(port + 4, 0x1E);
	outb(port + 0, 0xAE);

	if(inb(port + 0) != 0xAE) {
		return -1;
	}

	outb(port + 4, 0x0F);
	return 0;
}

static int wait_serial(serial_port_t port) {
	return inb(port + 5) & 1;
}

char read_serial(serial_port_t port) {
	while(wait_serial(port) == 0);
	return inb(port);
}

static int wait_to_write(serial_port_t port) {
	return inb(port + 5) & 0x20;
}

void write_serial(serial_port_t port, char data) {
	while(wait_to_write(port) == 0);
	outb(port, data);
}
