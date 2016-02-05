#pragma once
#include "Common.h"
class Instruction;
class State
{
public:
	// ִ�в�������һ��״̬
	virtual const State* Next(const shared_ptr<Instruction>& inst) const = 0;
	// ָʾ�Ƿ��Ѿ�����(ͨ�������޸ķ���ֵ��ָʾ����״̬
	virtual bool HasNext() const
	{
		return true;
	};
	virtual ~State()
	{
	}
};

