#pragma once
#include "Common.h"
// ��Ҫ��������̫�����ö���
class IStateFactory
{
	IStateFactory(const IStateFactory&) = delete;
protected:
	// ȡ����״̬
	virtual const State* GetState(unsigned char) = 0;
public:

	IStateFactory()
	{
	}
	// ȡ�����
	virtual const State* GetBeginStateInstance() = 0;
	// ����
	virtual void Reset() = 0;
	virtual ~IStateFactory()
	{
	}
};
