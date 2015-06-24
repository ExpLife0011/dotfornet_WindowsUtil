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
		void Reset();
	private:
		PDWORD descriptorLength;
		DWORD currentIndex;
		PIMAGE_IMPORT_DESCRIPTOR descriptor;
	};
}