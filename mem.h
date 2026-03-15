#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include "types.h"

typedef union header {
	struct {
		size_t size;
		unsigned is_free;
		union header* next;
	} s;
	long stub;
} header_t;

extern header_t *head;
extern header_t *tail;
extern void* __heap_end;

void* setbrk(long increment);
void* my_malloc(size_t size);
void my_free(void* block);
header_t* my_get_free_block(size_t size);

#endif