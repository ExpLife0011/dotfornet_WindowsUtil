#pragma once
#include "..\Common\Common.h"
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
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) override;
	
};

