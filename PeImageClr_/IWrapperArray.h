#pragma once
namespace PeImageClr
{
	interface class IElementName;
	public interface class IWrapperArray
	{
		// ��Ա���ͱ���ΪIElementName��cli��֪����ô������Э��
		System::Collections::Generic::IList<IElementName^>^ GetElements();
	};
}  // namespace PeImageClr
