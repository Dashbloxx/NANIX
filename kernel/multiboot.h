#pragma once

typedef struct {
	unsigned int flags;
	unsigned int mem_lower;
	unsigned int mem_upper;
	unsigned int boot_device;
	unsigned int cmdline;
	unsigned int mods_count;
	unsigned int mods_address;
	unsigned int num;
	unsigned int size;
	unsigned int addr;
	unsigned int mmap_length;
	unsigned int mmap_address;
	unsigned int drives_length;
	unsigned int drives_address;
	unsigned int config_table;
	unsigned int boot_loader_name;
	unsigned int apm_table;
	unsigned int vbe_control_info;
	unsigned int vbe_mode_info;
	unsigned int vbe_interface_seg;
	unsigned int vbe_interface_off;
	unsigned int vbe_interface_len;
} __attribute__((packed)) multiboot_header_t;
