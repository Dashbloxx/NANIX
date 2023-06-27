#include "kheap.h"
#include "kio.h"
#include "def.h"

void *kheap_start_address = NULL, *kheap_end_address = NULL;
unsigned int kheap_total_size = 0, kheap_total_used_size = 0;

kheap_segment_t *kheap_head = NULL;

int kheap_initialize(void *start_address, void *end_address) {
	if(start_address > end_address) {
		kprintf("Failed to initialize kernel heap...\n");
		return -1;
	}

	kheap_start_address = start_address;
	kheap_end_address = end_address;
	kheap_total_size = end_address - start_address;
	kheap_total_used_size = 0;
	return 0;
}

void *kbrk(int size) {
	void *address = NULL;
	if(size <= 0)
		return NULL;

	if((int)(kheap_total_size - kheap_total_used_size) <= size)
		return NULL;

	address = kheap_start_address + kheap_total_used_size + size;
	kheap_total_used_size += size + sizeof(void *);
	return address;
}

int kheap_is_free(kheap_segment_t *block) {
	if(!block)
		return 0;
	return (block->is_free == 1);
}

kheap_segment_t *kheap_worst_fit(int size) {
	kheap_segment_t *temp = kheap_head;
	while(temp != NULL) {
		if(kheap_is_free(temp)) {
			if((int)temp->size >= size)
				return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

kheap_segment_t *kheap_allocate_new_block(int size) {
	kheap_segment_t *temp = kheap_head;
	while(temp->next != NULL) {
		temp = temp->next;
	}

	kheap_segment_t *new_block = (kheap_segment_t *)kbrk(sizeof(kheap_segment_t));
	new_block->is_free = 0;
	new_block->size = size;
	new_block->data = kbrk(size);
	new_block->next = NULL;
	temp->next = new_block;
	return new_block;
}

void *kmalloc(int size) {
	if(size <= 0)
		return NULL;
	if(kheap_head == NULL) {
		kheap_head = (kheap_segment_t *)kbrk(sizeof(kheap_segment_t));
		kheap_head->is_free = 0;
		kheap_head->size = size;
		kheap_head->next = NULL;
		kheap_head->data = kbrk(size);
		return kheap_head->data;
	} else {
		kheap_segment_t *worst = kheap_worst_fit(size);
		if(worst == NULL) {
			kheap_segment_t *new_block = kheap_allocate_new_block(size);
			new_block->is_free = 0;
			new_block->size = size;
			new_block->data = kbrk(size);
			return new_block->data;
		} else {
			worst->is_free = 0;
			return worst->data;
		}
	}
	return NULL;
}

void kfree(void *address) {
	kheap_segment_t *temp = kheap_head;
	while(temp != NULL) {
		if(temp->data == address) {
			temp->is_free = 1;
			return;
		}
		temp = temp->next;
	}
}
