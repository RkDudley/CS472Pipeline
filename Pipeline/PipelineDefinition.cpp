#include "Pipeline.h"

Pipeline::Pipeline()
{
	//initlaize registers
	int val = 0x101;
	int j = 0;
	while (j < 32)
	{
		if (j == 0)
		{
			Regs[j] = 0;
		}
		else
		{
			Regs[j] = val;
			val++;
		}
		j++;
	}
}

// IF stage
void Pipeline::setIF(unsigned int ins)
{
	//instruction Fetch
	IF_ID_Write.setInstruction(ins);
	IF_ID_Write.incrementPC();
}

//IFID register
void Pipeline::setIFIDinstruction()
{
	int ins = IF_ID_Read.getInstruction();
	int pc = IF_ID_Read.getPC();
	ID_EX_Write.controlUnit(ins,pc);
	ID_EX_Write.regFile(ins,Regs);	
}

//IDEX register
void Pipeline::decodeIDEXControl()
{
	//decode 7 controls and assign to a value to registers
	signed int offset = ID_EX_Read.getOffset();
	int memR = ID_EX_Read.getMemToRead();
	int memW = ID_EX_Read.getMemWrite();
	std::string memToReg = ID_EX_Read.getMemToReg();
	int writeRegNum = ID_EX_Read.getWriteRegNumID();
	int regWrite = ID_EX_Read.getRegWrite();
	int data1 = ID_EX_Read.getReadData1();
	int data2 = ID_EX_Read.getReadData2();
	int aluSrc = ID_EX_Read.getAlUsrc();
	int writeData = ID_EX_Read.getRegData();
	int aluOp = ID_EX_Read.getALUop();
	std::string function = ID_EX_Read.getFunction();
	// assign ID stage to EX
	EX_MEM_Write.setOffsetEX(offset);
	EX_MEM_Write.setMemReadEX(memR);
	EX_MEM_Write.setMemWriteEX(memW);
	EX_MEM_Write.setMemToRegEX(memToReg);
	EX_MEM_Write.setRegWriteEX(regWrite);
	EX_MEM_Write.setReadData1EX(data1);
	EX_MEM_Write.setReadData2EX(data2);
	EX_MEM_Write.setALUSrcEX(aluSrc);
	EX_MEM_Write.setRegValEX(writeData);
	EX_MEM_Write.setWriteRegNumEX(writeRegNum);
	EX_MEM_Write.setAlUcontrolEX(aluOp, function);
	EX_MEM_Write.setALUresultEX();
}

//set EXMEM stage
//MEM >>  all important controls to assining to mem class
void Pipeline::setEXMEM()
{
	std::string memToReg = EX_MEM_Read.getMemtoRegEX();
	int regWrite = EX_MEM_Read.getRegWriteEX();
	std::string writeRegNum = EX_MEM_Read.getWriteRegNumEX();
	int ALUresult = EX_MEM_Read.getALUresultEX();
	int memRead = EX_MEM_Read.getMemReadEX();
	int memWrite = EX_MEM_Read.getMemWriteEX();
	int writeData = EX_MEM_Read.getswValueEX();
	//read from EX write from MEM
	MEM_WB_Write.setSWValue(writeData);
	MEM_WB_Write.setMemReadMEM(memRead);
	MEM_WB_Write.setMemWriteMEM(memWrite);
	MEM_WB_Write.setWriteDataMEM(writeRegNum);
	MEM_WB_Write.setMemToRegMEM(memToReg);
	MEM_WB_Write.setRegWriteMEM(regWrite);
	MEM_WB_Write.setALUResultMem(ALUresult);
	MEM_WB_Write.setDataMemory();

}
void Pipeline::setWB()
{	
	//get controls from MEM/WB read
	std::string memToReg = MEM_WB_Read.getMemToRegMem();
	std::string writeRegNum = MEM_WB_Read.getWriteRegNumMEM();
	std::string lwval = MEM_WB_Read.getLwDataValMEM();
	int ALUresult = MEM_WB_Read.getALUresultMEM();

	//set to write back
	WBwriteBack.setWriteDataWB(writeRegNum);//result
	WBwriteBack.setMemtoRegWB(memToReg);
	WBwriteBack.setlwVal(lwval);
	WBwriteBack.getALUResultWB(ALUresult);
	WBwriteBack.writeBackData(Regs);
}
void Pipeline::copyWriteToRead()
{
	IF_ID_Read = IF_ID_Write;
	ID_EX_Read = ID_EX_Write;
	EX_MEM_Read = EX_MEM_Write;
	MEM_WB_Read = MEM_WB_Write;
}

