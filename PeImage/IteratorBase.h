#pragma once
#include <iterator>
#include "CategoryPolicy.h"
template<
	typename TIterator,
	typename TCategory,
	typename TValueType,
	typename TDiff = ptrdiff_t,
	typename TPointer = TValueType *,
	typename TReference = TValueType&>
	struct IteratorBase :
	public CategoryPolicy<TIterator, TCategory, TValueType, TDiff, TPointer, TReference>,
	public _STD iterator<TCategory, TValueType, TDiff, TPointer, TReference>
{
	typedef TIterator TIterator;
/*
	û��ô��飬�����д�

	������friend IteratorFriendAccess;

	����ѡ���tagʵ�ֶ�Ӧ�Ľӿ�
	��ʽ�ӿ�Ϊ��

	// �ɷ�������ĵ���������
	void Decrement()
	{
	}
	// val-���� ����
	difference_type DistanceTo(const TIterator & val) const
	{
	}
	void Advance(int n)
	{
	}

	// ����
	bool Equal(const TIterator & val) const
	{
	}
	void Increment()
	{
	}
	reference Dereference()
	{
	}
	// ����ָ������ʱ���õ��Զ���
	pointer AddressOf()
	{
	}
*/
};
