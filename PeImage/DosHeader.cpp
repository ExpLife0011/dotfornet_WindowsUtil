#include "stdafx.h"
#include "DosHeader.h"
#include "DosStub.h"
#include "PeImage.h"
namespace PeDecoder
{
	DosHeader::DosHeader(TDataPtr ptr) :
		DataPtr(ptr)
	{
		assert(ptr);
	}
	bool DosHeader::IsValid() const
	{
		return GetPtr()->e_magic == IMAGE_DOS_SIGNATURE;
	}
	const unique_ptr<DosStub>& DosHeader::GetDosStub()
	{
		assert(IsValid());
		if (!dosStub_)
		{
			// dosHeader��ntHeader֮��ķ�Χ
			auto ntPtr = reinterpret_cast<unsigned char*>(PeImage::GetNtHeaderPtr(GetPtr()));  // NtHeaderλ��
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
