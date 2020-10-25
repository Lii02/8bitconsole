#ifndef BOARD_IC_H
#define BOARD_IC_H
#include <stdint.h>

typedef struct
{
	int8_t index;
	union
	{
		int8_t value;
		int8_t* value_ptr;
	};
} ic_pin_t;

typedef void(*ICFUN)(ic_pin_t*);

typedef struct
{
	int8_t pin_count;
	ic_pin_t* pins;
	const char* tag;
	ICFUN func;
} ic_t;

ic_t* create_integrated_chip(const char* tag, int8_t pin_count, ICFUN func);
void free_chip(ic_t* ic);
void do_chip_cycle(ic_t* ic);

#endif