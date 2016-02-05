#pragma once
#include "Common.h"

// ��ʾһ��ָ�������ʱ�洢��״̬���õı���
class Instruction
{
protected:
	bool isSuccess;
	const unsigned char* beginPtr;
	const unsigned char* currentPtr;
	shared_ptr<IStateFactory> factory;
	void SetSuccess()
	{
		isSuccess = true;
	}
public:

	explicit Instruction(const shared_ptr<IStateFactory>& factory)
	{
		assert(factory != nullptr);
		this->factory = factory;
		isSuccess = false;
	}
	virtual ~Instruction() = default;
	template<typename TCast>
	TCast* Cast()
	{
		return dynamic_cast<TCast*>(this);
	}
	// ptrΪ��ȡ��ʼλ��
	virtual void Init(const void* ptr)
	{
		assert(ptr != NULL);
		currentPtr = beginPtr = reinterpret_cast<const unsigned char*>(ptr);
		isSuccess = false;
		assert(factory!=nullptr);
		factory->Reset();
	}
	// �Ե�ǰ��ȡλ�����ô洢����
	virtual void Reset()
	{
		Init(CurrentBytePtr());
	}

	// �ɹ�����ָ���
	virtual int GetLength() const
	{
		if (IsSuccess())
		{
			return currentPtr - beginPtr;
		}
		return 0;
	}

	template<typename TStateFactory = IStateFactory>
	shared_ptr<TStateFactory> GetFactory() const
	{
		return dynamic_pointer_cast<TStateFactory>(factory);
	}
	template<>
	shared_ptr<IStateFactory> GetFactory() const
	{
		return factory;
	}
	virtual const unsigned char* CurrentBytePtr() const
	{
		return currentPtr;
	}
	virtual void NextByte()
	{
		currentPtr++;
	}
	// �Ƿ�����ɹ�
	virtual bool IsSuccess() const
	{
		return isSuccess;
	}
};

