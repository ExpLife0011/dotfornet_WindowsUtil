#pragma once
#include <Windows.h>
#include "../../Common/Common.h"
#include "OpcodeDef.h"
// OpcodeData��װ
class AsmOpcodeWapper
{
	_STD unique_ptr<OpcodeData[]> table0F38;
	_STD unique_ptr<OpcodeData[]> table0F3A;
	typedef const unsigned char(&OperandGroup2NodeType)[2];
	typedef const unsigned char(&OperandGroup3NodeType)[3];
	typedef const unsigned char(&OperandGroup4NodeType)[4];

public:
	AsmOpcodeWapper();

	~AsmOpcodeWapper();

	static _STD unique_ptr<OpcodeData[]> UnzipOpcodeData(const ZipOpcodeData zipArray[], int count);



	// ȡ1�ֽڱ�
	const OpcodeData& GetOpcodeData(int hex);
	// ȡ2�ֽڱ�
	const OpcodeData& GetTable0FOpcodeData(int hex);

	// ȡ3�ֽ�38��
	const OpcodeData& GetTable0F38OpcodeData(int hex);
	// ȡ3�ֽ�3A��
	const OpcodeData& GetTable0F3AOpcodeData(int hex);
	const Hex_Inst& GetHex_Inst(int index);

	const unsigned char& GetOperandGroup1(int index);

	OperandGroup2NodeType GetOperandGroup2(int index);
	OperandGroup3NodeType GetOperandGroup3(int index);
	OperandGroup4NodeType GetOperandGroup4(int index);

	const GrpInstData& GetGrpInst(int index);
	const PrefixInstData& GetPfxInst(int index);
	const InstChangeData& GetInstChange(int index);
	const RegOrOperandGroup& GetOperands(int index);
	const InstData& GetInst(int index);
	const LPCSTR& GetInstructionNames(int index);

	const char * GetRegisterName(unsigned char hex, RegisterLength type);

	const char * GetSegName(OperandType seg);

};
