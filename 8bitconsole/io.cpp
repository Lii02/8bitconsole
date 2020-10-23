#include "io.h"
#include <stdio.h>
#include "mem/memory.h"

input_file* read_rom_file(char* path)
{
	input_file* bc = (input_file*)li_malloc(sizeof(input_file));
	FILE* fptr = fopen(path, "rb");
	if (!fptr)
	{
		return NULL;
	}
	fseek(fptr, 0, SEEK_END);
	bc->length = ftell(fptr);
	rewind(fptr);
	bc->bytes = (uint8_t*)li_malloc(bc->length * sizeof(uint8_t));
	fread((void*)bc->bytes, bc->length, 1, fptr);
	fclose(fptr);
	return bc;
}

void free_input_file(input_file* file)
{
	li_free(file->bytes);
	li_free(file);
}