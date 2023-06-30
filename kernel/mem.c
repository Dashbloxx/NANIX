#include "mem.h"

void *memset(void *s, int c, unsigned int length) {
	unsigned char *p = s;
	while(length--) {
		*p = (unsigned char)c;
	}
	return s;
}
