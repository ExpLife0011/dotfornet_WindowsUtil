#pragma once
#include "AsmCommon.h"
// �˳�����ѭ��
class ExitState :
	public State
{
public:

	ExitState()
	{
	}

	~ExitState()
	{
	}
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
	virtual bool HasNext()  override;;
};

