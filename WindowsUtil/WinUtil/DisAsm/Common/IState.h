#pragma once
#include "Common.h"
class IInstruction;
class IState
{
public:
	// ִ�в�������һ��״̬
	virtual shared_ptr<IState> Next(shared_ptr<IInstruction>& inst) = 0;
	// ָʾ�Ƿ��Ѿ�����
	virtual bool HasNext() = 0;
	virtual ~IState()
	{
	}
};
class State:public IState
{
public:

	State()
	{
	}
	virtual bool HasNext()  override
	{ 
		return true; 
	};
};
