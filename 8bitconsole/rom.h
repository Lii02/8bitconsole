#ifndef ROM_H
#define ROM_H

#include <stdint.h>
#include "io.h"

// The EEPROM header is to be written in big endian
typedef struct 
{
	uint32_t signature;
	uint32_t prgm_size;
	uint32_t chr_size;
	uint16_t ram_ext;
	uint16_t entry_point;
} rom_header;

typedef struct
{
	rom_header header;
	uint8_t* prgm;
	uint8_t* chr;
	uint8_t** input_bytes;
} eeprom;

eeprom* load_eeprom(input_file* input);
void free_eeprom(eeprom* rom);

#endif