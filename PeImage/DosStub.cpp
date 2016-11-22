#include "stdafx.h"
#include "DosStub.h"
#include "PeImage.h"
#include "DosHeader.h"
#include "NtHeader.h"

namespace PeDecoder
{

	DosStub::DosStub(const PeImage& pe) :
		size_(0),
		ptr_(nullptr)
	{
		auto& dos = *pe.GetDosHeader();
		auto& nt = *pe.GetNtHeader();
		auto ntPtr = nt.RawPtr();  // NtHeaderλ��
		auto ptr = reinterpret_cast<unsigned char*>(dos.RawPtr() + 1); // dosStubӦ���ڵ�λ��
		auto size = ntPtr - ptr; // ʵ�ʴ�С��NtHeader��DosHeader�ص�ʱ������Ϊ�޸ģ�û��DosStub
		if (size > 0)
		{
			ptr_ = ptr;
			size_ = size;
		}
	}
	bool DosStub::IsExist() const
	{
		return GetSize() != 0;
	}
	DWORD DosStub::GetSize() const
	{
		return size_;
	}
	DosStub::operator bool() const
	{
		return IsExist();
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
