#pragma once
namespace PeImageClr
{
	using namespace System;
	// ������ȡ������ȡ������
	interface class IDescription
	{
		String^ GetDescription();
		array<String^>^ GetSortList();
	};
}  // namespace PeImageClr
