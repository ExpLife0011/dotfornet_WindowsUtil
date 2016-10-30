#pragma once
#include "DataPtr.h"
#include "DataSize.h"
#include "SectionIterator.h"
#include "IPeImage.h"
namespace PeDecoder
{
	namespace Detail
	{
		struct Section;
	}
	class SectionHeaders :
		public Detail::DataPtr<Detail::Section*>,
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
