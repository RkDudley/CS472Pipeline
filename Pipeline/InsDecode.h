//Project 3 MIPS PIPELINE
//Author: Rattikarn Dudley

#ifndef  ID_H
#define  ID_H
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "InstructionFetch.h"

class ID:public IF
{
private:
	unsigned int SRCREG1 = 0x3E00000;
	unsigned int SRCREG2 = 0x01F0000;
	unsigned int SRCDESTREG3 = 0x0000F800;
	unsigned int OPCODE = 0xFC000000;
	unsigned int FUNC = 0x0000003F;
	unsigned int OFFSETS = 0x0000FFFF;
	unsigned int instruction;
	int readReg1;
	int readReg2;
	int writeReg1511;
	int writeReg2016;
	int writeData;
	int writeRegs;
	int readData1;
	int readData2;
	std::string RegDest;
	int MemRead;
	int MemWrite;
	int ALUOp;
	int ALUSrc;
	int RegWrite;
	std::string MemToReg;
	int offSet;
	std::string function;
	int FuncInc;
	int pc;
	int opcode;
	int Rs, Rt, Rd;
public:
	ID();
	int getRegData();
	int getWrite2016();
	int getWrite1511();;
	int getWriteRegNumID();
	int getFunctionInt();
	int getPCID();
	int getinstructionID();
	std::string offStr;
	int getOffset();
	std::string getOffsetStr();
	int getAlUsrc();
	int getReadData2();
	int getReadData1();
	int getALUop();
	std::string getRegDest();
	std::string getFunction();
	int getMemToRead();
	int getMemWrite();
	std::string getMemToReg();
	int getRegWrite();
	short setOpCode(unsigned int ins);
	short setRs(unsigned int ins);
	short setRt(unsigned int ins);
	short setRd(unsigned int ins);
	short  setFunction(unsigned int numIns);
	int setOffset(unsigned int numIns);
	//unsigned int setPcAdress(unsigned int num, short int immOff);
	std::string setRegDst(unsigned int ins);
	int setALUop(unsigned int ins);
	int setRegWrite(unsigned int ins);
	int setALUsrc(unsigned int ins);
	int setMemRead(unsigned int ins);
	int setMemWrite(unsigned int ins);
	std::string setMemToReg(unsigned int ins);
	std::string setFunctionStr(unsigned int ins);
	void controlUnit(unsigned int ins, int pc);
	void regFile(unsigned int ins, int* regs);
};

#endif 


