#include "xcpu.h"
#include <opcode.h>
#include "../mem/memory.h"
#include <stdio.h>
#include <cstring>
#include "../ppu.h"

xregister registers[REGISTER_COUNT];
stack_t stack;
extern stack_t vram;

void initialize_cpu()
{
	memset(registers, 0, sizeof(registers));
	for (int i = 0; i < REGISTER_COUNT; i++)
	{
		registers[i].id = i;
	}
	registers[STATUS_FLAG_REGISTER].r8 |= STATIC_FLAG;
}

void set_stack()
{
	stack = (stack_t)li_malloc(INTERNAL_RAM);
	registers[STACK_PTR].r8_ptr = stack;
	memset(stack, 0, INTERNAL_RAM);
}

void extend_stack(uint16_t ext)
{
	stack = (stack_t)li_realloc(stack, INTERNAL_RAM + ext);
	registers[STACK_PTR].r8_ptr = stack;
	memset(stack, 0, INTERNAL_RAM + ext);
}

void reset_cpu()
{
}

void free_cpu()
{
	li_free(stack);
}

uint8_t get_8bit_register(int8_t id)
{
	for (int i = 0; i < REGISTER_COUNT; i++)
	{
		if (registers[i].id == id)
			return registers[i].r8;
	}
	return 0;
}

void stack_write(uint16_t address, uint8_t val)
{
	stack[address] = val;
}

uint8_t stack_read(uint16_t address)
{
	return stack[address];
}

void CPU_SETI()
{
	INCREASE_IP(1);
	int8_t flag = EEPROM_GET_BYTE();
	if (flag == 0x1)
	{
		registers[STATUS_FLAG_REGISTER].r8 |= INT_DISABLE_FLAG;
	}
}

void CPU_SETD()
{
	INCREASE_IP(1);
	int8_t flag = EEPROM_GET_BYTE();
	if (flag == 0x1)
	{
		registers[STATUS_FLAG_REGISTER].r8 |= DECIMAL_FLAG;
	}
}

void CPU_LD_REG_IM(int8_t id)
{
	INCREASE_IP(1);
	int8_t b = EEPROM_GET_BYTE();
	registers[id].r8 = b;
}

void CPU_LD_REG_REG(int8_t id)
{
	INCREASE_IP(1);
	uint8_t val = get_8bit_register(EEPROM_GET_BYTE());
	registers[id].r8 = val;
}

void CPU_ST_STACK(uint8_t id)
{
	INCREASE_IP(1);
	uint16_t addr = swap_2_bytes(EEPROM_GET_SHORT());
	if (addr > (INTERNAL_RAM - 1) && addr < (VRAM - 1))
	{
		ppu_write(addr - INTERNAL_RAM, registers[id].r8);
	}
	else
	{
		stack_write(addr, registers[id].r8);
	}
}

void CPU_ADD_ACCUMULATOR()
{
	INCREASE_IP(1);
	uint8_t b = EEPROM_GET_BYTE();
	registers[ACCUMULATOR_REGISTER].r8 += b;
}

void CPU_SUB_ACCUMULATOR()
{
	INCREASE_IP(1);
	uint8_t b = EEPROM_GET_BYTE();
	registers[ACCUMULATOR_REGISTER].r8 -= b;
}

void CPU_MUL_ACCUMULATOR()
{
	INCREASE_IP(1);
	uint8_t b = EEPROM_GET_BYTE();
	registers[ACCUMULATOR_REGISTER].r8 *= b;
}

void CPU_DIV_ACCUMULATOR()
{
	INCREASE_IP(1);
	uint8_t b = EEPROM_GET_BYTE();
	registers[ACCUMULATOR_REGISTER].r8 /= b;
}

void CPU_CALL(eeprom* rom)
{
	INCREASE_IP(1);
	uint16_t addr = swap_2_bytes(EEPROM_GET_SHORT());
	PUSH_SHORT(*registers[INDEX_PTR].r16_ptr);
	SET_INDEX_AFTER_HEADER(rom, addr);
}

void CPU_JMP(eeprom* rom)
{
	INCREASE_IP(1);
	uint16_t addr = swap_2_bytes(EEPROM_GET_SHORT());
	SET_INDEX_AFTER_HEADER(rom, addr);
}

void CPU_RET(eeprom* rom)
{
	INCREASE_IP(1);
	uint16_t addr = POP_SHORT();
	SET_INDEX_AFTER_HEADER(rom, addr);
}

void CPU_COUT()
{
	INCREASE_IP(1);
	uint16_t addr = swap_2_bytes(EEPROM_GET_SHORT());
	uint8_t b = 0;
	if (addr > (INTERNAL_RAM - 1) && addr < (VRAM - 1))
	{
		b = ppu_read(addr - INTERNAL_RAM);
	}
	else
	{
		b = stack_read(addr);
	}
	putchar(b);
}

void cpu_process(eeprom* rom)
{
	while (registers[INDEX_PTR].r8_ptr)
	{
		registers[PROGRAM_COUNTER].r16++;
		switch (*registers[INDEX_PTR].r8_ptr)
		{
		case NOP: INCREASE_IP(1); break;
		case HALT: return; break;
		case SETI: CPU_SETI(); break;
		case SETD: CPU_SETD(); break;
		case LDA_IM: CPU_LD_REG_IM(ACCUMULATOR_REGISTER); break;
		case LDA_REG: CPU_LD_REG_REG(ACCUMULATOR_REGISTER); break;
		case LDX_IM: CPU_LD_REG_IM(INDEXX_REGISTER); break;
		case LDX_REG: CPU_LD_REG_REG(INDEXX_REGISTER); break;
		case LDY_IM: CPU_LD_REG_IM(INDEXY_REGISTER); break;
		case LDY_REG: CPU_LD_REG_REG(INDEXY_REGISTER); break;
		case STA: CPU_ST_STACK(ACCUMULATOR_REGISTER); break;
		case STX: CPU_ST_STACK(INDEXX_REGISTER); break;
		case STY: CPU_ST_STACK(INDEXY_REGISTER); break;
		case ADD_A: CPU_ADD_ACCUMULATOR(); break;
		case SUB_A: CPU_SUB_ACCUMULATOR(); break;
		case MUL_A: CPU_MUL_ACCUMULATOR(); break;
		case DIV_A: CPU_DIV_ACCUMULATOR(); break;
		case CALL: CPU_CALL(rom); break;
		case JMP: CPU_JMP(rom); break;
		case RET: CPU_RET(rom); break;
		case COUT: CPU_COUT(); break;
		}
	}
}