#pragma once
#include <Windows.h>
#include "DataDirectoryEntryType.h"
namespace PeDecoder
{
	class NtHeader;
	// ע�������GetSize��һ����ӳ��ʵ��С
	class DataDirectoryEntries
	{
	public:
		DataDirectoryEntries(PIMAGE_DATA_DIRECTORY ptr, PDWORD sizePtr);
		DataDirectoryEntries(const NtHeader& nt);
		bool IsValid() const;
		// ʵ������С���������С��һ����
		static DWORD MaxSize();
		PIMAGE_DATA_DIRECTORY begin() const;
		PIMAGE_DATA_DIRECTORY end() const;
		DWORD GetSize() const;

		bool HasDirectory(DataDirectoryEntryType index) const;
		PIMAGE_DATA_DIRECTORY GetDirectoryEntry(DataDirectoryEntryType index) const;
		PIMAGE_DATA_DIRECTORY operator[](DataDirectoryEntryType index) const;
	protected:
		PIMAGE_DATA_DIRECTORY GetPtr() const;
		void Set(PIMAGE_DATA_DIRECTORY data, PDWORD size);
		PDWORD sizePtr_;
		PIMAGE_DATA_DIRECTORY ptr_;
	};

}  // namespace PeDecoder
