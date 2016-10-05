#pragma once
#include <Windows.h>
#include "DataDirectoryEntryType.h"
#include "DataSize.h"
#include "DataPtr.h"

namespace PeDecoder
{
	class NtHeader;

	// ע�������GetSize��һ����ӳ��ʵ��С
	class DataDirectoryEntries :
		public Detail::DataSize<PDWORD>,
		public Detail::DataPtr<PIMAGE_DATA_DIRECTORY>
	{
	public:
		typedef TDataPtr iterator;
		DataDirectoryEntries(TDataPtr ptr, TSizePtr sizePtr);
		DataDirectoryEntries(const NtHeader& nt);
		~DataDirectoryEntries() = default;
		bool IsValid() const;
		// indexԽ�緵��nullptr
		bool HasDirectory(DataDirectoryEntryType index);
		TDataPtr GetDirectoryEntry(DataDirectoryEntryType index);
		TDataPtr operator[](DataDirectoryEntryType index);
		iterator begin() const;
		iterator end() const;
		// ʵ������С���������С��һ����
		static constexpr TSizeType MaxSize();
	protected:
	};

}  // namespace PeDecoder
