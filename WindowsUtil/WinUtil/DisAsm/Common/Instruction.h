#pragma once
#include "Common.h"

// ��ʾһ��ָ�������ʱ�洢��״̬���õı���
class Instruction :public _STD enable_shared_from_this<Instruction>
{
protected:
	bool isSuccess;
	unsigned char* beginPtr;
	unsigned char* currentPtr;
	shared_ptr<IStateFactory>& factory;
public:

	explicit Instruction(shared_ptr<IStateFactory> factory)
		:factory(factory)
	{
	}
	virtual ~Instruction()
	{
	}
	template<typename TCast>
	shared_ptr<TCast> Cast()
	{
		return dynamic_pointer_cast<TCast>(shared_from_this());
	}
	// ptrΪ��ȡ��ʼλ��
	virtual void Init(void* ptr)
	{
		assert(ptr != NULL);
		currentPtr = beginPtr = reinterpret_cast<unsigned char*>(ptr);
		isSuccess = false;
		factory->Reset();
	}
	// �Ե�ǰ��ȡλ�����ô洢����
	virtual void Reset()
	{
		Init(CurrentBytePtr());
	}

	// �ɹ�����ָ���
	virtual int GetLength()
	{
		if (IsSuccess())
		{
			return currentPtr - beginPtr;
		}
		return 0;
	}

	template<typename TStateFactory = IStateFactory>
	shared_ptr<TStateFactory> GetFactory()
	{
		return dynamic_pointer_cast<TStateFactory>(factory);
	}
	template<>
	shared_ptr<IStateFactory> GetFactory()
	{
		return factory;
	}
	virtual unsigned char* CurrentBytePtr()
	{
		return currentPtr;
	}
	virtual void NextByte()
	{
		currentPtr++;
	}
	// �Ƿ�����ɹ�
	virtual bool IsSuccess()
	{
		return isSuccess;
	}
};

