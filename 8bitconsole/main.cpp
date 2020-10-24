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
	initialize_ppu();

	eeprom* rom = load_eeprom(file);
	extend_stack(rom->header.ram_ext);

	MemoryEditor ram_editor, rom_editor, vram_editor;
	rom_editor.ReadOnly = true;
	char* status_buffer = (char*)li_malloc(8);
	memset(status_buffer, 0, 8);

	render_buffer* test_buffer = create_render_buffer(CONSOLE_RESX, CONSOLE_RESY, 3);
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			put_pixel(test_buffer, x, y, 0xA5);
		}
	}
	
	while (window_running(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ram_editor.DrawWindow("RAM", stack, INTERNAL_RAM + rom->header.ram_ext);
		vram_editor.DrawWindow("VRAM", vram, VRAM);
		rom_editor.DrawWindow("ROM", file->bytes, file->length);

		ImGui::Begin("CPU Info");
		ImGui::Text("A: $%x", registers[ACCUMULATOR_REGISTER].r8);
		ImGui::Text("X: $%x Y: $%x", registers[INDEXX_REGISTER].r8, registers[INDEXY_REGISTER].r8);
		ImGui::Text("PC: $%x", registers[PROGRAM_COUNTER].r8);
		ImGui::Text("IP: $%x", *(registers[INDEX_PTR].r8_ptr));
		ImGui::Text("SP: $%x", *(registers[STACK_PTR].r8_ptr));
		itoa(registers[STATUS_FLAG_REGISTER].r8, status_buffer, 2);
		ImGui::Text("S: %s", status_buffer);
		float memory_usage = (get_memory_allocated() / 1024);
		ImGui::Text("Memory allocated: %.4f KB", memory_usage);
		ImGui::End();

		draw_buffer(test_buffer);

		cpu_process(rom->header.prgm_size, rom);
		
		update_window(window);
	}

	free_render_buffer(test_buffer);
	free_input_file(file);
	free_eeprom(rom);
	free_cpu();
	free_ppu();
	free_window(window);
	return 0;
}