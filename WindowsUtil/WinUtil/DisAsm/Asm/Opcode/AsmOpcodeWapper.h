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

	// ȡ���������
	const unsigned char* GetOperandGroup(int opCount, int index);

	// OT_None:ȡ1�ֽڱ�
	// OT_Table_0F:ȡ2�ֽڱ�
	// OT_Table_0F38:ȡ3�ֽ�38��
	// OT_Table_0F3A:ȡ3�ֽ�3A��
	const OpcodeData& GetOpcodeData(OpcodeType tableType, int hex);
	// ȡ�ֽ�-ָ���Ӧ��ϵ��
	const Hex_Inst& GetHex_Inst(int index);
	// ȡָ��-���Ӧ��
	const GrpInstData& GetGrpInst(int index);
	// ȡǰ׺��
	const PrefixInstData& GetPfxInst(int index);
	// ȡָ�������׺�ַ�����
	const InstChangeData& GetInstChange(int index);
	// ȡָ���
	const InstData& GetInst(int index);
	// ȡ������
	const RegOrOperandGroup& GetOperands(int index);
	// ȡָ������
	const LPCSTR& GetInstructionNames(int index);
	// ȡ�Ĵ�������
	const char * GetRegisterName(unsigned char hex, RegisterLength type);
	// ȡ�μĴ�������
	const char * GetSegName(OperandType seg);

};
