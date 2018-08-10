#include "InstructionFetch.h"

IF::IF()
{
	PC = 0x7A4000;
	add = 4;
	instruction = 0x00000000;
	PCinit = 0;
}

unsigned int IF::getPC()
{
	if (instruction == 0)
	{
		return PCinit;
	}
	else
	{
		return PC;
	}
	return PC;
}

unsigned int IF::incrementPC()
{
	if (instruction == 0)
	{
		return PCinit;
	}
	else
	{
		PC += add;
		return PC;
	}
	return PC;
}

unsigned int IF::getInstruction()
{
	return instruction;
}

unsigned int IF::setInstruction(unsigned int ins)
{
	if (ins == 0x00000000)
	{
		instruction = 0x00000000;
	}
	else
	{
		instruction = ins;
	}
	return  instruction;
}

