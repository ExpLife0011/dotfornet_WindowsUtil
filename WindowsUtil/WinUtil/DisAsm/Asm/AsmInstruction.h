#pragma once
#include "..\Common\Common.h"
#include "Opcode\AsmOpcodeWapper.h"

class StateFactory;
class AsmInstruction
	:public Instruction
{
	friend class InitState;
	//friend class SibState;
	//friend class RmState;
	friend class EscapeState;
	friend class GroupState;
	friend class InstructionState;
	friend class PrefixState;
	friend class ByteState;
	friend class EndState;
	friend class OperandState;
	friend class AsmOpcodeWapper;
private:
	shared_ptr<AsmOpcodeWapper> wapper;
	bool isX32;
	shared_ptr<_STD ostringstream> outputStr;

	// �����Ƕ�ȡ��������Ҫ��¼����Ϣ
	const unsigned char* operandGrp;
	unsigned char operandCount;
	static const int MaxOperandCount = 4;
	unsigned char operandSize[MaxOperandCount];  // ������(������)��ռ���ֳ����ڶ�ȡoperandGrp�Ὣ��Ӧ�����ֳ����ú�
	void SetOperandGrp(unsigned char count, const unsigned char* grp)
	{
		operandCount = count;
		operandGrp = grp;
	}
	void SetOperandSize(int index, unsigned char val)
	{
		operandSize[index] = val;
	}
	const unsigned char* GetOperandGrp() const
	{
		return operandGrp;
	}
	unsigned char GetOperandCount() const
	{
		return operandCount;
	}
	void ClearOperand()
	{
		for (auto i = 0; i < MaxOperandCount; i++)
		{
			SetOperandSize(i, 0);
		}
		SetOperandGrp(0, NULL);
	}

	// ������״̬����Ҫ���ݵ���ʱ������ֻ������OpcodeData��Ķ�����
	const void* tmpInstData;
	OpcodeType tmpInstType;

	// ȡ��ʱ����ָ��,�±�Ϊ��Ӧ����
	// OT_Inst - InstData
	// OT_Inst_Change - InstChangeData
	// OT_Prefix - PrefixInstData
	// OT_Grp - GrpInstData
	// OT_Table_0F - ��
	// OT_Table_0F38 - ��
	// OT_Table_0F3A - ��
	// OT_Esc - ��
	template<typename TOpcodeData>
	const TOpcodeData* GetTmpData()
	{
		return reinterpret_cast<const TOpcodeData*>(tmpInstData);
	}
	OpcodeType GetTmpInstType();
	void SetTmpData(OpcodeType type, const void* ptr);
	void ClearTmpData();
	// end


	_STD shared_ptr<AsmOpcodeWapper>& GetOpcodeDataWapper();
	// ����������������������Ϊ����ֻ���ָ��ȣ���������
	void SetOutputStream(const shared_ptr<_STD ostringstream>& output);
	bool IsX32();
	// TODO: ȡ�õ�ǰǰ׺�ж�������������ǰ׺��
	int GetCurrentPfxcdt();
	// �Ե�ǰ�α�λ����Ϊ��ʼ��ȡָ���123ָ�������,
	// ������ʾ�����ͣ�ֻ��1(��None��ʾ)��0F��0F38��0F3A��
	OpcodeType ReadInst(OpcodeType table);
	// �ж��Ƿ�ѡ���ָ���ϵ ,��Ҫ�жϵ�ǰ��ȡ����ǰ׺��ϣ�ֻ��66��F2��F3��
	// �ɹ��󷵻�true�����Ӧ���ݴ洢��������ʱ�������������Ϊѡ�񵽵�����
	// ����ʧ�ܷ���false��ʾָ����ڣ�ͬʱGetTmpInstType()ΪNULL
	bool SelectInst(const Hex_Inst& hexInst);
	// �Ե�ǰ��ȡ������Ϣ��ָ֤���Ƿ����
	bool VerifyCondition(Superscript ss, PrefixCondition pfx);

public:
	// ʵ����ʱ���ý���ָ���ֳ�
	explicit AsmInstruction(const shared_ptr<StateFactory>& factory, bool isX32);
	// ��ʼ��,������ʼ��ȡλ��
	virtual void Init(const void* ptr) override;
	~AsmInstruction();
};