void Pipeline::displayIFIDWrite(std::ostream &outFile)
{
	unsigned int instruction = IF_ID_Write.getInstruction();
	int pc = IF_ID_Write.getPC();
	std::cout << "IF/ID Write (written to by the IF stage) " << std::endl;
	outFile << "IF/ID Write (written to by the IF stage) " << std::endl;
	std::cout << "Instruction = 0x" << std::setfill('0') << std::setw(8)
	<< std::hex << std::uppercase << instruction << std::endl;
	outFile << "Instruction = 0x" << std::setfill('0') << std::setw(8)
		<< std::hex << std::uppercase << instruction << std::endl;
	std::cout << "Increment PC = " << std::hex << pc << std::endl << std::endl;
	outFile << "Increment PC = " << std::hex << pc << std::endl << std::endl;
}

void Pipeline::displayIFIDRead(std::ostream &outFile)
{
	unsigned int instruction = IF_ID_Read.getInstruction();
	int pc = IF_ID_Read.getPC();
	std::cout << "IF/ID Read (Read by the ID stage) " << std::endl;
	outFile << "IF/ID Read (Read by the ID stage) " << std::endl;
	std::cout << "Instruction = 0x" << std::setfill('0') << std::setw(8)
		<< std::hex << std::uppercase << instruction << std::endl;
	outFile<< "Instruction = 0x" << std::setfill('0') << std::setw(8)
		<< std::hex << std::uppercase << instruction << std::endl;
	std::cout << "Increment PC = " << std::hex << pc << std::endl << std::endl;
	outFile << "Increment PC = " << std::hex << pc << std::endl << std::endl;
}
void Pipeline::displayIDEXWrite(std::ostream &outFile)
{
	int instruction = ID_EX_Write.getinstructionID();
	int pc = ID_EX_Write.getPCID();
	std::string RegDest = ID_EX_Write.getRegDest();
	int ALUSrc = ID_EX_Write.getAlUsrc();
	int ALUOp = ID_EX_Write.getALUop();
	int MemRead = ID_EX_Write.getMemToRead();
	int memWrite = ID_EX_Write.getMemWrite();
	std::string MemToReg = ID_EX_Write.getMemToReg();
	int RegWrite = ID_EX_Write.getRegWrite();
	int readData1 = ID_EX_Write.getReadData1();
	int readData2 = ID_EX_Write.getReadData2();
	std::string offset = ID_EX_Write.getOffsetStr();
	int writeReg2016 = ID_EX_Write.getWrite2016();
	int writeReg1511 = ID_EX_Write.getWrite1511();
	std::string function = ID_EX_Write.getFunction();
	//decode 
	std::cout << "ID/EX (Write to by the IF stage) " << std::endl;
	outFile << "ID/EX (Write to by the IF stage) " << std::endl;
	if (instruction == 0x00000000)
	{
		std::cout << "Control = 00000000" << std::endl;
		outFile << "Control = 00000000" << std::endl;
	}
	else
	{
		std::cout << "RegDst = " << RegDest << ",";
		outFile << "RegDst = " << RegDest << ",";
		std::cout << " ALUSrc = " << ALUSrc << ",";
		outFile << " ALUSrc = " << ALUSrc << ",";
		std::cout << " ALUop = " << std::dec << std::setw(2) << ALUOp << ",";
		outFile << " ALUop = " << std::dec << std::setw(2) << ALUOp << ",";
		std::cout << " MemRead = " << MemRead << ", ";
		outFile << " MemRead = " << MemRead << ", ";
		std::cout << " MemWrite = " << memWrite << ",";
		outFile << " MemWrite = " << memWrite << ",";
		std::cout << " Branch = 0 ,";
		outFile << " Branch = 0 ,";
		std::cout << " MemToReg " << MemToReg << ",";
		outFile << " MemToReg " << MemToReg << ",";
		std::cout << " RegWrite = " << RegWrite << ",";
		outFile << " RegWrite = " << RegWrite << ",";
		std::cout << std::endl;
		outFile << std::endl;
		std::cout << std::hex << std::uppercase << "IncrPC " << pc;
		outFile << std::hex << std::uppercase << "IncrPC " << pc;
		std::cout  << " ReadReg1Value = " << readData1 << " ReadReg2Value = " << readData2 << " SEoffset = "
			<< offset <<std::dec << " WriteReg_20_16 = " << writeReg2016 << " WriteReg_15_11 = " << writeReg1511 
			<< " Function = " << function << std::endl;
		outFile  << " ReadReg1Value = " << readData1 << " ReadReg2Value = " << readData2 << " SEoffset = "
			<< offset  <<std::dec << " WriteReg_20_16 = " << writeReg2016 << " WriteReg_15_11 = " << writeReg1511
			<< " Function = " << function << std::endl;
	}
	std::cout << std::endl;
	outFile << std::endl;
}

