#pragma once
#include "..\PeDecoder.h"
namespace PE
{
	namespace Import
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
			int currentIndex;
			PIMAGE_IMPORT_DESCRIPTOR descriptor;
		};

	}
}