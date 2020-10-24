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

// 0-255 color
typedef struct
{
	int32_t r;
	int32_t g;
	int32_t b;
} ppu_rgb_color;

struct render_buffer
{
	uint8_t* buffer;
	int32_t width;
	int32_t height;
	int8_t bpp;
};

typedef unsigned char ppu_color;

void initialize_ppu();
void free_ppu();
ppu_rgb_color hex_to_float_rgb(ppu_color b);
void ppu_write(uint16_t address, uint8_t val);
uint8_t ppu_read(uint16_t address);
render_buffer* create_render_buffer(int32_t width, int32_t height, int8_t bpp);
void free_render_buffer(render_buffer* b);
void put_pixel(render_buffer* buff, int32_t x, int32_t y, ppu_color color);
void draw_buffer(render_buffer* buff);

#endif