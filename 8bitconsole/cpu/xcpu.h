#ifndef XCPU_H
#define XCPU_H
#include <stdint.h>
#include "../rom.h"

#define swap_2_bytes(val) \
((((val) >> 8) & 0x00FF) | (((val) << 8) & 0xFF00))

#define swap_4_bytes(val) \
((((val) >> 24) & 0x000000FF) | (((val) >> 8) & 0x0000FF00) | \
	(((val) << 8) & 0x00FF0000) | (((val) << 24) & 0xFF000000))

#define swap_8_bytes(val) \
	((((val) >> 56) & 0x00000000000000FF) | (((val) >> 40) & 0x000000000000FF00) | \
		(((val) >> 24) & 0x0000000000FF0000) | (((val) >> 8) & 0x00000000FF000000) | \
		(((val) << 8) & 0x000000FF00000000) | (((val) << 24) & 0x0000FF0000000000) | \
		(((val) << 40) & 0x00FF000000000000) | (((val) << 56) & 0xFF00000000000000))

#define PUSH_BYTE(x) *(registers[STACK_PTR].r8_ptr++) = (uint8_t)(x)
#define PUSH_SHORT(x)                                \
    *((uint16_t *)registers[STACK_PTR].r8_ptr) = (uint16_t)(x); \
    registers[STACK_PTR].r8_ptr += 2
#define PUSH_INT(x)                                  \
    *((uint32_t *)registers[STACK_PTR].r8_ptr) = (uint32_t)(x); \
    registers[STACK_PTR].r8_ptr += 4

#define POP_BYTE() ((uint8_t)(*(--registers[STACK_PTR].r8_ptr)))
#define POP_SHORT() ((uint16_t)(*((uint16_t *)(registers[STACK_PTR].r8_ptr -= 2))))
#define POP_INT() ((uint32_t)(*((uint32_t *)(registers[STACK_PTR].r8_ptr -= 4))))

#define EEPROM_GET_BYTE() ((uint8_t)*(registers[INDEX_PTR].r8_ptr++))
#define EEPROM_GET_SHORT() ((uint16_t) (*((uint16_t*) (registers[INDEX_PTR].r8_ptr++))))
#define EEPROM_GET_INT() ((uint32_t) (*((uint32_t*) (registers[INDEX_PTR].r8_ptr++))))
#define INCREASE_IP(x) for(int i = 0; i < x; i++) { *(registers[INDEX_PTR].r8_ptr)++; }

#define SET_INDEX_AFTER_HEADER(rom, i) registers[INDEX_PTR].r8_ptr = *(rom->input_bytes) + (sizeof(rom_header) + i);

typedef uint8_t* stack_t;

typedef struct
{
	int8_t id;
	union
	{
		struct
		{
			uint8_t r8;
		};

		struct
		{
			uint8_t* r8_ptr;
		};

		struct
		{
			uint16_t r16;
		};

		struct
		{
			uint16_t* r16_ptr;
		};
	};
} xregister;

void initialize_cpu();
void set_stack();
void extend_stack(uint16_t ext);
void reset_cpu();
void free_cpu();
void cpu_process(int32_t cycles, eeprom* rom);
void stack_write(uint16_t address, uint8_t val);
uint8_t stack_read(uint16_t address);

#endif