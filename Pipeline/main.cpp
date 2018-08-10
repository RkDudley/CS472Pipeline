//Project 3 MIPS PIPELINE
//Author: Rattikarn Dudley

#include <iostream>
#include "Pipeline.h"
#include <fstream>

void IF_stage(unsigned int ins,Pipeline& Process);
void ID_stage(Pipeline& Process);
void EX_stage(Pipeline& Process);
void MEM_stage(Pipeline& Process);
void WB_stage(Pipeline& Process);
void Print_stage(Pipeline& Process, std::ostream &outFile);
void Copy_stage(Pipeline& Process);

int main()
{
	std::ofstream outFile("output.txt");
	Pipeline process;

	unsigned int instructionCache[13] = {0xA1020000,0x810AFFFC,0x00831820,0x01263820,0x01224820,0x81180000,0x81510010,0x00624022,
		0x00000000,0x00000000,0x00000000,0x00000000 };
	
	// each loop is a one clock cycle
	
	for (int i = 0; i < 13; i++)
	{
		std::cout <<std::dec << "Clock Cycle " << i << std::endl <<std::endl;
		outFile << std::dec << "Clock Cycle " << i << std::endl << std::endl;
		if (i == 0)
		{
			//initialize stage
			IF_stage(i, process);
			ID_stage(process);
			EX_stage(process);
			MEM_stage(process);
			WB_stage(process);
			Print_stage(process,outFile);
		}
		else
		{
			std::cout << "Before we copy the write side of pipeline register to the read side" << std::endl <<std::endl;
			outFile << "Before we copy the write side of pipeline register to the read side" << std::endl << std::endl;
			IF_stage(instructionCache[i-1], process);
			ID_stage(process);
			EX_stage(process);
			MEM_stage(process);
			WB_stage(process);
			Print_stage(process,outFile);
			Copy_stage(process);
			std::cout << std::endl;
			std::cout << "After we copy the write side of pipeline register to the read side" << std::endl <<std::endl;
			outFile << "After we copy the write side of pipeline register to the read side" << std::endl << std::endl;
			Print_stage(process,outFile);
		}		
	}
	outFile.close();
	return 0;
}

void IF_stage(unsigned int instr, Pipeline& process)
{
	//instruction fetch
	process.setIF(instr);
}

void ID_stage(Pipeline& process)
{
	//decode instructions
	process.setIFIDinstruction();
}

void EX_stage(Pipeline& process) 
{
	//get a decode instruction from ID stage
	process.decodeIDEXControl();
}

void MEM_stage(Pipeline& process) 
{	// get all control for execution stage
	process.setEXMEM();
}
void WB_stage(Pipeline& process)
{
	//set write back regs and value 
	process.setWB();
}

void Copy_stage(Pipeline& process)
{
	//copy write to read 
	process.copyWriteToRead();
}

void Print_stage(Pipeline& process,std::ostream &outfile) 
{
	process.displayIFIDWrite(outfile);
	process.displayIFIDRead(outfile);
	process.displayIDEXWrite(outfile);
	process.displayIDEXRead(outfile);
	process.displayEXMEMWrite(outfile);
	process.displayEXMEMRead(outfile);
	process.displayMemWBWrite(outfile);
	process.displayMemWBRead(outfile);
}




