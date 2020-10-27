#ifndef INPUT_H
#define INPUT_H

#include "glfw/emulator_window.h"
#include <stdint.h>

typedef struct
{
	const char* tag;
	int32_t key;
	int8_t flag;
} button_t;
button_t create_button_map(const char* tag, int32_t key, int8_t flag);

typedef struct
{
	union
	{
		button_t buttons[8];

		struct
		{
			button_t a;
			button_t b;
			button_t start;
			button_t select;
			button_t up;
			button_t down;
			button_t left;
			button_t right;
		};
	};
} inputmap_t;
inputmap_t default_input_map();
button_t* get_button_by_tag(inputmap_t* im, const char* tag);

void update_input(emulator_window* window, inputmap_t* inputmap);

#endif