#pragma once
#include "../Common/Common.h"
namespace PE
{
	// �����Thunk�ṹ��ȡ��
	class ImportDescriptorIterator;
	class ImportThunkIterator
	{
		
		bool is32;
		PVOID currentThunk;
		PVOID currentOriginalThunk;

		PVOID originalThunk;
		PVOID thunk;
		void Init(PIMAGE_IMPORT_DESCRIPTOR descriptor, PeDecoder& pe);
	public:
		ImportThunkIterator(ImportDescriptorIterator& importDescriptorIterator);
		ImportThunkIterator(PIMAGE_IMPORT_DESCRIPTOR descriptor, PeDecoder& pe)
		{
			Init(descriptor, pe);
		}

		PIMAGE_THUNK_DATA32 CurrentThunk32();
		PIMAGE_THUNK_DATA32 CurrentOriginalThunk32();
		PIMAGE_THUNK_DATA64 CurrentThunk64();

		PIMAGE_THUNK_DATA64 CurrentOriginalThunk64();




		bool Next();
		void Reset();
		~ImportThunkIterator();

	};

}