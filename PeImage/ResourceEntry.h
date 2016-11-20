#pragma once
#include <Windows.h>
namespace PeDecoder
{

	// Resource Directory (root) (resource ���ͷ���->RDE)
	//			|-> Resource Directory Entry ��ÿ�����ͷ�������->RD,����ǰ��Ľṹ��

	//						|-> Resource Directory (��Ԫ��ID����->RDE)
	//									|-> Resource Directory Entry ��Ԫ��ID�������->RD��

	//												|-> Resource Directory �����Է���->Data��
	//															|-> �������

	class ResourceDirectoryNode;
	class ResourceEntry
	{
	public:
		friend class ResourceEntryIterator;
		ResourceEntry(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY ptr);
		PIMAGE_RESOURCE_DIRECTORY_ENTRY GetPtr() const;
		bool NameIsString() const;
		PIMAGE_RESOURCE_DIR_STRING_U GetName() const;
		WORD GetID() const;

		PIMAGE_RESOURCE_DIRECTORY GetRoot() const;
		PIMAGE_RESOURCE_DIRECTORY GetChildDirectoryPtr() const;
		PIMAGE_RESOURCE_DATA_ENTRY GetDataEntryPtr()const;
		bool DataIsDirectory() const;
		ResourceDirectoryNode GetChildDirectory();

	protected:
		
		PIMAGE_RESOURCE_DIRECTORY root_;
		PIMAGE_RESOURCE_DIRECTORY_ENTRY ptr_;
	};


}  // namespace PeDecoder
