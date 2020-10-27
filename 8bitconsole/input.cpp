#include "input.h"
#include <opcode.h>
#include "cpu/xcpu.h"
#include <string.h>

extern stack_t stack;

button_t create_button_map(const char* tag, int32_t key, int8_t flag)
{
	button_t b;
	b.tag = tag;
	b.key = key;
	b.flag = flag;
	return b;
}

inputmap_t default_input_map()
{
	inputmap_t im;
	im.a = create_button_map("A", GLFW_KEY_X, A_BUTTON_FLAG);
	im.b = create_button_map("B", GLFW_KEY_Z, B_BUTTON_FLAG);
	im.start = create_button_map("Start", GLFW_KEY_SPACE, START_BUTTON_FLAG);
	im.select = create_button_map("Select", GLFW_KEY_ENTER, SELECT_BUTTON_FLAG);
	im.up = create_button_map("Up", GLFW_KEY_UP, UP_BUTTON_FLAG);
	im.down = create_button_map("Down", GLFW_KEY_DOWN, DOWN_BUTTON_FLAG);
	im.left = create_button_map("Left", GLFW_KEY_LEFT, LEFT_BUTTON_FLAG);
	im.right = create_button_map("Right", GLFW_KEY_RIGHT, RIGHT_BUTTON_FLAG);
	return im;
}

button_t* get_button_by_tag(inputmap_t* im, const char* tag)
{
	for (unsigned int i = 0; i < 8; i++)
	{
		if (strcmp(im->buttons[i].tag, tag) == 0)
			return &im->buttons[i];
	}
	return NULL;
}

void update_input(emulator_window* window, inputmap_t* inputmap)
{
	for (unsigned int i = 0; i < 8; i++)
	{
		int32_t button_state = glfwGetKey(window->ptr, inputmap->buttons[i].key);
		
		if (button_state == GLFW_PRESS)
		{
			stack[INPUT_ADDR] |= inputmap->buttons[i].flag;
		}
		else
		{
			stack[INPUT_ADDR] &= ~inputmap->buttons[i].flag;
		}
	}
}