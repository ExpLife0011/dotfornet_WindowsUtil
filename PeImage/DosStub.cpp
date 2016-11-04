#include "stdafx.h"
#include "DosStub.h"
#include "DosHeader.h"
#include "NtHeader.h"

namespace PeDecoder
{

	DosStub::DosStub(const DosHeader& dos, const NtHeader& nt) :
		size_(0),
		ptr_(nullptr)
	{
		auto ntPtr = nt.GetPos();  // NtHeaderλ��
		auto ptr = reinterpret_cast<unsigned char*>(dos.RawPtr() + 1); // dosStubӦ���ڵ�λ��
		auto size = ntPtr - ptr; // ʵ�ʴ�С��NtHeader��DosHeader�ص�ʱ������Ϊ�޸ģ�û��DosStub
		if (size > 0)
		{
			ptr_ = ptr;
			size_ = size;
		}
	}
	DWORD DosStub::GetSize() const
	{
		return size_;
	}

	DosStub::iterator DosStub::begin() const
	{
		return ptr_;
	}

	DosStub::iterator DosStub::end() const
	{
		return ptr_ + GetSize();
	}

}  // namespace PeDecoder
