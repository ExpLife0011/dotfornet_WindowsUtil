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
	virtual  const State*  Next(const shared_ptr<Instruction>& inst) const override;
};

