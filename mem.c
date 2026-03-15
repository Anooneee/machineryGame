#include "mem.h"
#include <stdio.h>

#define HEAP_SIZE 128000

header_t *head = NULL;
header_t *tail = NULL;

UINT8 heap[HEAP_SIZE];

void* heap_end = heap;

/* based on https://mohitmishra786.github.io/chessman/2024/11/24/Everything-About-Memory-Allocators-Write-a-simple-memory-allocator.html */


void* setbrk(long increment) {
	void* old_heap = heap_end;

	if ((char*)heap_end + increment > (char*)heap + HEAP_SIZE) {
		return (void*)(-1);
	}
	heap_end = (char*)heap_end + increment;
	return old_heap;
}

void* my_malloc(size_t size) {
	header_t *header;
	void *block;

	if (!size) {
		return NULL;
	}

	size = (size + 3) & ~3;

	header = my_get_free_block(size);

	if (header) {
		header->s.is_free = 0;
		return (header+1);
	}

	block = setbrk(sizeof(header_t) + size);
	if (block == (void*)-1) {
		return NULL;
	}

	header = (header_t*)block;

	header->s.size = size;
	header->s.is_free = 0;
	header->s.next = NULL;

	if (!head) {
		head = header;
	}

	if (tail) {
		tail->s.next = header;
	}

	tail = header;

	return (header+1);
}

void my_free(void* block) {
	header_t *header;
	header_t *temp;
	void *programbreak;

	if (!block) return;

	header = ((header_t*)block) - 1;

	programbreak = setbrk(0);

	if ((char*)block + header->s.size == programbreak) {
		if (head == tail) {
			head = NULL;
			tail = NULL;
		}
		else {
			temp = head;
			while (temp) {
				if (temp->s.next == tail) {
					temp->s.next = NULL;
					tail = temp;
					break;
				}
				temp = temp->s.next;
			}
		}

		setbrk(-(sizeof(header_t) + header->s.size));
	}
	else {
		header->s.is_free = 1;
	}
}

header_t* my_get_free_block(size_t size) {
	header_t *current;
	header_t *bestFit;

	current = head;
	bestFit = NULL;
	while (current) {
		if (current->s.is_free && current->s.size >= size) {
			if (!bestFit || bestFit->s.size > current->s.size) {
				bestFit = current;
			}
		}

		current = current->s.next;
	}

	return (bestFit) ? bestFit : NULL;
}

void greenbob() {
	header_t* current = head;

	while (current) {
		printf("%lu ",current->s.size);
		printf("%u\n",current->s.is_free);
		current = current->s.next;
	}
}