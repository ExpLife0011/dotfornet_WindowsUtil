#pragma once
#include "IWrapperArray.h"
#include "PeStructWrapper.h"
#include "PeStructArrayConverter.h"
namespace PeImageClr
{
	// �����������飬 ���������������������������
	[TypeConverter(PeStructArrayConverter::typeid)]
	public ref class ExportFuncArrayWrapper :
		public IWrapperArray,
		public PeStructWrapper<PeDecoder::ExportDirectory>
	{
		System::Collections::Generic::IList<IElementName^>^ list;
		void InitArrayList();
	public:
		virtual PeStructWrapperType & GetUnmanagedStruct() override;
		virtual array<String^>^ GetSortList() override;
		virtual System::Collections::Generic::IList<IElementName^>^ GetElements() override;

		ExportFuncArrayWrapper(PeImage^ pe);
		virtual String ^ GetDescription() override;
	};
}  // namespace PeImageClr
