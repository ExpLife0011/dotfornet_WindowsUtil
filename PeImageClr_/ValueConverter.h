#pragma once
namespace PeImageClr
{
	using namespace System;
	using namespace System::Globalization;
	using namespace System::Collections;
	using namespace System::ComponentModel;
	using namespace System::Reflection;
	using namespace System::Runtime::InteropServices;
	// FIX: ��64λ������ļ�ʱ��ƫ���ֳ�������
	public ref class ValueConverter :public TypeConverter
	{
		MethodInfo^ parseMethod = nullptr;
		String^ format;
	public:
		virtual bool CanConvertFrom(ITypeDescriptorContext^ context, Type^ sourceType) override;

		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value, Type^ destinationType) override;
		// intptr ��ת��
		virtual  Object^ ConvertFrom(ITypeDescriptorContext^ context, CultureInfo^ culture, Object^ value) override;
	};
}  // namespace PeImageClr
