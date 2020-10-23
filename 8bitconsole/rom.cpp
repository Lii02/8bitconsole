#include "rom.h"
#include <cstring>
#include <opcode.h>
#include "cpu/xcpu.h"
#include "mem/memory.h"
#include <stdio.h>

extern xregister registers[REGISTER_COUNT];

#define IP_DEF registers[INDEX_PTR].r8_ptr

eeprom* load_eeprom(input_file* input)
{
	eeprom* rom = (eeprom*)li_malloc(sizeof(eeprom));
	memset(rom, 0, sizeof(eeprom));
	registers[INDEX_PTR].r8_ptr = input->bytes;
	rom->header.signature = swap_4_bytes(EEPROM_GET_INT());
	if (rom->header.signature != ROM_SIGNATURE)
	{
		printf("EEPROM header signature is incorrect.\n");
	}
	rom->header.prgm_size = EEPROM_GET_INT();
	rom->prgm = (uint8_t*)li_malloc(rom->header.prgm_size);

	rom->header.chr_size = EEPROM_GET_INT();
	rom->chr = (uint8_t*)li_malloc(rom->header.chr_size);
	
	rom->header.ram_ext = EEPROM_GET_SHORT();
	rom->header.entry_point = EEPROM_GET_SHORT();
	
	unsigned int i;
	for (i = 0; i < rom->header.prgm_size; i++)
	{
		rom->prgm[i] = EEPROM_GET_BYTE();
		INCREASE_IP(1);
	}

	for (i = 0; i < rom->header.chr_size; i++)
	{
		rom->chr[i] = EEPROM_GET_BYTE();
		INCREASE_IP(1);
	}
	rom->input_bytes = &input->bytes;
	SET_INDEX_AFTER_HEADER(rom, rom->header.entry_point);

	return rom;
}

void free_eeprom(eeprom* rom)
{
	li_free(rom->prgm);
	li_free(rom->chr);
	li_free(rom);
}