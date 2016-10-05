#pragma once
#include "DataPtr.h"
#include "DataSize.h"
#include "SectionIterator.h"
#include "IPeImage.h"
namespace PeDecoder
{

	class SectionHeaders :
		public Detail::DataPtr<PIMAGE_SECTION_HEADER>,
		public Detail::DataSize<PWORD>
	{
	public:
		typedef Detail::SectionIterator iterator;
		SectionHeaders(TDataPtr ptr, TSizePtr sizePtr, PDWORD sectionAlignmentPtr);
		explicit SectionHeaders(const IPeImage& pe);
		PDWORD GetSectionAlignment() const;

		TDataPtr RvaToSectionHeader(DWORD rva) const;
		TDataPtr OffsetToSectionHeader(DWORD fileOffset) const;

		// Ϊ�˼���c++�㷨������ĸ����д��
		iterator begin() const;
		// ��β����һԪ�ص�ַ
		iterator end() const;

	protected:
		// ���뱣����Դ�����ṩ�޸�
		PDWORD sectionAlignmentPtr_;
	};

}  // namespace PeDecoder
