#pragma once
#include "AsmCommon.h"
// ������һЩ��β����
class EndState :
	public State
{
public:

	EndState()
	{
	}

	~EndState()
	{
	}
	virtual  const State*  Next(const shared_ptr<Instruction>& inst) const override;
};

