#include "stdafx.h"
#include "DosHeader.h"
namespace PeDecoder
{
	bool DosHeader::Valid(const TDataPtr ptr)
	{
		assert(ptr);
		return ptr->e_magic == IMAGE_DOS_SIGNATURE;
	}
	void * DosHeader::GetNtHeaderPtr(const PIMAGE_DOS_HEADER dosHeader)
	{
		return reinterpret_cast<unsigned char*>(dosHeader) + dosHeader->e_lfanew;
	}
	const unique_ptr<DosStub>& DosHeader::GetDosStub()
	{
		assert(Valid(GetPtr()));
		if (!dosStub_)
		{
			// dosHeader��ntHeader֮��ķ�Χ
			auto ntPtr = reinterpret_cast<unsigned char*>(GetNtHeaderPtr(GetPtr()));  // NtHeaderλ��
			auto ptr = reinterpret_cast<unsigned char*>(GetPtr() + 1); // dosStubӦ���ڵ�λ��
			auto size = ntPtr - ptr; // ʵ�ʴ�С��NtHeader��DosHeader�ص�ʱ������Ϊ�޸ģ�û��DosStub
			if (size > 0)
			{
				dosStub_ = make_unique<DosStub>(ptr, size);
			}
		}
		return dosStub_;
	}
}  // namespace PeDecoder
