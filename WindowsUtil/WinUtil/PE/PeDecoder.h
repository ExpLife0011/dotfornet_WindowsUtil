#pragma once
#include <cassert>
#include <Windows.h>
#include <WinBase.h>
#include <WinTrust.h>
#include <delayimp.h>
#include "PeDecoder.h"
#pragma region ��Ԫ�õ�һЩԤ����
namespace Process
{
	namespace Hook
	{
		PVOID HookEat(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc, PDWORD oldFuncRva);
		PVOID HookIat(LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress);
	}
}
namespace PE
{
	class PeDecoder;
	namespace Import
	{
		class ImportThunkReader;
		PVOID GetProcImportThunkAddress(PeDecoder& pe, LPCSTR dllName, LPCSTR procName);
	}
	namespace DelayLoad
	{
		PVOID GetDelayLoadAddressTableAddress(PeDecoder& pe, LPCSTR dllName, LPCSTR procName);
	}
	namespace Section
	{
		class SectionReader;
	}
	namespace Export
	{
		FARPROC GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName));
		PDWORD GetProcExportFuncTableAddress(PeDecoder& pe, LPCSTR lpProcName);
	}
}
#pragma endregion
namespace PE
{
#define ALIGN_UP(value, alignment) ((UINT)(value + alignment - 1)&~(alignment - 1))
	
	// PE������, ������������س�����ļ�
	// TODO: ����Ŀ¼����ֻ����˵��뵼����\��Դ\�ض�λ\�ڵĶ�ȡ��
	class PeDecoder
	{
	public:
		friend class Section::SectionReader;
		friend class Import::ImportThunkReader;
		friend PVOID DelayLoad::GetDelayLoadAddressTableAddress(PeDecoder& pe, LPCSTR dllName, LPCSTR procName);
		friend PVOID Import::GetProcImportThunkAddress(PeDecoder& pe, LPCSTR dllName, LPCSTR procName);
		friend PVOID Process::Hook::HookEat(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc, PDWORD oldFuncRva);
		friend PVOID Process::Hook::HookIat(LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress);
		friend FARPROC Export::GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName));
		friend PDWORD Export::GetProcExportFuncTableAddress(PeDecoder& pe, LPCSTR lpProcName);

		PeDecoder()=default;
		~PeDecoder() = default;
		PeDecoder(PeDecoder& pe)=delete;
		bool LoadPEImage(PVOID base, bool isMapped);
		PVOID GetBase();
		bool IsMapped();
		PIMAGE_DOS_HEADER DosHeader();
		PIMAGE_NT_HEADERS32 NtHeader32();
		PIMAGE_NT_HEADERS64 NtHeader64();
		bool HasNtHeader32();

		PIMAGE_SECTION_HEADER RvaToSection(DWORD rva);
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset);
		DWORD RvaToOffset(DWORD rva);
		DWORD OffsetToRva(DWORD fileOffset);

		PIMAGE_EXPORT_DIRECTORY GetImageExport(PDWORD* size = NULL);
		PIMAGE_IMPORT_DESCRIPTOR GetImageImport(PDWORD* size = NULL);
		PIMAGE_RESOURCE_DIRECTORY GetImageResource(PDWORD* size = NULL);
		PIMAGE_BASE_RELOCATION GetImageBasereloc(PDWORD* size = NULL);
		PVOID GetImageIat(PDWORD* size = NULL); // ȡiatͷ, ����Ϊ32Ҳ����Ϊ64, ���ò��Ƕ���Ϣ,����ֱ�ӷ���ָ��
		/*PIMAGE_DELAYLOAD_DESCRIPTOR*/PImgDelayDescr GetImageDelayImport(PDWORD* size = NULL);


#pragma region �ⲿ��δ���reader
		PIMAGE_DEBUG_DIRECTORY GetImageDebug(PDWORD* size = NULL);
		PIMAGE_RUNTIME_FUNCTION_ENTRY GetImageException(PDWORD* size = NULL);
		PVOID GetImageSecurity(PDWORD* size = NULL);
		PIMAGE_ARCHITECTURE_HEADER GetImageArchitecture(PDWORD* size = NULL);
		PIMAGE_TLS_DIRECTORY64 GetImageTls64(PDWORD* size = NULL);
		PIMAGE_TLS_DIRECTORY32 GetImageTls32(PDWORD* size = NULL);
		PIMAGE_LOAD_CONFIG_DIRECTORY64 GetImageLoadConfig64(PDWORD* size = NULL);
		PIMAGE_LOAD_CONFIG_DIRECTORY32 GetImageLoadConfig32(PDWORD* size = NULL);
		PIMAGE_BOUND_IMPORT_DESCRIPTOR GetImageBoundImport(PDWORD* size = NULL);
		PIMAGE_COR20_HEADER GetImageComDescriptor(PDWORD* size = NULL);
#pragma endregion	
		

		PVOID GetRvaData(DWORD rva);
		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index);
	private:
		
		PBYTE base;
		PIMAGE_DOS_HEADER dosHeader;
		PIMAGE_NT_HEADERS32 ntHeader;
		
		bool isMapped;
		bool isPE;
		bool hasNtHeader32;
		PWORD imageType; //IMAGE_NT_OPTIONAL_HDR32_MAGIC IMAGE_NT_OPTIONAL_HDR64_MAGIC IMAGE_ROM_OPTIONAL_HDR_MAGIC
		PVOID DirectoryEntryToData(DWORD index, PDWORD* size); // �ɸ�����Ҫ��ȡsizeָ��, sizeΪNULL��ȡֵ,����ΪNULLʱ���ı�sizeָ���ֵ
		
		PIMAGE_DATA_DIRECTORY imageDataDirectoryEntry;
		PDWORD imageDataDirectorySize;
		PIMAGE_SECTION_HEADER firstSectionHeader;
		PIMAGE_SECTION_HEADER lastSectionHeader;
		PDWORD sectionAlignment;
		PWORD sectionCount;
	};

}