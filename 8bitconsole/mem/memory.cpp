#include "memory.h"
#include <stdlib.h>

static size_t allocated_memory;
typedef unsigned char byte;

void initialize_memory(void)
{
	allocated_memory = 0x0;
}

size_t get_memory_allocated()
{
	return allocated_memory;
}

void* li_malloc(unsigned int size)
{
	void* ptr = malloc(size);
	allocated_memory += size;
	return ptr;
}

void* li_realloc(void* block, unsigned int new_size)
{
	byte* memory = ((byte*)block) - sizeof(size_t);
	size_t old_size = *(size_t*)memory;
	allocated_memory -= old_size;
	allocated_memory += new_size;
	block = realloc(block, new_size);
	return block;
}


void li_free(void* block)
{
	byte* memory = ((byte*)block) - sizeof(size_t);
	size_t size = *(size_t*)memory;
	allocated_memory -= size;
	free(block);
}