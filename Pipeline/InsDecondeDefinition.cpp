//Project 3 MIPS PIPELINE
//Author: Rattikarn Dudley

#include "InsDecode.h"

ID::ID()
{
	SRCREG1, SRCREG2, SRCDESTREG3, OPCODE, FUNC, OFFSETS;
	function = "0";
	readReg1 = 0;
	readReg2 = 0;
	writeData = 0;
	readData1 = 0;
	readData2 = 0;
	RegDest = "0";
	MemRead = 0;
	MemWrite = 0;
	ALUOp = 0;
	ALUSrc = 0;
	RegWrite = 0;
	MemToReg = "0";
	offSet = 0;
	pc = 0;
	opcode = 0;
	Rt = 0;
	Rs = 0;
	Rd = 0;
	instruction = 0x00000000;
	pc = 0;
	writeRegs = 0;
};

int ID::getRegData()
{
	return writeRegs;
}

int ID::getWriteRegNumID()
{
	return writeData;
}
int ID::getFunctionInt()
{
	return FuncInc;
}
int ID::getPCID()
{
	return pc;
}
int ID::getinstructionID()
{
	return instruction;
}
std::string ID::getOffsetStr()
{
	return offStr;
}

std::string ID::getRegDest()
{
	return RegDest;
}

int ID::getAlUsrc()
{
	return ALUSrc;
}

int ID::getReadData2()
{
	return readData2;
}

int ID::getOffset()
{
	return offSet;
}
int ID::getALUop()
{
	return ALUOp;
}

std::string ID::getFunction()
{
	return function;
}

int ID::getReadData1()
{
	return readData1;
}
int ID::getMemToRead()
{
	return MemRead;
}
int ID::getMemWrite()
{
	return MemWrite;
}
std::string ID::getMemToReg()
{
	return MemToReg;
}
int ID::getRegWrite()
{
	return RegWrite;
}

int ID::getWrite1511()
{
	return writeReg1511;
}
int ID::getWrite2016()
{
	return writeReg2016;
}
short ID::setOpCode(unsigned int instr)
{
	//shift right to 26 bits 32 - 6 = 26 
	// 6 is the first 6 bits for opcode position in 32 bits 
	unsigned int ins = setInstruction(instr);
	opcode = (ins & OPCODE) >> 26;

	return opcode;
}

short ID::setRs(unsigned int instr)
{
	//shift right to 32 - 11 = 21 
	//opcode 6 bits + source1 5 bits = 11 
	Rs = (instr & SRCREG1) >> 21;
	return Rs;
}

short ID::setRt(unsigned int instr)
{
	//shift right to 32-16 = 16
	//opcode 6 bits + source1 5 bit + source2 5 bit = 16
	Rt = (instr & SRCREG2) >> 16;
	return Rt;
}

short ID::setRd(unsigned int instr)
{
	//shift right to 32-21 = 11
	//op 6 + sr1 5 + sr2 5 + dest 5 = 21
	Rd = (instr & SRCDESTREG3) >> 11;
	return Rd;
}
short ID::setFunction(unsigned int ins)
{
	//no shift right is necessary
	//the last 6 bits funtion is the last bit in 32
	FuncInc = (ins & FUNC);
	return FuncInc;
}

int ID::setOffset(unsigned int ins)
{
	offSet = (ins & OFFSETS);
	offSet = (offSet << 16) >> 16;
	return offSet;
}

void ID::controlUnit(unsigned int ins, int pcaddr)
{
	// 7 control signals 
	// 2 misses branch and  jump 
	setRegDst(ins);
	setALUop(ins);
	setMemToReg(ins);
	setRegWrite(ins);
	setMemRead(ins);
	setMemWrite(ins);
	setALUsrc(ins);
	instruction = ins;
	pc = pcaddr;
}

