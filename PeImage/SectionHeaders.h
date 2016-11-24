#pragma once
#include "ISectionHeaders.h"
namespace PeDecoder
{	
	class PeImage;
	class SectionHeaders:
		public ISectionHeaders
	{
	public:
		typedef Detail::Section* DataPtr;
		typedef DataPtr iterator;

		explicit SectionHeaders(const PeImage& pe);

		virtual DataPtr RawPtr() const override;
		virtual WORD GetSize() const override;
		virtual DWORD GetSectionAlignment() const override;

		virtual DataPtr RvaToSectionHeader(DWORD rva) const override;
		virtual DataPtr OffsetToSectionHeader(DWORD fileOffset) const override;

		// Ϊ�˼���c++�㷨������ĸ����д��
		virtual iterator begin() const override;
		// ��β����һԪ�ص�ַ
		virtual iterator end() const override;
		virtual ~SectionHeaders();
	protected:
		WORD size_;
		DWORD alignment_;
		DataPtr ptr_;
	};

}  // namespace PeDecoder
