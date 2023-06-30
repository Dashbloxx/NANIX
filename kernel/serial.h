#pragma once

typedef enum {
	com1 = 0x3F8,
	com2 = 0x2F8,
	com3 = 0x3E8,
	com4 = 0x2E8,
	com5 = 0x5F8,
	com6 = 0x4F8,
	com7 = 0x5E8,
	com8 = 0x4E8
} serial_port_t;

int serial_initialize(serial_port_t port);
char read_serial(serial_port_t port);
void write_serial(serial_port_t port, char data);
