#pragma once

typedef struct _kheap_segment_t {
	unsigned int size;
	unsigned char is_free;
	struct _kheap_segment_t *next;
	void *data;
} __attribute__((packed)) kheap_segment_t;

int kheap_initialize(void *start_address, void *end_address);
void *kbrk(int size);
int kheap_is_free(kheap_segment_t *block);
kheap_segment_t *kheap_worst_fit(int size);
kheap_segment_t *kheap_allocate_new_block(int size);
void *kmalloc(int size);
void kfree(void *address);
