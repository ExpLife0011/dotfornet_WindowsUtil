#pragma once
#include "BaseRelocationIterator.h"
namespace PE
{
	// �ض�λ���װ
	class RelocDirectory :
		public DataDirectory<RelocDirectory, PIMAGE_BASE_RELOCATION, IMAGE_DIRECTORY_ENTRY_BASERELOC>,
		public GetIterator<BaseRelocationIterator, RelocDirectory>
	{
	public:
		friend GetIteratorBase::Iterator;
		explicit RelocDirectory(PeDecoder* pe);

		~RelocDirectory();


	};

}  // namespace PE