void Pipeline::displayIDEXRead(std::ostream &outFile)
{
	//get instruction from IF
	int pc = ID_EX_Read.getPCID();
	unsigned int instruction = ID_EX_Read.getinstructionID();
	
	//set each control to variable 
	std::string RegDest = ID_EX_Read.getRegDest();
	int ALUSrc = ID_EX_Read.getAlUsrc();
	int ALUOp = ID_EX_Read.getALUop();
	int MemRead = ID_EX_Read.getMemToRead();
	int memWrite = ID_EX_Read.getMemWrite();
	std::string MemToReg = ID_EX_Read.getMemToReg();
	int RegWrite = ID_EX_Read.getRegWrite();

	//assign all regfile data
	int readData1 = ID_EX_Read.getReadData1();
	int readData2 = ID_EX_Read.getReadData2();
	std::string offset = ID_EX_Read.getOffsetStr();
	int writeReg2016 = ID_EX_Read.getWrite2016();
	int writeReg1511 = ID_EX_Read.getWrite1511();
	std::string function = ID_EX_Read.getFunction();

	std::cout << "ID/EX Read (Read by the EX stage) " << std::endl;
	outFile << "ID/EX Read (Read by the EX stage) " << std::endl;
	if (instruction == 0x00000000)
	{
		std::cout << "Control = 00000000" << std::endl;
		outFile << "Control = 00000000" << std::endl;
	}
	else
	{
		std::cout << "RegDst = " << RegDest << ",";
		outFile << "RegDst = " << RegDest << ",";
		std::cout << " ALUSrc = " << ALUSrc << ",";
		outFile << " ALUSrc = " << ALUSrc << ",";
		std::cout << " ALUop = " << std::dec << std::setw(2) << ALUOp << ",";
		outFile << " ALUop = " << std::dec << std::setw(2) << ALUOp << ",";
		std::cout << " MemRead = " << MemRead << ", ";
		outFile << " MemRead = " << MemRead << ", ";
		std::cout << " MemWrite = " << memWrite << ",";
		outFile << " MemWrite = " << memWrite << ",";
		std::cout << " Branch = 0 ,";
		outFile << " Branch = 0 ,";
		std::cout << " MemToReg " << MemToReg << ",";
		outFile << " MemToReg " << MemToReg << ",";
		std::cout << " RegWrite = " << RegWrite << ",";
		outFile << " RegWrite = " << RegWrite << ",";
		std::cout << std::endl;
		outFile << std::endl;
		std::cout << std::hex << std::uppercase << "IncrPC " << pc;
		outFile << std::hex << std::uppercase << "IncrPC " << pc;
		std::cout << " ReadReg1Value = " << readData1 << " ReadReg2Value = " << readData2 << " SEoffset = "
			<< offset <<std::dec << " WriteReg_20_16 = " << writeReg2016 << " WriteReg_15_11 = " << writeReg1511
			<< " Function = " << function << std::endl;
		outFile << " ReadReg1Value = " << readData1 << " ReadReg2Value = " << readData2 << " SEoffset = "
			<< offset <<std::dec << " WriteReg_20_16 = " << writeReg2016 << " WriteReg_15_11 = " << writeReg1511
			<< " Function = " << function << std::endl;
	}
	std::cout << std::endl;
	outFile << std::endl;
}

