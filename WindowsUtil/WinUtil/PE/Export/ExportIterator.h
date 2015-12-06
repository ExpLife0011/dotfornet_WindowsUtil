#pragma once
#include "../Common/Common.h"
namespace PE
{
	// �������ȡ�� 
	// ֻ�����ֱ���, ��Ϊ�ṹ��ϵ, û�����ֵĺ����ᱻ©��
	template<typename _ExportDirectory>
	class ExportIterator
	{
		_ExportDirectory& export;
		int currentIndex;
	public:
		ExportIterator(_ExportDirectory& export) :export(export)
		{
			Reset();
		}
		~ExportIterator() {}

		PDWORD CurrentFuncRva()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &export.funcsTable[export.nameOrdinalsTable[currentIndex]];
		}
		PDWORD CurrentNameRva()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &export.namesTable[currentIndex];
		}
		PWORD CurrentNameOrdinals()
		{
			if (currentIndex == -1)
			{
				return NULL;
			}
			return &export.nameOrdinalsTable[currentIndex];
		}
		bool Next()
		{
			if (export.numberOfNames)
			{
				if (++currentIndex < *export.numberOfNames)
				{
					return true;
				}
			}
			return false;
		}
		void Reset()
		{
			currentIndex = -1;
		}
	};


}