#ifndef ASM8BIT_STRUCTS_H
#define ASM8BIT_STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct
{
	const char* path;
	unsigned int line;
} srcdata_t;

inline srcdata_t create_srcdata(const char* path, unsigned int line)
{
	srcdata_t src;
	src.path = path;
	src.line = line;
	return src;
}

typedef struct
{
	int errors;
	int warnings;
	bool give_warnings;
} handler;

inline handler* create_handler()
{
	handler* h = (handler*)malloc(sizeof(handler));
	memset(h, 0, sizeof(handler));
	return h;
}

inline void free_handler(handler* h)
{
	free(h);
}

void report_error(handler* h, const char* message, srcdata_t src)
{
	h->errors++;
	printf("asm(%s:%d): %s\n", src.path, src.line, message);
}

typedef struct
{
	srcdata_t data;
	char* str;
	int16_t flag;
} token_t;

#endif