void Pipeline::displayEXMEMWrite(std::ostream &outFile)
{
	//set controls pass to these EX/MEM stage
	int memR = EX_MEM_Write.getMemReadEX();
	int memW = EX_MEM_Write.getMemWriteEX();
	std::string memToReg = EX_MEM_Write.getMemtoRegEX();
	int regWrite = EX_MEM_Write.getRegWriteEX();

	//set data to EX/MEM
	int data1 = EX_MEM_Write.getReadData1EX();
	signed short data2 = EX_MEM_Write.getReadData2EX();
	int zero = 0;
	int ALUresult = EX_MEM_Write.getALUresultEX();
	int Value = EX_MEM_Write.getswValueEX();
	std::string writeRegNum = EX_MEM_Write.getWriteRegNumEX();

	std::cout << "EX/MEM Write (written to by the EX stage) " << std::endl;
	outFile << "EX/MEM Write (written to by the EX stage) " << std::endl;
	if (ALUresult == 0)
	{
		std::cout << "Control: 00000000 " << std::endl;
		outFile << "Control: 00000000 " << std::endl;
	}
	else
	{
		std::cout << "Control: ";
		outFile << "Control: ";
		std::cout << "MemRead = " << memR << ", MemWrite = " << memW << ", Branch = 0" << ", MemToReg = " << memToReg
		<< ", RegWrite = " << regWrite << std::endl;
		outFile << "MemRead = " << memR << ", MemWrite = " << memW << ", Branch = 0" << ", MemToReg = " << memToReg
			<< ", RegWrite = " << regWrite << std::endl;
		std::cout << "CalcBTA = X, " << "Zero = " << zero << std::hex << std::uppercase << " ALUResult = " << ALUresult <<
		", SWvalue = " << Value << ", WriteRegNum = " << writeRegNum << std::endl;
		outFile << "CalcBTA = X, " << "Zero = " << zero << std::hex << std::uppercase << " ALUResult = " << ALUresult <<
			", SWvalue = " << Value << ", WriteRegNum = " << writeRegNum << std::endl;
	}
	std::cout << std::endl;
	outFile << std::endl;
}
void Pipeline::displayEXMEMRead(std::ostream &outFile)
{
	//set all controls that are needed to EX/MEM read
	int memR = EX_MEM_Read.getMemReadEX();
	int memW = EX_MEM_Read.getMemWriteEX();
	std::string memToReg = EX_MEM_Read.getMemtoRegEX();
	int regWrite = EX_MEM_Read.getRegWriteEX();

	//set data 
	int data1 = EX_MEM_Read.getReadData1EX();
	int data2 = EX_MEM_Read.getReadData2EX();
	int zero = 0;
	int ALUresult = EX_MEM_Read.getALUresultEX();
	int Value = EX_MEM_Read.getswValueEX();
	std::string writeRegNum = EX_MEM_Read.getWriteRegNumEX();

	std::cout << "EX/MEM Read (Read by the Mem stage) " << std::endl;
	outFile << "EX/MEM Read (Read by the Mem stage) " << std::endl;
	if (ALUresult == 0)
	{
		std::cout << "Control: 00000000 " << std::endl;
		outFile << "Control: 00000000 " << std::endl;
	}
	else
	{
		std::cout << "Control: ";
		outFile << "Control: ";
		std::cout << "MemRead = " << memR << ", MemWrite = " << memW << ", Branch = 0" << ", MemToReg = " << memToReg
			<< ", RegWrite = " << regWrite << std::endl;
		outFile << "MemRead = " << memR << ", MemWrite = " << memW << ", Branch = 0" << ", MemToReg = " << memToReg
			<< ", RegWrite = " << regWrite << std::endl;
		std::cout << "CalcBTA = X, " << "Zero = " << zero << std::hex << std::uppercase << " ALUResult = " << ALUresult <<
			", SWvalue = " << Value << ", WriteRegNum = " << writeRegNum << std::endl;
		outFile << "CalcBTA = X, " << "Zero = " << zero << std::hex << std::uppercase << " ALUResult = " << ALUresult <<
			", SWvalue = " << Value << ", WriteRegNum = " << writeRegNum << std::endl;
	}
	std::cout << std::endl;
	outFile << std::endl;
}
void Pipeline::displayMemWBWrite(std::ostream &outFile)
{
	int ALUresult = MEM_WB_Write.getALUresultMEM();
	std::string MemtoReg = MEM_WB_Write.getMemToRegMem();
	int regWrite = MEM_WB_Write.getRegWriteMem();
	std::string WriteRegNum = MEM_WB_Write.getWriteRegNumMEM();
	std::string lwDataVal = MEM_WB_Write.getLwDataValMEM();
		
	std::cout << "MEM/WB Write(written to by the MEM stage)" << std::endl;
	outFile << "MEM/WB Write(written to by the MEM stage)" << std::endl;
	if (ALUresult == 0)
	{
		std::cout << "Control = 00000000" << std::endl;
		outFile << "Control = 00000000" << std::endl;
	}
	else
	{
		std::cout << "MemToReg = " << MemtoReg << ", RegWrite = " << regWrite << std::endl;
		outFile << "MemToReg = " << MemtoReg << ", RegWrite = " << regWrite << std::endl;
		std::cout << "LWDataValue = " << lwDataVal << " ALUResult = " << ALUresult << " WriteRegNum = " << WriteRegNum << std::endl;
		outFile << "LWDataValue = " << lwDataVal << " ALUResult = " << ALUresult << " WriteRegNum = " << WriteRegNum << std::endl;
	}
	std::cout << std::endl;
	outFile << std::endl;
}

