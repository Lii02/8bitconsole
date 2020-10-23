#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("RomPackager [.byte file] [.chr file] [output file]\n");
		exit(0);
	}

	char* byte_filep = argv[1];
	char* chr_filep = argv[2];
	char* output_flep = argv[3];

	return 0;
}