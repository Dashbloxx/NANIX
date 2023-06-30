#pragma once

typedef struct {
	unsigned int prev_tss;
	unsigned int esp0, ss0, esp1, ss1, esp2, ss2;
	unsigned int cr3;
	unsigned int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	unsigned int es, cs, ss, ds, fs, gs;
	unsigned int ldt;
	unsigned short int trap, iomap_base;
} __attribute__((packed)) tss_t;
