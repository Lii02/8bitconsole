#ifndef CONSOLE_PPU_H
#define CONSOLE_PPU_H
#include <stdint.h>

#define CONSOLE_RESX 512
#define CONSOLE_RESY 512

// Background byte is rarely used
#define BACKGROUND_BYTE 0x0020
#define PIXELS_BYTE_FIRST 0x0021
#define PIXELS_BYTE_LAST 0xF021

#define PPUCTRL vram[0x0]
#define PPUSCROLL vram[0x1]
#define PPUMASK vram[0x2]

typedef struct
{
	float r;
	float g;
	float b;
} ppu_rgb_color;

typedef unsigned char ppu_color;

void initialize_ppu();
void free_ppu();
ppu_rgb_color hex_to_float_rgb(ppu_color b);
void ppu_write(uint16_t address, uint8_t val);
uint8_t ppu_read(uint16_t address);

#endif