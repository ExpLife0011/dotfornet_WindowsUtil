#include "stdafx.h"
#include "DosStub.h"
#include "DosHeader.h"
#include "NtHeader.h"

namespace PeDecoder
{

	DosStub::DosStub(void* ptr, DWORD size):
		DataPtr(reinterpret_cast<unsigned char*>(ptr)),
		size_(size)
	{
	}
	DosStub::DosStub(const IPeImage & pe) :
		DosStub(nullptr, 0)
	{
		auto ntPtr = reinterpret_cast<unsigned char*>(pe.GetNtHeader()->GetPtr());  // NtHeaderλ��
		auto ptr = reinterpret_cast<unsigned char*>(pe.GetDosHeader()->GetPtr() + 1); // dosStubӦ���ڵ�λ��
		auto size = ntPtr - ptr; // ʵ�ʴ�С��NtHeader��DosHeader�ص�ʱ������Ϊ�޸ģ�û��DosStub
		if (size > 0)
		{
			SetPtr(ptr);
			size_ = size;
		}
	}
	DWORD DosStub::GetSize() const
	{
		return size_;
	}

	DosStub::iterator DosStub::begin() const
	{
		return GetPtr();
	}

	DosStub::iterator DosStub::end() const
	{
		return GetPtr() + GetSize();
	}

}  // namespace PeDecoder
