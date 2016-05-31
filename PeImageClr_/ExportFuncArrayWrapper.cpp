#include "stdafx.h"
#include "ExportFuncArrayWrapper.h"
#include "PeImage.h"
#include "ExportFuncWrapper.h"
#include "ExportNameWrapper.h"
namespace PeImageClr
{
	void ExportFuncArrayWrapper::InitArrayList()
	{
		list = gcnew System::Collections::Generic::List<IElementName^>();

		// ��func ȡindex��ֵ������name list��name
		// ��name ord��ȡ���±�func��list��nameдֵ
		//��� ExportFuncWrapper ������Ҫ������ord
		auto funcTable = GetUnmanagedStruct().GetFunctionsPtr();
		auto numberOfFunctions = *GetUnmanagedStruct().GetNumberOfFunctionsPtr();
		for (int i = 0; i < numberOfFunctions; i++)
		{
			list->Add(gcnew ExportFuncWrapper(i, IntPtr(&funcTable[i]), pe));
		}
		auto numberOfNames = *GetUnmanagedStruct().GetNumberOfNamesPtr();
		auto nameTable = GetUnmanagedStruct().GetNamesPtr();
		auto nameOrdinalTable = GetUnmanagedStruct().GetNameOrdinalsPtr();
		for (int i = 0; i < numberOfNames; i++)
		{
			auto tmpNameRva = &nameTable[i];
			auto tmpOrdinal = &nameOrdinalTable[i];
			auto tmpFunc = safe_cast<ExportFuncWrapper^>(list[*tmpOrdinal]);
			tmpFunc->AddName(gcnew ExportNameWrapper(IntPtr(tmpNameRva), IntPtr(tmpOrdinal), pe));
		}


	}
	ExportFuncArrayWrapper::PeStructWrapperType & ExportFuncArrayWrapper::GetUnmanagedStruct()
	{
		return *pe->GetPeDecoder().GetExportDirectory();
	}
	array<String^>^ ExportFuncArrayWrapper::GetSortList()
	{
		return nullptr;
	}
	System::Collections::Generic::IList<IElementName^>^ ExportFuncArrayWrapper::GetElements()
	{
		if (list == nullptr)
		{
			InitArrayList();
		}
		return list;
	}
	ExportFuncArrayWrapper::ExportFuncArrayWrapper(PeImage ^ pe) :PeStructWrapperBase(pe)
	{
		SetDescription(IntPtr::Zero, pe->BaseAddress, 0);
	}
	String ^ ExportFuncArrayWrapper::GetDescription()
	{
		if (GetElements() == nullptr)
		{
			return String::Empty;
		}
		return String::Format("(Count: {0})", GetElements()->Count);
	}
}  // namespace PeImageClr
