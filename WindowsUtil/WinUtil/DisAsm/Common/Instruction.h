#pragma once
#include "Common.h"

// ��ʾһ��ָ�������ʱ�洢��״̬���õı���
class Instruction
{
	Instruction(const Instruction&) = delete;
protected:
	bool isSuccess;
	const unsigned char* beginPtr;
	const unsigned char* currentPtr;
	unsigned int range;  // ��ȡ�����Ʒ�Χ������Ϊ0��ʾ����
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
	virtual void Init(const void* ptr, unsigned int range)
	{
		assert(ptr != NULL);
		beginPtr = reinterpret_cast<const unsigned char*>(ptr);
		currentPtr = 0;
		isSuccess = false;
		assert(factory != nullptr);
		factory->Reset();
		this->range = range;
	}
	void Init(const void* ptr)
	{
		Init(ptr, 0);
	}
	// �Ե�ǰ��ȡλ�����ô洢����
	virtual void Reset()
	{
		Init(CurrentBytePtr());
	}
	// �����Ѷ�����
	int ReadCount() const
	{
		return currentPtr == NULL ? 0 : currentPtr - beginPtr;
	}

	// �ɹ�����ָ���
	virtual int GetInstructionLength() const
	{
		return IsSuccess() ? ReadCount() : 0;
	}

	template<typename TStateFactory = IStateFactory>
	TStateFactory* GetFactory() const
	{
		return dynamic_cast<TStateFactory*>(factory.get());
	}
	template<>
	IStateFactory* GetFactory() const
	{
		return factory.get();
	}

	virtual const unsigned char* CurrentBytePtr() const
	{
		return currentPtr;
	}
	// ��һ�β������ó�ʼλ�ÿ�ʼ��ȡ
	virtual bool NextByte()
	{
		if (currentPtr == 0)
		{
			currentPtr = beginPtr;
			return true;
		}

		++currentPtr;
		return (range == 0) | (ReadCount() < range);
	}
	// �Ƿ�����ɹ�
	virtual bool IsSuccess() const
	{
		return isSuccess;
	}
};

