#include "ExcecuteOp.h"

EX::EX()
{
	ALUresult = 0;
	zero = 0; // for branch
	Offset = 0;
	RegData = 0;
	memRead = 0;
	memWrite = 0;
	regWrite = 0;
	writeData = 0;
	Value = 0;
}

int EX::getALUSrcEX()
{
	return ALUSrc;
}
int EX::getReadData1EX()
{
	return readData1;
}
signed short EX::getReadData2EX()
{
	return readData2;
}
std::string EX::getWriteRegNumEX()
{
	return writeRegNum;
}
int EX::getswValueEX()
{
	return Value;
}
int EX::getRegValEX()
{
	return RegData;
}
int EX::getALUresultEX()
{
	return ALUresult;
}
std::string EX::getMemtoRegEX()
{
	return memToReg;
}
signed short int EX::getOffsetEX()
{
	return offset;
}
int EX::getRegWriteEX()
{
	return  regWrite;
}
int EX::getMemReadEX()
{
	return memRead;
}
int EX::getMemWriteEX()
{
	return memWrite;
}
int EX::setALUSrcEX(int src)
{
	ALUSrc = src;
	return ALUSrc;
}
int EX::setRegValEX(int data)
{
	RegData = data;
	return data;
}
void EX::setALUSrcEX()
{
	if (ALUSrc == 0) // R type
	{
		Value = readData2;
	}
	else if(ALUSrc == 1) // I type
	{
		signed int tempval = readData2;
		readData2 = offset;
		Value = tempval;
	}
}

int EX::setAlUcontrolEX(int aluOp, std::string function)
{
	if (aluOp == 00) // I type
	{
		ALUControl = 010;
		return ALUControl;
	}
	else if (aluOp == 10)// R type
	{	
		if (function == "32")
		{
			ALUControl = 010;
			return ALUControl;
		}
		else if (function == "34")
		{
			ALUControl = 110;
			return ALUControl;
		}
	}
	return 0;
}

unsigned int EX::setALUresultEX()
{
	setALUSrcEX();
	if ( ALUControl== 010) // add
	{
		ALUresult = readData1 + readData2;
	}
	else if (ALUControl == 110) // subtract
	{
		ALUresult = readData1 - readData2;
	}
	return ALUresult;
}

int EX::setReadData1EX(int data1)
{
	readData1 = data1;
	return readData1;
}
int EX::setReadData2EX(int data2)
{
	readData2 = data2;
	return readData2;
}
int EX::setMemReadEX(int memToRead)
{
	memRead = memToRead;
	return memRead;
}
int EX::setMemWriteEX(int memWriteID)
{
	memWrite = memWriteID;
	return memWrite;
}
std::string EX::setMemToRegEX(std::string memReg)
{
	memToReg = memReg;
	return memToReg;
}
int EX::setRegWriteEX(int reg)
{
	regWrite = reg;
	return regWrite;
}
signed short int EX::setOffsetEX(signed int offsetID)
{
	offset = offsetID;
	return offset;
}
void EX::setWriteRegNumEX(int data)
{
	if (memToReg == "X" )// SW
	{
		writeRegNum = "X";
	}
	else if (memToReg == "1") //LW
	{
		writeData = data;
		writeRegNum = std::to_string(writeData);
	}
	else if (memToReg == "0") // R
	{
		writeData = data;
		writeRegNum = std::to_string(writeData);
	}
}
