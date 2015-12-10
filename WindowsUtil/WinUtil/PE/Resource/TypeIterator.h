#pragma once
#include "ResourceNameIterator.h"
namespace PE
{
	class ResourceDirectory;
	class TypeIterator:
		public IIterator<PIMAGE_RESOURCE_DIRECTORY_ENTRY>,
		public GetIterator<ResourceNameIterator, ResourceDirectory>,
		public IGetValue<PIMAGE_RESOURCE_DIRECTORY>
	{
		PIMAGE_RESOURCE_DIRECTORY_ENTRY firstTypeDirectoryEntry;
		PIMAGE_RESOURCE_DIRECTORY_ENTRY lastTypeDirectoryEntry;
		PIMAGE_RESOURCE_DIRECTORY_ENTRY currentTypeDirectoryEntry;
	public:

		TypeIterator(ResourceDirectory& resourceDirectory);

		~TypeIterator();

		// ͨ�� IIterator �̳�
		virtual PIMAGE_RESOURCE_DIRECTORY_ENTRY Current() override;
		virtual bool Next() override;
		virtual void Reset() override;

		// ͨ�� IGetValue �̳�
		virtual PIMAGE_RESOURCE_DIRECTORY GetValue() override;
	};
}
