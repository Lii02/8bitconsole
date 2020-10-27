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

void ppu_render()
{
	draw_buffer(PPUBUFFID);
}

render_buffer* create_render_buffer(int32_t width, int32_t height)
{
	render_buffer* buff = (render_buffer*)li_malloc(sizeof(render_buffer));
	buff->bpp = 3;
	int32_t s = width * height * buff->bpp;
	buff->buffer = (uint8_t*)li_malloc(s);
	memset(buff->buffer, 0, s);
	buff->width = width;
	buff->height = height;
	glGenTextures(1, &buff->id);
	glBindTexture(GL_TEXTURE_2D, buff->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	update_render_buffer(buff);
	return buff;
}

void free_render_buffer(render_buffer* b)
{
	glDeleteTextures(1, &b->id);
	li_free(b->buffer);
	li_free(b);
}

void update_render_buffer(render_buffer* buff)
{
	glBindTexture(GL_TEXTURE_2D, buff->id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, buff->width, buff->height, 0, GL_RGB, GL_UNSIGNED_BYTE, buff->buffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void put_pixel(render_buffer* buff, int32_t x, int32_t y, ppu_rgb_color color)
{
	int32_t position = ((x + y * buff->width) * buff->bpp);
	buff->buffer[position] = color.r;
	buff->buffer[position + 1] = color.g;
	buff->buffer[position + 2] = color.b;
}

void draw_buffer(uint32_t id)
{
	glBindTexture(GL_TEXTURE_2D, id);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}