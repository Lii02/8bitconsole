#include "emulator_window.h"
#include <stdio.h>
#include "../mem/memory.h"
#include <GL/glew.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../ppu.h"

void setup_viewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	emulator_window* win = (emulator_window*)glfwGetWindowUserPointer(window);
	win->width = width;
	win->height = height;
	setup_viewport(width, height);
}

emulator_window* initialize_window(int width, int height, bool vsync)
{
	emulator_window* w = (emulator_window*)li_malloc(sizeof(emulator_window));
	w->width = width;
	w->height = height;
	w->vsync = vsync;

	if (!glfwInit())
	{
		printf("GLFW failed to load!\n");
	}

	w->ptr = glfwCreateWindow(width, height, "8bitconsole", NULL, NULL);
	glfwSetWindowUserPointer(w->ptr, w);
	glfwSetFramebufferSizeCallback(w->ptr, framebuffer_size_callback);
	glfwMakeContextCurrent(w->ptr);

	auto glew = glewInit();
	if (glew != GLEW_OK)
	{
		printf("GLEW failed to load!\n");
	}

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(w->ptr, true);
	ImGui_ImplOpenGL3_Init("#version 400");

	setup_viewport(width, height);
	return w;
}

bool window_running(emulator_window* window)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	return !glfwWindowShouldClose(window->ptr);
}

void update_window(emulator_window* window)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwPollEvents();
	glfwSwapBuffers(window->ptr);
	glfwSwapInterval(window->vsync);
}

void free_window(emulator_window* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window->ptr);
	li_free(window);
}