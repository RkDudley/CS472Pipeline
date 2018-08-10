#ifndef MEM_H
#define MEM_H

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

class MEM
{
private:
	int Main_Mem[1024];
	int address; // store address from memory
	std::string writeData;
	int readData;
	int ALUresult;
	std::string memToreg;
	int RegWrite;
	int ALU;
	std::string LWdataVal;
	int memWrite;
	int memRead;
	int val;
public:
	MEM();
	std::string getLwDataValMEM();
	std::string getMemToRegMem();
	int getSWval();
	int getRegWriteMem();
	int getALUresultMEM();
	std::string getWriteRegNumMEM();
	std::string setMemToRegMEM(std::string memReg);
	int setRegWriteMEM(int regW);
	std::string setWriteDataMEM(std::string data);
	int setALUResultMem(int result);
	int setALUControl(int control);
	int setMemWriteMEM(int memW);
	int setMemReadMEM(int memRead);
	int setSWValue(int data);
	void setDataMemory();
};
#endif 

