#pragma once
#include "PeImageFwd.h"
#include "DirectoryBase.h"
namespace PeDecoder
{
	// UNDONE: 
	class ImportDirectory :
		public Detail::DirectoryBase<DataDirectoryEntryType::Import>
	{
	public:
		typedef ImportDirectoryIterator iterator;
		// �����size��ʾ�����ṹ����thunk��name�Ĵ�С
		ImportDirectory(PeImage& pe, TDataPtr ptr, TSizePtr sizePtr);

		~ImportDirectory() = default;
		iterator begin();
		iterator end();
	};

	

}  // namespace PeDecoder
