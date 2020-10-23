#ifndef EMULATOR_WINDOW_H
#define EMULATOR_WINDOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


typedef struct
{
	GLFWwindow* ptr;
	int width;
	int height;
	bool vsync;
} emulator_window;

emulator_window* initialize_window(int width, int height, bool vsync);
bool window_running(emulator_window* window);
void update_window(emulator_window* window);
void free_window(emulator_window* window);

#endif