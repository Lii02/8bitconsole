#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <FreeImage.h>

#pragma comment(lib, "FreeImage.lib")

typedef unsigned char Byte;
typedef Byte* ByteArray;

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("usage: CharCompressor [input file] [output file]\n");
		exit(0);
	}

	FreeImage_Initialise();

	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib = 0;
	Byte* img = 0;
	char* filename = argv[1];
	fif = FreeImage_GetFileType(filename, 0);
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	img = FreeImage_GetBits(dib);
	int width = FreeImage_GetWidth(dib);
	int height = FreeImage_GetHeight(dib);
	if (img == nullptr)
	{
		printf("%s failed to load!\n", filename);
		FreeImage_DeInitialise();
		exit(0);
	}

	char* output_file = argv[2];
	FILE* write_ptr;
	write_ptr = fopen(output_file, "wb");
	
	uint32_t data_length = FreeImage_GetDIBSize(dib);

	fwrite(img, data_length, 1, write_ptr);

	printf("Wrote %d bytes\n", ftell(write_ptr));

	FreeImage_Unload(dib);
	FreeImage_DeInitialise();

	return 0;
}