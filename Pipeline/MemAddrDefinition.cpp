#include "MemoryAddress.h"

MEM::MEM()
{
	//initialize main memory 0-255
	int location = 0;
	int i = 0;
	//assign address to each memories
	while (i < 1024)
	{
		if (i == 0)
		{
			Main_Mem[i] = 0;
			location++;
		}
		else if (location <= 0xFF && i != 0)
		{
			Main_Mem[i] = location;
			location++;
		}
		else
		{
			// assign address back to 0 when reach count to 255
			location = 0;
			Main_Mem[i] = location;
			location++;
		}
		i++;
	}
	address = 0;
	writeData = "0";
	readData = 0;
	ALUresult = 0;
	memToreg = "0";
	RegWrite = 0;
	ALU = 0;
	LWdataVal = "0";
	val = 0;
}

std::string MEM::getLwDataValMEM()
{
	return LWdataVal;
}
int MEM::getALUresultMEM()
{
	return ALUresult;
}
std::string MEM::getWriteRegNumMEM()
{
	return writeData;
}
std::string MEM::getMemToRegMem()
{
	return memToreg;
}

int MEM::getSWval()
{
	return val;
}

int MEM::getRegWriteMem()
{
	return RegWrite;
}

int MEM::setSWValue(int data)
{
	val = data;
	return val;
}
std::string MEM::setMemToRegMEM(std::string mr)
{
	memToreg = mr;
	return memToreg;
}

int MEM::setRegWriteMEM(int rw)
{
	RegWrite = rw;
	return RegWrite;
}
std::string MEM::setWriteDataMEM(std::string data)
{
	writeData = data;
	return writeData;
}

int MEM::setALUResultMem(int result)
{
	ALUresult = result;
	return ALUresult;
}

int MEM::setALUControl(int control)
{
	ALU = control;
	return ALU;
}

int MEM::setMemReadMEM(int memr)
{
	memRead = memr;
	return memRead;
}
int MEM::setMemWriteMEM(int memw)
{
	memWrite = memw;
	return memWrite;
}

void MEM::setDataMemory()
{
	if (memWrite == 0 && memRead == 1) // lw 
	{
		address = Main_Mem[ALUresult]; // store val from main memory to address 
		std::stringstream ss;
		ss << std::hex << address;
		std::string temp(ss.str());
		LWdataVal = temp;
	}
	else if (memWrite == 1 && memRead == 0) // sw data in store in memory 
	{
		address = ALUresult;
		Main_Mem[address] = val;
		LWdataVal = "X";
	}
	else	//no R type in this stage
	{
		LWdataVal = "X";
	}
}