void ID::regFile(unsigned int ins, int* Regs)
{
	readReg1 = setRs(ins); // rs
	writeReg2016 = setRt(ins); //rt
	writeReg1511 = setRd(ins);

	if (setRegDst(ins) == "1") // R type
	{
		readReg2 = setRt(ins); // rt
		readData1 = Regs[0 + readReg1]; // rs
		readData2 = Regs[0 + readReg2]; // rt
		writeRegs = Regs[0 + writeReg1511];
		setFunctionStr(ins);
		writeData = writeReg1511;
		offStr = "X";
	}
	else if (setRegDst(ins) == "0" || setRegDst(ins) == "X") // lw
	{
		readReg2 = setRt(ins);
		readData1 = Regs[0 + readReg1]; 
		readData2 = Regs[0 + writeReg2016];
		writeRegs = Regs[0 + writeReg2016];
		writeData = writeReg2016;
		offSet = setOffset(ins);
		std::stringstream ss;
		ss <<std::setfill('0') << std::setw(8) << std::hex << std::uppercase  << offSet;
		std::string tempoffStr(ss.str());
		offStr = tempoffStr;
		setFunctionStr(ins);
	}
}

std::string ID::setRegDst(unsigned int ins)
{
	if (setOpCode(ins) == 0) // R type
	{
		RegDest = "1";
		return RegDest;
	}
	else if (setOpCode(ins) == 0x20)//lw
	{
		RegDest = "0";
		return RegDest;
	}
	else if (setOpCode(ins) == 0x28)//sw
	{
		RegDest = "X";
		return RegDest;
	}
	return 0;
}


int ID::setALUop(unsigned int ins)
{
	int opcode = setOpCode(ins);
	switch (opcode)
	{
	case 0:
		ALUOp = 10; // R type
		return ALUOp;
		break;
	case 0x20:
	case 0x28:
		ALUOp = 00; // I type
		return ALUOp;
	default:
		break;
	}
	return 0;
}

int ID::setALUsrc(unsigned int ins)
{
	if (setOpCode(ins) == 0) // r type
	{
		ALUSrc = 0;
		return ALUSrc;
	}
	else if(setOpCode(ins) == 0x28 || setOpCode(ins) == 0x20)
	{
		ALUSrc = 1;
		return ALUSrc;
	}
	return 0;
}

int ID::setRegWrite(unsigned int ins)
{
	if (setOpCode(ins) == 0)
	{
		RegWrite = 1;
		return RegWrite;
	}
	else if (setOpCode(ins) == 0x20)
	{
		RegWrite = 1;
		return RegWrite;
	}
	else if (setOpCode(ins) == 0x28)
	{
		RegWrite = 0;
		return RegWrite;
	}
	return 0;
}

std::string ID::setMemToReg(unsigned int ins)
{
	if (setOpCode(ins) == 0)
	{
		MemToReg = "0";
		return MemToReg;
	}
	else if (setOpCode(ins) == 0x20)
	{
		MemToReg = "1";
		return MemToReg;
	}
	else if (setOpCode(ins) == 0x28)
	{
		MemToReg = "X";
		return MemToReg;
	}
	return MemToReg;
}

int ID::setMemRead(unsigned int ins)
{
	if (setOpCode(ins) == 0)
	{
		MemRead = 0;
		return MemRead;
	}
	else if (setOpCode(ins) == 0x20)
	{   // only for load byte
		MemRead = 1;
		return MemRead;
	}
	else if (setOpCode(ins) == 0x28)
	{
		MemRead = 0;
		return MemRead;
	}
	return 0;
}
int ID::setMemWrite(unsigned int ins)
{
	if (setOpCode(ins) == 0)
	{
		MemWrite = 0;
		return MemWrite;
	}
	else if (setOpCode(ins) == 0x20)
	{
		MemWrite = 0;
		return MemWrite;
	}
	else if (setOpCode(ins) == 0x28)
	{
		MemWrite= 1;
		return MemWrite;
	}
	return 0;
}

std::string ID::setFunctionStr(unsigned int ins)
{
	if (setOpCode(ins) == 0)
	{
		int func = setFunction(ins);
		function = std::to_string(func);
		return function;
	}
	else
	{
		function = "X";
		return function;
	}
	return function;
}

