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
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) override;
};

