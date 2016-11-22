#pragma once
#include <Windows.h>
#include "Section.h"
namespace PeDecoder
{
	__interface ISectionHeaders
	{
		Detail::Section* RawPtr() const;
		WORD GetSize() const;
		DWORD GetSectionAlignment() const;

		Detail::Section* RvaToSectionHeader(DWORD rva) const;
		Detail::Section* OffsetToSectionHeader(DWORD fileOffset) const;

		// Ϊ�˼���c++�㷨������ĸ����д��
		Detail::Section* begin() const;
		// ��β����һԪ�ص�ַ
		Detail::Section* end() const;
	};
}  // namespace PeDecoder