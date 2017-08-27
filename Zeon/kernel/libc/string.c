#include <string.h>

void *memset(void *ptr, int val, size_t size) {
	char *buf = (char *) ptr;
	
	for (; size != 0; --size)
		*buf++ = val;
	return ptr;
}
