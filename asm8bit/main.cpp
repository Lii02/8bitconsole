#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "structs.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("usage: asm8bit [file]\n");
		exit(0);
	}

	FILE* fptr = fopen(argv[1], "r");
	if (!fptr)
	{
		printf("%s failed to load\n", argv[1]);
		exit(0);
	}
	fseek(fptr, 0, SEEK_END);
	size_t flength = ftell(fptr);
	rewind(fptr);
	char* file_str = (char*)malloc(flength * sizeof(char));
	fread((void*)file_str, flength, 1, fptr);
	fclose(fptr);

	handler* handle = create_handler();

	free_handler(handle);
	free(file_str);
	return 0;
}