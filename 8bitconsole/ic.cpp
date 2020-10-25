#include "ic.h"
#include "mem/memory.h"

ic_t* create_integrated_chip(const char* tag, int8_t pin_count, ICFUN func)
{
	ic_t* ic = (ic_t*)li_malloc(sizeof(ic_t));
	ic->func = func;
	ic->pin_count = pin_count;
	ic->tag = tag;
	ic->pins = (ic_pin_t*)li_malloc(pin_count * sizeof(ic_pin_t));
	for (int i = 0; i < pin_count; i++)
	{
		ic->pins[i].index = i;
		ic->pins[i].value = 0;
		ic->pins[i].value_ptr = NULL;
	}
	return ic;
}

void free_chip(ic_t* ic)
{
	li_free(ic->pins);
	li_free(ic);
}

void do_chip_cycle(ic_t* ic)
{
	for (int i = 0; i < ic->pin_count; i++)
	{
		ic->func(&ic->pins[i]);
	}
}