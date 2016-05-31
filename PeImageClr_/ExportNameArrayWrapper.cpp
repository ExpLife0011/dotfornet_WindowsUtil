#include "stdafx.h"
#include "ExportNameArrayWrapper.h"
#include "ExportNameWrapper.h"
namespace PeImageClr
{
	 ExportNameArrayWrapper::ExportNameArrayWrapper(List<ExportNameWrapper^>^ nameWrappers)
	{
		// ��֧��Э��ֻ��ת����
		names = gcnew List<IElementName^>();
		for each (auto var in nameWrappers)
		{
			names->Add(var);
		}
	}
	 System::Collections::Generic::IList<IElementName^>^ ExportNameArrayWrapper::GetElements()
	{
		return names;
	}
	 array<String^>^ ExportNameArrayWrapper::GetSortList()
	{
		return nullptr;
	}
}  // namespace PeImageClr
