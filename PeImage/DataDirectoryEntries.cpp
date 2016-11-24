#include "stdafx.h"
#include "DataDirectoryEntries.h"

#include "PeImage.h"
#include "NtHeader.h"

namespace PeDecoder
{
	DataDirectoryEntries::DataDirectoryEntries(const PeImage & pe)
	{
		auto& nt = *pe.GetNtHeader();
		ptr_ = nt.GetDataDirectory();
		size_ = nt.GetDataDirectorySize();
	}

	bool DataDirectoryEntries::IsValid() const
	{
		return GetSize() <= IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
	}

	bool DataDirectoryEntries::HasDirectory(DataDirectoryEntryType index) const
	{
		return GetDirectoryEntry(index) != nullptr;
	}
	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::GetDirectoryEntry(DataDirectoryEntryType index) const
	{
		assert(IsValid());
		if (index < MaxSize() && index < GetSize())
		{
			return &GetPtr()[index];
		}
		// �����޸ĵĽṹ����Ԫ�ز��룬����null��ʾ������ṹ
		return nullptr;
	}
	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::operator[](DataDirectoryEntryType index) const
	{
		return GetDirectoryEntry(index);
	}

	DataDirectoryEntries::~DataDirectoryEntries()
	{
		ptr_ = nullptr;
	}


	DWORD DataDirectoryEntries::MaxSize()
	{
		return _DataDirectoryEntryTypeEnd + 1;
	}

	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::begin() const
	{
		assert(IsValid());
		return GetPtr();
	}

	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::end() const
	{
		assert(IsValid());
		auto size = GetSize();
		size = size > MaxSize() ? MaxSize() : size;
		return GetPtr() + size;
	}

	DWORD DataDirectoryEntries::GetSize() const
	{
		return size_;
	}

	PIMAGE_DATA_DIRECTORY DataDirectoryEntries::GetPtr() const
	{
		assert(ptr_);
		return ptr_;
	}


}  // namespace PeDecoder
