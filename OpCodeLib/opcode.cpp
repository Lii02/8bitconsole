#include "opcode.h"

opcode codes[] =
{
	{"nop", NOP, 0}, {"halt", HALT, 0}, {"int", INT_OP, 0}, {"jmp", JMP, 1}, {"call", CALL, 1}, {"ret", RET, 0},
	{"cout", COUT, 1},
	// Status flag operations
	{"seti", SETI, 1}, {"setd", SETD, 1},
	// Register manipulation operation
	{"lda", LDA_IM, 1}, {"lda", LDA_REG, 1},
	{"ldx", LDX_IM, 1}, {"ldx", LDX_REG, 1},
	{"ldy", LDY_IM, 1}, {"ldy", LDY_REG, 1},
	{"adda", ADD_A, 1}, {"suba", SUB_A, 1}, {"mula", MUL_A, 1}, {"diva", DIV_A, 1},
	// Stack manipulation operations
	{"sta", STA, 1}, { "stx", STX, 1}, { "sty", STY, 1},
	// Compare operations
	{"cmpa", CMPA_IM, 1}, {"cmpx", CMPX_IM, 1}, {"cmpy", CMPY_IM, 1}, {"cmpa", CMPA_MEM, 1}, {"cmpx", CMPX_MEM, 1}, {"cmpy", CMPY_MEM, 1},
	// Branch operations
	{"beq", BEQ, 1},
};

opcode get_opcode(uint8_t op)
{
	for (int i = 0; i < sizeof(codes); i++)
	{
		if (codes[i].op == op)
		{
			return codes[i];
		}
	}
	return codes[0];
}