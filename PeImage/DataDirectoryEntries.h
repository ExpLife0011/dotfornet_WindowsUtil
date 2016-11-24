#pragma once
#include <Windows.h>
#include "DataDirectoryEntryType.h"
namespace PeDecoder
{
	class PeImage;
	// ע�������GetSize��һ����ӳ��ʵ��С
	class DataDirectoryEntries
	{
	public:
		explicit DataDirectoryEntries(const PeImage& pe);
		bool IsValid() const;
		// ʵ������С���������С��һ����
		static DWORD MaxSize();
		PIMAGE_DATA_DIRECTORY begin() const;
		PIMAGE_DATA_DIRECTORY end() const;
		DWORD GetSize() const;

		bool HasDirectory(DataDirectoryEntryType index) const;
		PIMAGE_DATA_DIRECTORY GetDirectoryEntry(DataDirectoryEntryType index) const;
		PIMAGE_DATA_DIRECTORY operator[](DataDirectoryEntryType index) const;
		virtual ~DataDirectoryEntries();
	protected:
		PIMAGE_DATA_DIRECTORY GetPtr() const;
		DWORD size_;
		PIMAGE_DATA_DIRECTORY ptr_;
	};

}  // namespace PeDecoder
