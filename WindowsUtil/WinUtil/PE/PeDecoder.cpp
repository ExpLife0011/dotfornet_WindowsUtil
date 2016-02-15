#include "Common\Common.h"
namespace PE
{
#define ALIGN_UP(value, alignment) ((UINT)(value + alignment - 1)&~(alignment - 1))

	// �ж��ļ��Ƿ�ӳ�䣨ֵ���ⲿ���룩
	bool PeDecoder::IsMapped() const
	{
		return isMapped;
	}

	// ���ӵ�ָ��
	bool PeDecoder::Attach(PVOID base, bool isMapped)
	{
		if (base == NULL)
		{
			return false;
		}
		if (base == this->base)
		{
			return true;
		}
		
		// ��ʼ������
		isPE = false;
		Clear();
		isAttached = true;

		this->base = (PBYTE)(base);
		this->isMapped = isMapped;
		// �󶨽ṹ
		BindPtr();

		// ���pe��ʽ
		if (!GetDosHeader->VerifyDosSignature() || !GetNtHeader->VerifyNtSignature())
		{
			return false;
		}
		// ��ʼ��ntͷ
		if (!GetNtHeader->Init())
		{
			return false;
		}
		this->hasNtHeader32 = GetNtHeader->HasNtHeader32();
		isPE = true;
		return true;
	}

	// ���룬���ó�Ա
	void PeDecoder::Dettach()
	{
		base = NULL;
		Clear();
		isAttached = false;
	}

	// ���ӳٳ�ʼ���ṹ�󶨵�����
	void PeDecoder::BindPtr()
	{
		if (!isBinded)
		{
			isBinded = true;
			GetDosHeader.Bind(this);
			GetNtHeader.Bind(this);
			GetSection.Bind(this);
			GetReloc.Bind(this);
			GetExport.Bind(this);
			GetImport.Bind(this);
			GetResource.Bind(this);
			GetException.Bind(this);
			GetSecurity.Bind(this);
			GetDebug.Bind(this);
			GetArchitecture.Bind(this);
			GetGlobalptr.Bind(this);
			GetTls.Bind(this);
			GetLoadConfig.Bind(this);
			GetBoundImport.Bind(this);
			GetIat.Bind(this);
			GetDelayImport.Bind(this);
			GetComDescriptor.Bind(this);
		}
	}

	// ȡ��ַ
	PVOID PeDecoder::GetBase()
	{
		return this->base;
	}
	PeDecoder::PeDecoder()
	{
		isBinded = false;
		isAttached = false;
		Clear();
	}
	// ����
	void PeDecoder::Clear()
	{
		GetDosHeader.Reset();
		GetNtHeader.Reset();
		GetSection.Reset();
		GetReloc.Reset();
		GetExport.Reset();
		GetImport.Reset();
		GetResource.Reset();
		GetException.Reset();
		GetSecurity.Reset();
		GetDebug.Reset();
		GetArchitecture.Reset();
		GetGlobalptr.Reset();
		GetTls.Reset();
		GetLoadConfig.Reset();
		GetBoundImport.Reset();
		GetIat.Reset();
		GetDelayImport.Reset();
		GetComDescriptor.Reset();
	}
	// �ж��Ƿ�Ϊ32λ���򣬺�����һ�����
	bool PeDecoder::HasNtHeader32() const
	{
		return hasNtHeader32;
	}
	// �ж��Ƿ���PE�ļ�
	bool PeDecoder::IsPE() const
	{
		return isPE;
	}
	// �ж��Ƿ񸽼ӳɹ�
	bool PeDecoder::IsAttached() const
	{
		return isAttached;
	}
	// ���ƫ���ҽڵ�ַ
	PIMAGE_SECTION_HEADER PeDecoder::RvaToSection(DWORD rva)
	{
		auto currentSection = GetSection->firstSectionHeader;
		while (currentSection < GetSection->lastSectionHeader)
		{
			if (rva < currentSection->VirtualAddress +
				ALIGN_UP((UINT)(currentSection->Misc.VirtualSize), (UINT)(*GetSection->sectionAlignment)))
			{
				return rva < currentSection->VirtualAddress ? NULL : currentSection;
			}
			currentSection++;
		}
		return NULL;
	}
	// �ļ�ƫ���ҽڵ�ַ
	PIMAGE_SECTION_HEADER PeDecoder::OffsetToSection(DWORD fileOffset)
	{
		auto currentSection = GetSection->firstSectionHeader;
		while (currentSection < GetSection->lastSectionHeader)
		{
			if (fileOffset < currentSection->PointerToRawData + currentSection->SizeOfRawData)
			{
				return fileOffset < currentSection->PointerToRawData ? NULL : currentSection;
			}
			currentSection++;
		}
		return NULL;
	}
	// ���ƫ��ת���ļ�ƫ��
	DWORD PeDecoder::RvaToOffset(DWORD rva)
	{
		if (!rva)
		{
			return 0;
		}
		IMAGE_SECTION_HEADER *section = RvaToSection(rva);
		if (section == NULL)
		{
			return rva;
		}
		return rva - section->VirtualAddress + section->PointerToRawData;
	}
	// �ļ�ƫ��ת�����ƫ��
	DWORD PeDecoder::OffsetToRva(DWORD fileOffset)
	{
		if (fileOffset)
		{
			IMAGE_SECTION_HEADER *section = OffsetToSection(fileOffset);
			if (section != NULL)
			{
				return fileOffset - section->PointerToRawData + section->VirtualAddress;
			}
		}
		return 0;
	}
	// ȡ�����ƫ��ָ�������
	PVOID PeDecoder::GetRvaData(DWORD rva)
	{
		return base + (isMapped ? rva : RvaToOffset(rva));
	}
	

	// ͨ��ID��ȡDataDirectoryEntry��ַ��ʧ�ܷ���NULL
	PIMAGE_DATA_DIRECTORY PeDecoder::GetDataDirectory(DWORD index)
	{
		if (*GetNtHeader->imageDataDirectorySize > index && IMAGE_NUMBEROF_DIRECTORY_ENTRIES > index)
		{
			return &GetNtHeader->imageDataDirectoryEntry[index];
		}
		return NULL;
	}
	// ȡ��DataDirectoryEntryָ������ݵ�ַ
	PVOID PeDecoder::DirectoryEntryToData(DWORD index, PDWORD* size)
	{
		auto dir = GetDataDirectory(index);
		if (!dir || dir->VirtualAddress == NULL)
		{
			return NULL;
		}
		if (size)
		{
			*size = &dir->Size;
		}
		return GetRvaData(dir->VirtualAddress);
	}
}  // namespace PE
