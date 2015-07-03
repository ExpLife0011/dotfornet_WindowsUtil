#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <WinTrust.h>
namespace PE
{
	// PE������
	// TODO: ����Ŀ¼����ֻ����˵��뵼����\��Դ\�ض�λ\�ڵĶ�ȡ��
	class PeDecoder
	{
	public:

		PeDecoder(PVOID pe, bool isMapped);
		~PeDecoder();
		bool HasNtHeader32();
		bool IsPE();
		bool IsMapped();
		PVOID GetBase();
		PIMAGE_DOS_HEADER DosHeader();

		PIMAGE_NT_HEADERS32 NtHeader32();
		PIMAGE_NT_HEADERS64 NtHeader64();
		PIMAGE_ROM_HEADERS RomHeader();
		PIMAGE_SECTION_HEADER RvaToSection(DWORD rva);
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset);
		DWORD RvaToOffset(DWORD rva);
		DWORD OffsetToRva(DWORD fileOffset);
		PIMAGE_EXPORT_DIRECTORY GetImageExport(PDWORD* size = NULL);
		PIMAGE_IMPORT_DESCRIPTOR GetImageImport(PDWORD* size = NULL);
		PIMAGE_RESOURCE_DIRECTORY GetImageResource(PDWORD* size = NULL);
		PIMAGE_BASE_RELOCATION GetImageBasereloc(PDWORD* size = NULL);
		PVOID ImageIat(PDWORD* size = NULL); // ȡiatͷ, ����Ϊ32Ҳ����Ϊ64, ���ò��Ƕ���Ϣ,����ֱ�ӷ���ָ��


#pragma region �ⲿ��δ���reader
		PIMAGE_DEBUG_DIRECTORY ImageDebug(PDWORD* size = NULL);
		PIMAGE_RUNTIME_FUNCTION_ENTRY ImageException(PDWORD* size = NULL);
		PVOID ImageSecurity(PDWORD* size = NULL);
		PIMAGE_ARCHITECTURE_HEADER ImageArchitecture(PDWORD* size = NULL);
		PIMAGE_TLS_DIRECTORY64 ImageTls64(PDWORD* size = NULL);
		PIMAGE_TLS_DIRECTORY32 ImageTls32(PDWORD* size = NULL);
		PIMAGE_LOAD_CONFIG_DIRECTORY64 ImageLoadConfig64(PDWORD* size = NULL);
		PIMAGE_LOAD_CONFIG_DIRECTORY32 ImageLoadConfig32(PDWORD* size = NULL);
		PIMAGE_DELAYLOAD_DESCRIPTOR ImageDelayImport(PDWORD* size = NULL);
		PIMAGE_BOUND_IMPORT_DESCRIPTOR ImageBoundImport(PDWORD* size = NULL);
		PIMAGE_COR20_HEADER ImageComDescriptor(PDWORD* size = NULL);
#pragma endregion	
		

		PVOID GetRvaData(DWORD rva);
		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index);
		PIMAGE_SECTION_HEADER GetFirstSectionHeader();
		PWORD GetNumberOfSection();
	private:
		PVOID DirectoryEntryToData(DWORD index, PDWORD* size); // �ɸ�����Ҫ��ȡsizeָ��, sizeΪNULL��ȡֵ,����ΪNULLʱ���ı�sizeָ���ֵ
		PUINT8 base;
		PVOID ntHeader;
		PIMAGE_DATA_DIRECTORY imageDataDirectoryEntry;
		PDWORD imageDataDirectorySize;
		PIMAGE_SECTION_HEADER firstSectionHeader;
		PIMAGE_SECTION_HEADER lastSectionHeader;
		PDWORD sectionAlignment;
		PWORD sectionCount;
		bool isMapped;
		bool isPE;
		PWORD imageType; //IMAGE_NT_OPTIONAL_HDR32_MAGIC IMAGE_NT_OPTIONAL_HDR64_MAGIC IMAGE_ROM_OPTIONAL_HDR_MAGIC
		UINT AlignUp(UINT value, UINT alignment);
		void CheckImage();
		PVOID NtHeader();

	};
}