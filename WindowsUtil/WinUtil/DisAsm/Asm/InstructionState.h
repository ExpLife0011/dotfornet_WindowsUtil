#pragma once
// �����ﴦ��ָ��
// ����������ƣ�����ָ����Ϣ������ת����ȡ���������Ƕ�ȡRM
// ����ת��������RM״̬

#include "..\Common\Common.h"
#include "Opcode\OpcodeDef.h"
class InstructionState :
	public State
{
public:

	InstructionState()
	{
	}

	~InstructionState()
	{
	}
	virtual  const State*  Next(const shared_ptr<Instruction>& inst)  const override;
	
};

