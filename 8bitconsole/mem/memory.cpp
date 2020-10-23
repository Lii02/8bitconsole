#include "memory.h"
#include <stdlib.h>

size_t memory_header;
typedef unsigned char byte;

void initialize_memory()
{
	memory_header = 0x0;
}

size_t get_memory_allocated()
{
	return memory_header;
}

void* li_malloc(unsigned int size)
{
	void* ptr = malloc(size);
	memory_header += size;
	return ptr;
}

void* li_realloc(void* block, unsigned int new_size)
{
	memory_header += new_size;
	block = realloc(block, new_size);
	return block;
}


void li_free(void* block)
{
	byte* memory = ((byte*)block) - sizeof(size_t);
	size_t size = *(size_t*)memory;
	memory_header -= size;
	free(block);
}