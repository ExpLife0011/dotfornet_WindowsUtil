#pragma once
#include "..\Common\Common.h"
class OpcodeReader
{
public:

	OpcodeReader()
	{
	}
	// ���ض�ȡ����, ��ȡ��Ϣ������inst������
	int Read(shared_ptr<IInstruction>& inst)
	{
		auto& current = inst->GetFactory()->GetBeginStateInstance();
		while ((current = current->Next(inst))->HasNext());
		return inst->GetLength();		
	}
	~OpcodeReader()
	{
	}
};

