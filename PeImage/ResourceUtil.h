#pragma once
namespace PeDecoder
{
	DWORD GetNumberOfEntries(PIMAGE_RESOURCE_DIRECTORY directory);

	PIMAGE_RESOURCE_DIR_STRING_U LocateEntryName(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);

	PIMAGE_RESOURCE_DIRECTORY_ENTRY LocateFirstEntry(PIMAGE_RESOURCE_DIRECTORY res);

	PIMAGE_RESOURCE_DIRECTORY LocateResourceDirectory(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);

	PIMAGE_RESOURCE_DATA_ENTRY LocateResourceDataEntry(PIMAGE_RESOURCE_DIRECTORY root, PIMAGE_RESOURCE_DIRECTORY_ENTRY entry);
}  // namespace PeDecoder
