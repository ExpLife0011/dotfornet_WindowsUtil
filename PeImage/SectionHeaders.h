#pragma once
#include "DataPtr.h"
#include "DataSize.h"

namespace PeDecoder
{
	class SectionHeaders:
		public Detail::DataPtr<PIMAGE_SECTION_HEADER>,
		public Detail::DataSize<PWORD>
	{
	public:
		typedef TDataPtr iterator;
		SectionHeaders(TDataPtr ptr, TSizePtr sizePtr, PDWORD sectionAlignmentPtr);

		~SectionHeaders() = default;
		PDWORD GetSectionAlignment();

		TDataPtr RvaToSectionHeader(DWORD rva);
		TDataPtr OffsetToSectionHeader(DWORD fileOffset);

		// Ϊ�˼���c++�㷨������ĸ����д��
		iterator begin() const;
		// ��β����һԪ�ص�ַ
		iterator end() const;

	protected:
		// ���뱣����Դ�����ṩ�޸�
		PDWORD sectionAlignmentPtr_;
	};
	
}  // namespace PeDecoder
