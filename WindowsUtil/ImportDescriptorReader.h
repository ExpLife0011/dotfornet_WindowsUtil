#pragma once
#include "PeDecoder.h"
namespace PE
{
	// �����Descriptor�ṹ��ȡ��
	class ImportDescriptorReader
	{
	public:
		ImportDescriptorReader(PeDecoder& pe);
		~ImportDescriptorReader();
		bool Next();
		PIMAGE_IMPORT_DESCRIPTOR Current();
		static PCHAR GetDescriptorName(PeDecoder& pe, PIMAGE_IMPORT_DESCRIPTOR descriptor);
		void Reset();
		
	private:
		PDWORD descriptorLength;
		DWORD currentIndex;
		PIMAGE_IMPORT_DESCRIPTOR descriptor;
	};
}