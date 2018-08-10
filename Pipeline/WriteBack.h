#ifndef  WB_H
#define WB_H

#include <string>
#include <sstream>
#include <iomanip>

class WB
{
private:
	int ReadData;
	std::string memToReg;
	std::string writeData;
	std::string lwval;
	int ALUResult;
public:
	WB();
	int getALUResultWB(int result);
	std:: string setMemtoRegWB(std::string memr);
	std::string setWriteDataWB(std::string writeD);
	std::string setlwVal(std::string lwval);
	void writeBackData(int *reg);
};

#endif // ! WB_H

