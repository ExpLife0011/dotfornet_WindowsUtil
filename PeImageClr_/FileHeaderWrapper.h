#pragma once
#include <Windows.h>
#include <WinBase.h>
#include "PeStructWrapper.h"
#include "UnmanagedValue.h"
#include "UnmanagedEnum.h"
#include "MachineType.h"
#include "UnmanagedDateTimeValue.h"
#include "CharacteristicsType.h"
namespace PeImageClr
{
	using namespace System::ComponentModel;

	// FIX: ֱ������ȡֵ�ò���ƫ�Ƶ�ַ, �뵽���������滻�������ȡ��ͷָ�����Լ�����ƫ����Ҫ�˹��ɱ�̫��
	// 
	/*[StructLayout(LayoutKind::Sequential, Size = sizeof(IMAGE_FILE_HEADER))]
	public value struct FileHeader
	{
	MachineType    Machine;
	WORD    NumberOfSections;
	DWORD   TimeDateStamp;
	DWORD   PointerToSymbolTable;
	DWORD   NumberOfSymbols;
	WORD    SizeOfOptionalHeader;
	CharacteristicsType    Characteristics;
	};*/

	[TypeConverter(ShowPropertiesConverter::typeid)]
	public ref class FileHeaderWrapper :
		public PeStructWrapper<IMAGE_FILE_HEADER>
	{
		static array<String^>^ sortList;

	internal:
		// ͨ�� PeStructWrapper �̳�
		virtual PeStructWrapperType & GetUnmanagedStruct() override;

	public:

		FileHeaderWrapper(PeImage^ pe);
		virtual array<String^>^ GetSortList() override;
		property UnmanagedEnum<MachineType>^ Machine
		{
			UnmanagedEnum<MachineType>^ get()
			{
				return gcnew UnmanagedEnum<MachineType>(IntPtr(&GetUnmanagedStruct().Machine), GetPeBase());
			}
		};

		property UnmanagedValue<WORD>^    NumberOfSections
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().NumberOfSections), GetPeBase());
			}
		};
		property UnmanagedDateTimeValue<DWORD>^   TimeDateStamp
		{
			UnmanagedDateTimeValue<DWORD>^ get()
			{
				return gcnew UnmanagedDateTimeValue<DWORD>(IntPtr(&GetUnmanagedStruct().TimeDateStamp), GetPeBase());
			}
		};
		property UnmanagedValue<DWORD>^   PointerToSymbolTable
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().PointerToSymbolTable), GetPeBase());
			}
		};
		property UnmanagedValue<DWORD>^   NumberOfSymbols
		{
			UnmanagedValue<DWORD>^ get()
			{
				return gcnew UnmanagedValue<DWORD>(IntPtr(&GetUnmanagedStruct().NumberOfSymbols), GetPeBase());
			}
		};
		property UnmanagedValue<WORD>^    SizeOfOptionalHeader
		{
			UnmanagedValue<WORD>^ get()
			{
				return gcnew UnmanagedValue<WORD>(IntPtr(&GetUnmanagedStruct().SizeOfOptionalHeader), GetPeBase());
			}
		};


		property UnmanagedEnum<CharacteristicsType>^ Characteristics
		{
			UnmanagedEnum<CharacteristicsType>^ get()
			{
				return gcnew UnmanagedEnum<CharacteristicsType>(IntPtr(&GetUnmanagedStruct().Characteristics), GetPeBase());
			}
		};
	};
}  // namespace PeImageClr
