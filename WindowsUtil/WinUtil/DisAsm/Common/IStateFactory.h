#pragma once
#include "..\Common\Common.h"
// ��Ҫ��������̫�����ö���
class IStateFactory
{
public:

	IStateFactory()
	{
	}
	// ȡ�����
	virtual shared_ptr<IState> GetBeginStateInstance() = 0;
	// ȡ����״̬
	virtual shared_ptr<IState> GetState(unsigned char) = 0;
	virtual ~IStateFactory()
	{
	}
};
