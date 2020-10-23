#include "ppu.h"
#include "mem/memory.h"
#include "cpu/xcpu.h"
#include <stdio.h>
#include "opcode.h"
#include <GL/glew.h>
#include <string.h>

extern stack_t stack;
stack_t vram;

ppu_rgb_color hex_to_float_rgb(ppu_color b)
{
	ppu_rgb_color c;
	c.r = ((b >> 5) * 255 / 7) / 255.0f;
	c.g = (((b >> 2) & 0x07) * 255 / 7) / 255.0f;
	c.b = ((b & 0x03) * 255 / 3) / 255.0f;
	return c;
}

void ppu_write(uint16_t address, uint8_t val)
{
	vram[address] = val;
}

uint8_t ppu_read(uint16_t address)
{
	return vram[address];
}

void initialize_ppu()
{
	vram = (stack_t)li_malloc(VRAM);
	memset(vram, 0, VRAM);
}

void free_ppu()
{
	li_free(vram);
}