#include "WriteBack.h"

WB::WB()
{
	memToReg = "0";
	ReadData = 0;
	writeData = "0";
	ALUResult = 0;
	lwval = "0";
}

std::string WB::setlwVal(std::string val)
{
	lwval = val;
	return lwval;
}

std::string WB::setMemtoRegWB(std::string memg)
{
	memToReg = memg;
	return memToReg;
}
std::string WB::setWriteDataWB(std::string writeD)
{
	writeData = writeD;
	return writeData;
}
int WB::getALUResultWB(int result)
{
	ALUResult = result;
	return result;
}

void WB::writeBackData(int *Regs)
{
	//only add and lb in these stage
	if (memToReg == "0") // add//sub
	{
		//write back R type
		int writeBackData = std::stoi(writeData);
		Regs[writeBackData] = ALUResult;

	}
	else if (memToReg== "1") // lb
	{
		int writeBackData = std::stoi(writeData);
		int value = std::stoi(lwval);
		//write back to lb type
		//value is from main memory
		Regs[writeBackData] = value;
	}
}