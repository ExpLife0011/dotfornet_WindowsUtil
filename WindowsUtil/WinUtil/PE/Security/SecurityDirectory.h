#pragma once
#include "../Common/Common.h"
namespace PE
{
	template<typename _PeDecoder>
	class SecurityDirectory :
		public DataDirectory<_PeDecoder, PVOID, IMAGE_DIRECTORY_ENTRY_SECURITY>
	{
	protected:
		virtual PVOID DirectoryEntryToData() override
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

		SecurityDirectory(_PeDecoder& pe) :DataDirectory<_PeDecoder, PVOID, IMAGE_DIRECTORY_ENTRY_SECURITY>(pe)
		{
		}

		~SecurityDirectory()
		{
		}
	};

}