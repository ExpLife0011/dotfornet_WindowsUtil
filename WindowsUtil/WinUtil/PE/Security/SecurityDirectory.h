#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class SecurityDirectory :
		public DataDirectory<_PeDecoder, PVOID, IMAGE_DIRECTORY_ENTRY_SECURITY>
	{
	protected:
		 PVOID DirectoryEntryToData() 
		{
			if (peDecoder.IsMapped()) // ����ӳ�䵽�ڴ�
			{
				return NULL;
			}
			if (!dataDirectory || dataDirectory->VirtualAddress == NULL)
			{
				return NULL;
			}
			return reinterpret_cast<PBYTE>(peDecoder.GetBase()) + dataDirectory->VirtualAddress;
		}
	public:
		friend DataDirectoryBase;
		SecurityDirectory(_PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}

		~SecurityDirectory()
		{
		}
	};

}