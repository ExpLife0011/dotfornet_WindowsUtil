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
	virtual  const State*  Next(const shared_ptr<Instruction>& inst) const override;
	virtual bool HasNext() const  override;
};

