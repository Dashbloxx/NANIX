#pragma once

typedef struct {
	unsigned short int limit_low : 16;
	unsigned short int base_low : 16;
	unsigned char base_middle : 8;
	unsigned char access : 8;
	unsigned char limit_high : 4;
	unsigned char flags : 4;
	unsigned char base_high : 8;
} __attribute__((packed)) gdt_t;

typedef struct {
	unsigned short int limit;
	unsigned int base;
} __attribute__((packed)) gdt_pointer_t;

void gdt_entry(unsigned int index, unsigned int base, unsigned int limit, unsigned char access, unsigned char flags);
void gdt_initialize();
