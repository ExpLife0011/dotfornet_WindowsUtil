#pragma once
namespace PeImageClr
{	
	using namespace System;
	using namespace System::Collections::Generic;
	// ������������
	public interface class IPropertiesFilter
	{
		List<String^>^ GetHidePropList();
	};
}  // namespace PeImageClr
