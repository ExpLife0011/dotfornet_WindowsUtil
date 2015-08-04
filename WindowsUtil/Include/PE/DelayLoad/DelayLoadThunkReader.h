#pragma once
#include <cassert>
#include "DelayLoadDescriptorReader.h"

namespace PE
{
	namespace DelayLoad
	{
		// װ��2015��winnt��PIMAGE_DELAYLOAD_DESCRIPTOR�ṹ��ôû�ˣ�����PImgDelayDescr
		class DelayLoadThunkReader
		{
			PVOID importAddressTable;
			PVOID importNameTable;
			PImgDelayDescr descriptor;
			PVOID currentImportAddressTable;
			PVOID currentImportNameTable;
		public:
			DelayLoadThunkReader(PeDecoder& pe, PImgDelayDescr descriptor);
			DelayLoadThunkReader();
			~DelayLoadThunkReader();
			void Init(PeDecoder& pe, PImgDelayDescr descriptor);
			PVOID CurrentNameTable();
			PVOID CurrentAddressTable();
			bool Next();
			void Reset();
		};

	}
}