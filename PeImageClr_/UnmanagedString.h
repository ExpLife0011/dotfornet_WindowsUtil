#pragma once
#include "ShowPropertiesConverter.h"
#include "StructOffset.h"
#include "IDescription.h"
#include "UnmanagedValueSort.h"
#include "UnmanagedMemory.h"
namespace PeImageClr
{
	using namespace System;

	[TypeConverter(ShowPropertiesConverter::typeid)]
	public 	ref class UnmanagedString :
		public StructOffset,
		public IDescription
	{
		static array<String^>^ sortList;
		int strLen;
	public:
		UnmanagedString(IntPtr addr, IntPtr base, int strLen);
		virtual String ^ GetDescription();

		virtual array<String^>^ GetSortList();
		property String^ String
		{
			System::String^ get()
			{
				if (strLen == 0)
				{
					auto result = Marshal::PtrToStringAnsi(addr);
					strLen = System::Text::Encoding::ASCII->GetByteCount(result); // �����ַ�������
					return result;
				}
				// FIX: �����ַ����м���\0ʱ��Ѻ����Ҳ������������ֱ������Ƴ��ȣ������str��һ����0��β��
				return Marshal::PtrToStringAnsi(addr, strLen)->TrimEnd(' ', '\0');
			}
			void set(System::String^ value)
			{
				int writeCount = System::Text::Encoding::ASCII->GetByteCount(value);

				if (strLen == 0)
				{
					strLen = System::Text::Encoding::ASCII->GetByteCount(Marshal::PtrToStringAnsi(addr));
				}
				if (writeCount <= strLen)
				{
					auto strBytes = System::Text::Encoding::ASCII->GetBytes(value);
					UnmanagedMemory::Copy(strBytes, 0, addr, strBytes->Length);
				}
			}
		};
	};

}  // namespace PeImageClr
