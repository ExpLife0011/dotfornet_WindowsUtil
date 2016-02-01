#pragma once
#include "Common.h"
class Instruction;
class IState
{
public:
	// ִ�в�������һ��״̬
	virtual  const unique_ptr<IState>&  Next(shared_ptr<Instruction>& inst) = 0;
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
