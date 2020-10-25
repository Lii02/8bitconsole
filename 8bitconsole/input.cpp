#include "input.h"
#include <opcode.h>
#include "cpu/xcpu.h"

extern stack_t stack;

inputmap_t default_input_map()
{
	inputmap_t im;
	im.a.tag = "A";
	im.a.key = GLFW_KEY_X;
	im.a.flag = A_BUTTON_FLAG;
	im.b.tag = "B";
	im.b.key = GLFW_KEY_Z;
	im.b.flag = B_BUTTON_FLAG;
	im.start.tag = "Start";
	im.start.key = GLFW_KEY_SPACE;
	im.start.flag = START_BUTTON_FLAG;
	im.select.tag = "Select";
	im.select.key = GLFW_KEY_ENTER;
	im.select.flag = SELECT_BUTTON_FLAG;
	im.up.tag = "Up";
	im.up.key = GLFW_KEY_UP;
	im.up.flag = UP_BUTTON_FLAG;
	im.down.tag = "Down";
	im.down.key = GLFW_KEY_DOWN;
	im.down.flag = DOWN_BUTTON_FLAG;
	im.left.tag = "Left";
	im.left.key = GLFW_KEY_LEFT;
	im.left.flag = LEFT_BUTTON_FLAG;
	im.right.tag = "Right";
	im.right.key = GLFW_KEY_RIGHT;
	im.right.flag = RIGHT_BUTTON_FLAG;
	return im;
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