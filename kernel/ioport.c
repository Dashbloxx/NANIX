#include "ioport.h"

unsigned char inb(unsigned short int port) {
	unsigned char data;
	asm volatile("inb %w1, %b0" : "=a"(data) : "Nd"(port));
	return data;
}

void outb(unsigned short int port, unsigned char data) {
	asm volatile("outb %b0, %w1" : : "a"(data), "Nd"(port));
}

unsigned short int inw(unsigned short int port) {
	unsigned short int data;
	asm volatile("inw %w1, %w0" : "=a"(data) : "Nd"(port));
	return data;
}

void outw(unsigned short int port, unsigned short int data) {
	asm volatile("outw %w0, %w1" : : "a"(data), "Nd"(port));
}

unsigned int inl(unsigned short int port) {
	unsigned int data;
	asm volatile("inl %w1, %0" : "=a"(data) : "Nd"(port));
	return data;
}

void outl(unsigned short int port, unsigned int data) {
	asm volatile("outl %0, %w1" : : "a"(data), "Nd"(port));
}
