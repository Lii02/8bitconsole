#pragma once
#include <stdint.h>

typedef struct
{
	uint8_t* bytes;
	uint32_t length;
} input_file;

input_file* read_rom_file(char* path);
void free_input_file(input_file* file);