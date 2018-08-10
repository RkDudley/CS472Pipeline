#ifndef EX_H
#define EX_H

#include "InsDecode.h"
#include "InstructionFetch.h"

class EX :public ID
{
private:
	int ALUSrc;
	int ALUresult;
	int ALUControl;
	int zero;
	unsigned int readData1;
	signed short readData2;
	signed short int offset;
	unsigned int Value;
	std::string memToReg;
	std::string writeRegNum;
	int writeData;
	int memRead;
	int memWrite;
	int regWrite;
	int RegData;
	signed int Offset;
public:
	EX();
	//Read to MEM
	int setRegValEX(int val);
	signed short int getOffsetEX();
	int getALUSrcEX();
	int getReadData1EX();
	signed short getReadData2EX();
	std::string getMemtoRegEX();
	int getRegValEX();
	int getMemReadEX();
	int getMemWriteEX();
	int getRegWriteEX();
	int getALUresultEX();
	int getswValueEX();
	std::string getWriteRegNumEX();
	// get data from read ID
	int setALUSrcEX(int src);
	void setALUSrcEX();
	void setWriteRegNumEX(int data);
	signed short int setOffsetEX(signed int offsetID);
	int setMemReadEX(int memRead);
	int setMemWriteEX(int memWrite);
	std::string setMemToRegEX(std::string memReg);
	int setRegWriteEX(int reg);
	int setAlUcontrolEX(int aluOp, std::string function);
	int setReadData1EX(int data1);
	int setReadData2EX(int data2);
	unsigned int setALUresultEX();
};


#endif
