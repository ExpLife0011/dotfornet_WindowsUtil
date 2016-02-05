#pragma once
#include <Windows.h>
#include "../../Common/Common.h"
#include "OpcodeDef.h"
// OpcodeData��װ
class AsmOpcodeWapper
{
	_STD unique_ptr<OpcodeData[]> table0F38;
	_STD unique_ptr<OpcodeData[]> table0F3A;

public:
	AsmOpcodeWapper();

	~AsmOpcodeWapper();

	static _STD unique_ptr<OpcodeData[]> UnzipOpcodeData(const ZipOpcodeData zipArray[], int count);


	const unsigned char* GetOperandGroup(int opCount, int index);
	// ȡ1�ֽڱ�
	const OpcodeData& GetOpcodeData(int hex);
	// ȡ2�ֽڱ�
	const OpcodeData& GetTable0FOpcodeData(int hex);

	// ȡ3�ֽ�38��
	const OpcodeData& GetTable0F38OpcodeData(int hex);
	// ȡ3�ֽ�3A��
	const OpcodeData& GetTable0F3AOpcodeData(int hex);
	const Hex_Inst& GetHex_Inst(int index);


	

	const GrpInstData& GetGrpInst(int index);
	const PrefixInstData& GetPfxInst(int index);
	const InstChangeData& GetInstChange(int index);
	const RegOrOperandGroup& GetOperands(int index);
	const InstData& GetInst(int index);
	const LPCSTR& GetInstructionNames(int index);

	const char * GetRegisterName(unsigned char hex, RegisterLength type);

	const char * GetSegName(OperandType seg);

};
