#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "imgui/imgui.h"
#include "imgui/imgui_memory_editor.h"
#include "mem/memory.h"
#include "io.h"
#include "rom.h"
#include <opcode.h>
#include "cpu/xcpu.h"
#include "glfw/emulator_window.h"
#include "ppu.h"
#include "ic.h"
#include "input.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")

extern xregister registers[REGISTER_COUNT];
extern stack_t stack;
extern stack_t vram;

int main(int argc, char** argv)
{
	initialize_memory();

	// temporary
	printf("Input EEPROM path: ");
	char eeprom_path[0xFF];
	scanf("%s", eeprom_path);

	input_file* file = read_rom_file(eeprom_path);
	if (!file)
	{
		printf("%s failed to load!\n", eeprom_path);
		exit(0);
	}
#ifdef _WIN32
	system("cls");
#endif
	emulator_window* window = initialize_window(CONSOLE_RESX, CONSOLE_RESY, true);

	initialize_cpu();
	set_stack();
	eeprom* rom = load_eeprom(file);
	//extend_stack(rom->header.ram_ext);
	rom->header.ram_ext = 0;
	initialize_ppu();
	glEnable(GL_TEXTURE_2D);

	render_buffer* main_buffer = create_render_buffer(CONSOLE_RESX, CONSOLE_RESY);
	
	MemoryEditor ram_editor, rom_editor, vram_editor;
	
	PPUBUFFID = main_buffer->id;

	inputmap_t inputmap = default_input_map();

	for (unsigned int i = 0x5; i < 0x9; i++)
	{
		uint8_t b = (rom->header.chr_size << (8 * (i - sizeof(unsigned int))));
		int16_t new_index = VRAM_FIRST + 0x4 + (i - sizeof(unsigned int));
		write_byte(new_index, b);
	}

	while (window_running(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		write_byte(RUNNING_ADDR, !glfwWindowShouldClose(window->ptr));

		ram_editor.DrawWindow("RAM", stack, INTERNAL_RAM + rom->header.ram_ext);
		vram_editor.DrawWindow("VRAM", vram, VRAM);
		rom_editor.DrawWindow("ROM", file->bytes, file->length);

		ImGui::Begin("CPU Info");
		ImGui::Text("A: $%x", registers[ACCUMULATOR_REGISTER].r8);
		ImGui::Text("X: $%x Y: $%x", registers[INDEXX_REGISTER].r8, registers[INDEXY_REGISTER].r8);
		ImGui::Text("PC: $%x", registers[PROGRAM_COUNTER].r8);
		ImGui::Text("IP: $%x", *(registers[INDEX_PTR].r8_ptr));
		ImGui::Text("SP: $%x", *(registers[STACK_PTR].r8_ptr));
		ImGui::Text("S: %x", registers[STATUS_FLAG_REGISTER].r16);
		ImGui::Text("Input flag: %x", get_byte(INPUT_ADDR));
		ImGui::End();

		ppu_render();
		cpu_process(rom);
		
		update_input(window, &inputmap);
		update_window(window);
	}

	free_render_buffer(main_buffer);
	free_input_file(file);
	free_eeprom(rom);
	free_cpu();
	free_ppu();
	free_window(window);
	return 0;
}