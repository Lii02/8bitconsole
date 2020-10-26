#ifndef OPCODE_H
#define OPCODE_H
#include <stdint.h>

#define ROM_SIGNATURE 0x6C756B65

// Registers
#define REGISTER_COUNT 0x8
#define INDEX_PTR 0x0
#define STATUS_FLAG_REGISTER 0x1
#define ACCUMULATOR_REGISTER 0x2
#define STACK_PTR 0x3
#define PROGRAM_COUNTER 0x4
#define INDEXX_REGISTER 0x5
#define INDEXY_REGISTER 0x6
#define MEMORY_MODE_REGISTER 0x7

// Flag register values
#define INT_DISABLE_FLAG (1 << 8)
#define CMP_FLAG (1 << 7)
#define DECIMAL_FLAG (1 << 6)
#define NEGATIVE_FLAG (1 << 5)
// Static flag(last bit) is always 1
#define STATIC_FLAG (1 << 0)

// Status flag operations
#define SETI 0xA0
#define SETD 0xA1

// Register manipulation operations
#define LDA_IM 0xB0
#define LDA_REG 0xB1
#define LDX_IM 0xB2
#define LDX_REG 0xB3
#define LDY_IM 0xB4
#define LDY_REG 0xB5
#define ADD_A 0xD0
#define SUB_A 0xD1
#define MUL_A 0xD2
#define DIV_A 0xD3

// Stack manipulation operations
#define STA 0xC0
#define STX 0xC1
#define STY 0xC2

// Compare operations
#define CMPA_IM 0x20
#define CMPX_IM 0x21
#define CMPY_IM 0x22
#define CMPA_MEM 0x23
#define CMPX_MEM 0x24
#define CMPY_MEM 0x25

// Branch operations
#define BEQ 0x30

// General opcodes
#define NOP 0xEA
#define HALT 0xCC
#define INT_OP 0xEB
#define JMP 0xEC
#define CALL 0xED
#define RET 0xEE
#define COUT 0xEF

#define INTERNAL_RAM 0x900
#define VRAM 0xFFFF
#define VRAM_FIRST (INTERNAL_RAM + rom->header.ram_ext)

// Input
#define INPUT_ADDR 0x0010
#define A_BUTTON_FLAG (1 << 0)
#define B_BUTTON_FLAG (1 << 1)
#define START_BUTTON_FLAG (1 << 2)
#define SELECT_BUTTON_FLAG (1 << 3)
#define UP_BUTTON_FLAG (1 << 4)
#define DOWN_BUTTON_FLAG (1 << 5)
#define LEFT_BUTTON_FLAG (1 << 6)
#define RIGHT_BUTTON_FLAG (1 << 7)

#define RUNNING_ADDR 0x0011

typedef struct
{
	const char* str;
	uint8_t op;
	uint8_t args;
} opcode;

opcode get_opcode(uint8_t op);

#endif