#pragma once
#include "Common.h"
class OpcodeReader
{
public:

	OpcodeReader()
	{
	}
	// ���ض�ȡ����, ��ȡ��Ϣ������inst������
	int Read(shared_ptr<Instruction>& inst)
	{
		auto current = inst->GetFactory()->GetBeginStateInstance().get();
		while (current!=NULL && current->HasNext())
		{
			auto& tmpState = current->Next(inst);
			assert(tmpState);
			current = tmpState.get();
		}
		return inst->GetLength();
	}
	~OpcodeReader()
	{
	}
};

