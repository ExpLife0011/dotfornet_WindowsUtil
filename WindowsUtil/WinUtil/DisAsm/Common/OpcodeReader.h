#pragma once
#include "Common.h"
class OpcodeReader
{
public:

	OpcodeReader()
	{
	}
	// ���ض�ȡ����, ��ȡ��Ϣ������inst������
	int Read(const shared_ptr<Instruction>& inst) const
	{
		auto current = inst->GetFactory()->GetBeginStateInstance();
		while (current != NULL && current->HasNext())
		{
			current = current->Next(inst);
			assert(current);
		}
		return inst->GetLength();
	}
	~OpcodeReader()
	{
	}
};