void Pipeline::displayMemWBRead(std::ostream &outFile)
{
	int ALUresult = MEM_WB_Read.getALUresultMEM();
	std::string MemtoReg = MEM_WB_Read.getMemToRegMem();
	int regWrite = MEM_WB_Read.getRegWriteMem();
	std::string WriteRegNum = MEM_WB_Read.getWriteRegNumMEM();
	std::string lwDataVal = MEM_WB_Read.getLwDataValMEM();

	std::cout << "MEM/WB Read(Read to by the WB stage)" << std::endl;
	outFile << "MEM/WB Read(Read to by the WB stage)" << std::endl;
	if (ALUresult == 0)
	{
		std::cout << "Control = 00000000" << std::endl;
		outFile << "Control = 00000000" << std::endl;
	}
	else
	{
		std::cout << "MemToReg = " << MemtoReg << ", RegWrite = " << regWrite << std::endl;
		outFile << "MemToReg = " << MemtoReg << ", RegWrite = " << regWrite << std::endl;
		std::cout << "LWDataValue = " << lwDataVal << " ALUResult = " << ALUresult << " WriteRegNum = " << WriteRegNum << std::endl;
		outFile << "LWDataValue = " << lwDataVal << " ALUResult = " << ALUresult << " WriteRegNum = " << WriteRegNum << std::endl;
	}
	std::cout << std::endl;
	outFile << std::endl;
}