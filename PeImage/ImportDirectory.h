#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	class ImportDirectoryIterator;
	// UNDONE: 
	class ImportDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Import>
	{
	public:
		typedef ImportDirectoryIterator iterator;
		// �����size��ʾ�����ṹ����thunk��name�Ĵ�С
		using DirectoryBase::DirectoryBase;
		iterator begin();
		iterator end();
	};

	

}  // namespace PeDecoder
