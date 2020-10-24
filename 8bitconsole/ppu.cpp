#include "ppu.h"
#include "mem/memory.h"
#include "cpu/xcpu.h"
#include <stdio.h>
#include <opcode.h>
#include <GL/glew.h>
#include <string.h>

extern stack_t stack;
stack_t vram;

ppu_rgb_color hex_to_float_rgb(ppu_color b)
{
	ppu_rgb_color c;
	c.r = ((b >> 5) * 255 / 7);
	c.g = (((b >> 2) & 0x07) * 255 / 7);
	c.b = ((b & 0x03) * 255 / 3);
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

render_buffer* create_render_buffer(int32_t width, int32_t height, int8_t bpp)
{
	render_buffer* buffer = (render_buffer*)li_malloc(sizeof(render_buffer));
	int32_t s = width * height * bpp;
	buffer->buffer = (uint8_t*)li_malloc(s);
	memset(buffer->buffer, 0, s);
	buffer->width = width;
	buffer->height = height;
	buffer->bpp = bpp;
	return buffer;
}

void free_render_buffer(render_buffer* b)
{
	li_free(b->buffer);
	li_free(b);
}

void put_pixel(render_buffer* buff, int32_t x, int32_t y, ppu_color color)
{
	if (0 <= x && x < buff->width && 0 <= y && y < buff->height)
	{
		ppu_rgb_color col = hex_to_float_rgb(color);
		int32_t position = (x + y * buff->width) * buff->bpp;
		buff->buffer[position] = (uint8_t)col.r;
		buff->buffer[position + 1] = (uint8_t)col.g;
		buff->buffer[position + 2] = (uint8_t)col.b;
	}
}

void draw_buffer(render_buffer* buff)
{
	glDrawPixels(buff->width, buff->height, GL_RGB, GL_UNSIGNED_BYTE, buff->buffer);
}