#include "ImportDescriptorReader.h"
namespace PE
{
	namespace Import
	{
		// �����Descriptor�ṹ��ȡ��
		ImportDescriptorReader::ImportDescriptorReader(PeDecoder& pe)
		{
			descriptorLength = NULL;
			descriptor = pe.GetImageImport(&descriptorLength);
			Reset();
		}
		ImportDescriptorReader::~ImportDescriptorReader() {}
		bool ImportDescriptorReader::Next()
		{
			if (descriptorLength)
			{
				if (++currentIndex < *descriptorLength)
				{
					auto checkResult = descriptor[currentIndex];
					return !(checkResult.Name == NULL || checkResult.FirstThunk == NULL);
				}
			}
			return false;
		}
		PIMAGE_IMPORT_DESCRIPTOR ImportDescriptorReader::Current()
		{
			return currentIndex == -1 ?NULL:&descriptor[currentIndex];
		}

		void ImportDescriptorReader::Reset()
		{
			currentIndex = -1;
		}

	}
}