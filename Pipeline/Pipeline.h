//Project 3 MIPS PIPELINE
//Author: Rattikarn Dudley
#ifndef PIPELINE_H
#define PIPELINE_H

#include <string>
#include "InsDecode.h"
#include "InstructionFetch.h"
#include "ExcecuteOp.h"
#include "MemoryAddress.h"
#include "WriteBack.h"

class Pipeline
{
private:
	int Regs[32];
	IF IF_ID_Read;
	IF IF_ID_Write;
	ID ID_EX_Read;
	ID ID_EX_Write;
	EX EX_MEM_Read;
	EX EX_MEM_Write;
	MEM MEM_WB_Read;
	MEM MEM_WB_Write;
	WB WBwriteBack;
public:
	Pipeline();
	//IF
	void setIF(unsigned int ins);
	//IFID
	void setIFIDinstruction();
	//IDEX
	void decodeIDEXControl();
	//EXMEM
	void setEXMEM();
	//MEMWB
	void setWB();
	//copy write to read
	void copyWriteToRead();
	//display all stages
	void displayIFIDWrite(std::ostream &outFile);
	void displayIFIDRead(std::ostream &outFile);
	void displayIDEXWrite(std::ostream &outFile);
	void displayIDEXRead(std::ostream &outFile);
	void displayEXMEMWrite(std::ostream &outFile);
	void displayEXMEMRead(std::ostream &outFile);
	void displayMemWBWrite(std::ostream &outFile);
	void displayMemWBRead(std::ostream &outFile);
};

#endif