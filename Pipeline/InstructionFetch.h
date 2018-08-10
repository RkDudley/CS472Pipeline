//Project 3 MIPS PIPELINE
//Author: Rattikarn Dudley
#ifndef IF_H
#define IF_H

#include <iomanip>
#include <iostream>
class IF
{
private:	
	int PCinit;
	int PC;
	int add;
	unsigned int instruction;
public:
	IF();
	unsigned int incrementPC();
	unsigned int getPC();
	unsigned int setInstruction(unsigned int ins);	
	unsigned int getInstruction();
};



#endif