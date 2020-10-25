#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <opcode.h>

typedef unsigned char Byte;

#define WRITE_TO_PTR(data, size) fwrite(data, size, 1, write_ptr);

typedef struct
{
	uint8_t* bytes;
	uint32_t length;
} input_file;

input_file* read_file(char* path)
{
	input_file* bc = (input_file*)malloc(sizeof(input_file));
	FILE* fptr = fopen(path, "rb");
	if (!fptr)
	{
		return NULL;
	}
	fseek(fptr, 0, SEEK_END);
	bc->length = ftell(fptr);
	rewind(fptr);
	bc->bytes = (uint8_t*)malloc(bc->length * sizeof(uint8_t));
	fread((void*)bc->bytes, bc->length, 1, fptr);
	fclose(fptr);
	return bc;
}

void free_input_file(input_file* file)
{
	free(file->bytes);
	free(file);
}

#define swap_4_bytes(val) \
((((val) >> 24) & 0x000000FF) | (((val) >> 8) & 0x0000FF00) | \
	(((val) << 8) & 0x00FF0000) | (((val) << 24) & 0xFF000000))

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		printf("RomPackager [.byte file] [.chr file] [output file]\n");
		exit(0);
	}

	char* byte_filep = argv[1];
	input_file* bytefile = read_file(byte_filep);
	if (!bytefile)
	{
		printf("%s failed to load!\n", byte_filep);
		exit(0);
	}
	char* chr_filep = argv[2];
	input_file* chr_file = read_file(chr_filep);
	if (!chr_file)
	{
		printf("%s failed to load!\n", chr_filep);
		exit(0);
	}
	char* output_filep = argv[3];

	FILE* write_ptr = fopen(output_filep, "wb");
	int32_t sig = swap_4_bytes(ROM_SIGNATURE);
	WRITE_TO_PTR((Byte*)&sig, 4);

	WRITE_TO_PTR((Byte*)&bytefile->length, 4);
	WRITE_TO_PTR((Byte*)&chr_file->length, 4);
	int16_t ram_ext = 0;
	WRITE_TO_PTR((Byte*)&ram_ext, 2);
	int16_t entry_point = 0;
	WRITE_TO_PTR((Byte*)&entry_point, 2);

	WRITE_TO_PTR(bytefile->bytes, bytefile->length);
	WRITE_TO_PTR(chr_file->bytes, chr_file->length);

	printf("Wrote %d bytes into %s", ftell(write_ptr), output_filep);
	free_input_file(bytefile);
	free_input_file(chr_file);
	return 0;
}