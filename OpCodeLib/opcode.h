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
#define INT_DISABLE_FLAG 0b10000000
#define ZERO_FLAG 0b01000000
#define DECIMAL_FLAG 0b00100000
#define NEGATIVE_FLAG 0b00010000
// Static flag(last bit) is always 1
#define STATIC_FLAG 0b00000001

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

typedef struct
{
	const char* str;
	uint8_t op;
	uint8_t args;
} opcode;

opcode get_opcode(uint8_t op);

#endif