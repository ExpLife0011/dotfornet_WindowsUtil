#pragma once
#include "AsmCommon.h"
class InitState :
	public State
{
public:

	InitState()
	{
	}

	~InitState()
	{
	}

	// ͨ�� State �̳�
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
	
};

