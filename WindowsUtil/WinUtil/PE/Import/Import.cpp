#include "Import.h"
namespace PE
{
	LPSTR GetDescriptorName(PeDecoder & pe, PIMAGE_IMPORT_DESCRIPTOR descriptor)
	{
		return reinterpret_cast<LPSTR>(pe.GetRvaData(descriptor->Name));
	}

	PIMAGE_IMPORT_BY_NAME GetNameStruct(PeDecoder & pe, PIMAGE_THUNK_DATA32 thunk)
	{
		return reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(pe.GetRvaData(thunk->u1.AddressOfData));
	}
	PIMAGE_IMPORT_BY_NAME GetNameStruct(PeDecoder & pe, PIMAGE_THUNK_DATA64 thunk)
	{
		// FIX: 32λ���ڽض�
		return reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(pe.GetRvaData(thunk->u1.AddressOfData));
	}
	bool IsSnapByOrdinal(PIMAGE_THUNK_DATA32 thunk)
	{
		return IMAGE_SNAP_BY_ORDINAL32(thunk->u1.Ordinal);
	}
	bool IsSnapByOrdinal(PIMAGE_THUNK_DATA64 thunk)
	{
		return IMAGE_SNAP_BY_ORDINAL64(thunk->u1.Ordinal);
	}
	ULONGLONG GetOrdinal(PIMAGE_THUNK_DATA64 thunk)
	{
		return IMAGE_ORDINAL64(thunk->u1.Ordinal);
	}
	DWORD GetOrdinal(PIMAGE_THUNK_DATA32 thunk)
	{
		return IMAGE_ORDINAL32(thunk->u1.Ordinal);
	}
	PVOID GetProcImportThunkAddress(PeDecoder & pe, LPCSTR dllName, LPCSTR procName)
	{
		assert(procName && pe.IsMapped());
		auto idr = pe.GetImport()->CreateIterator();
		while (idr->Next())
		{
			auto currentDescriptor = idr->Current();
			if (dllName)
			{
				auto currentDllName = GetDescriptorName(pe, currentDescriptor);
				if (_stricmp(dllName, currentDllName) != 0)
				{
					continue;
				}
			}
			auto itr = idr->CreateIterator();
			while (itr->Next())
			{
				if (pe.HasNtHeader32())
				{
					auto currentThunk = itr->CurrentOriginalThunk32();
					if (!IsSnapByOrdinal(currentThunk))
					{
						auto currentProcName = GetNameStruct(pe, currentThunk);
						if (strcmp(reinterpret_cast<char*>(currentProcName->Name), procName))
						{
							continue;
						}
						return itr->CurrentThunk32();

					}
				}
				else
				{
					auto currentThunk = itr->CurrentOriginalThunk64();
					if (!IsSnapByOrdinal(currentThunk))
					{
						auto currentProcName = GetNameStruct(pe, currentThunk);
						if (strcmp(reinterpret_cast<char*>(currentProcName->Name), procName))
						{
							continue;
						}
						return itr->CurrentThunk64();

					}
				}
			}
		}
		return NULL;

	}
}  // namespace PE
