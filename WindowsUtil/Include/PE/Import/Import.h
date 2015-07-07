#pragma once
#include "ImportDescriptorReader.h"
#include "ImportThunkReader.h"
namespace PE
{
	namespace Import
	{
		LPSTR GetDescriptorName(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR descriptor);
		 PIMAGE_IMPORT_BY_NAME GetNameStruct(PeDecoder& pe, PIMAGE_THUNK_DATA32 thunk);
		 PIMAGE_IMPORT_BY_NAME GetNameStruct(PeDecoder& pe, PIMAGE_THUNK_DATA64 thunk);
		 bool IsSnapByOrdinal(PIMAGE_THUNK_DATA32 thunk);
		 bool IsSnapByOrdinal(PIMAGE_THUNK_DATA64 thunk);
		 ULONGLONG GetOrdinal(PIMAGE_THUNK_DATA64 thunk);
		 DWORD GetOrdinal(PIMAGE_THUNK_DATA32 thunk);
		 PVOID GetProcImportThunkAddress(PeDecoder& pe, LPCSTR dllName, LPCSTR procName); // ���û��dllName��ƥ���һ�������ĺ�����

	}
}