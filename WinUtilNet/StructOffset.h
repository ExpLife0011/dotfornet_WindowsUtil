#pragma once
namespace NAMESPACE {
	public ref class  StructOffset
	{
	protected:
		IntPtr base;
		IntPtr addr;		
	public:
		StructOffset(IntPtr addr,IntPtr base) :addr(addr),base(base)
		{
			
		}
		// ������ļ���ͷ��ƫ����
		[TypeConverter(ValueConverter::typeid)]
		property IntPtr Offset
		{
			IntPtr get()
			{
				switch (IntPtr::Size)
				{
				case sizeof(DWORD32) :
					return IntPtr(addr.ToInt32() - base.ToInt32());
				case sizeof(DWORD64):
					return IntPtr(addr.ToInt64() - base.ToInt64());
				default:
					throw gcnew System::InvalidCastException();
				}
				
			}
		}

	};
}