#pragma once

#include "DirectoryBase.h"
namespace PeDecoder
{
	class ImportDescriptorIterator;
	// UNDONE: 
	class ImportDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Import>
	{
	public:
		typedef ImportDescriptorIterator iterator;
		// �����size��ʾ�����ṹ����thunk��name�Ĵ�С
		using DirectoryBase::DirectoryBase;
		iterator begin();
		iterator end();
	};

	

}  // namespace PeDecoder
