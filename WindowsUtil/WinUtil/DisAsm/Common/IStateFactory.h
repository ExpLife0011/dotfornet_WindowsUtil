#pragma once
#include "Common.h"
// ��Ҫ��������̫�����ö���
class IStateFactory
{
	IStateFactory(const IStateFactory&) = delete;
protected:
	
public:

	IStateFactory()
	{
	}
	// ȡ����״̬
	virtual const State* GetState(unsigned char) = 0;
	// ȡ�����
	virtual const State* GetBeginStateInstance() = 0;
	// ����
	virtual void Reset() = 0;
	virtual ~IStateFactory()
	{
	}
};
