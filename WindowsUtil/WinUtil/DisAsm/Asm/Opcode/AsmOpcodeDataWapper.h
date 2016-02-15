#pragma once
#include <Windows.h>
#include "../../Common/Common.h"
#include "OpcodeDef.h"
// OpcodeData��װ
class AsmOpcodeDataWapper
{
	unique_ptr<OpcodeData[]> table0F38;
	unique_ptr<OpcodeData[]> table0F3A;
	AsmOpcodeDataWapper(const AsmOpcodeDataWapper& obj) = delete;
public:
	AsmOpcodeDataWapper();

	~AsmOpcodeDataWapper();
	
	static _STD unique_ptr<OpcodeData[]> UnzipOpcodeData(const ZipOpcodeData zipArray[], int count);

	// ȡ���������
	const unsigned char* GetOperandGroup(int opCount, int index) const;
	// ����ֵ�Ƿ���OperandTypeö���ж���ΪSEG
	bool IsSeg(unsigned char val) const
	{
		return val >= SEG_CS && val <= SEG_SS;
	}

	// ����:ȡ1�ֽڱ�
	// OT_Table_0F:ȡ2�ֽڱ�
	// OT_Table_0F38:ȡ3�ֽ�38��
	// OT_Table_0F3A:ȡ3�ֽ�3A��
	const OpcodeData& GetOpcodeData(OpcodeType tableType, int hex);
	// ȡ�ֽ�-ָ���Ӧ��ϵ��,����OpcodeData��¼���±�
	const Hex_Inst& GetHex_Inst(int index) const;
	// ȡָ��-���Ӧ��
	const GrpInstData& GetGrpInst(int index) const;
	// ȡǰ׺��
	const PrefixInstData& GetPfxInst(int index) const;
	// ȡָ�������׺�ַ�����
	const InstChangeData& GetInstChange(int index) const;
	// ȡָ���
	const InstData& GetInst(int index) const;
	// ȡ������
	const RegOrOperandGroup& GetOperands(int index) const;
	// ȡָ������
	const LPCSTR& GetInstructionNames(int index) const;
	// ȡ�Ĵ�������
	const char * GetRegisterName(unsigned char hex, RegisterLength type) const;
	const char * GetRegisterName(OperandType reg) const;

	// ȡ�μĴ�������
	const char * GetSegName(OperandType seg) const;


};
