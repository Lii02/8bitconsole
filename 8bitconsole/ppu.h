#ifndef CONSOLE_PPU_H
#define CONSOLE_PPU_H
#include <stdint.h>

#define CONSOLE_RESX 512
#define CONSOLE_RESY 512

#define PPUCTRL vram[0x0]
#define PPUSCROLLX vram[0x1]
#define PPUSCROLLY vram[0x2]
#define PPUMASK vram[0x3]
#define PPUBUFFID vram[0x4]
#define PPUCHRLEN vram[0x5]

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
	uint8_t bpp;
	uint32_t id;
};

typedef unsigned char ppu_color;

void initialize_ppu();
void free_ppu();
void ppu_render();
ppu_rgb_color hex_to_float_rgb(ppu_color b);
void ppu_write(uint16_t address, uint8_t val);
uint8_t ppu_read(uint16_t address);
render_buffer* create_render_buffer(int32_t width, int32_t height);
void free_render_buffer(render_buffer* b);
void update_render_buffer(render_buffer* buff);
void put_pixel(render_buffer* buff, int32_t x, int32_t y, ppu_color color);
void draw_buffer(uint32_t id);

#endif