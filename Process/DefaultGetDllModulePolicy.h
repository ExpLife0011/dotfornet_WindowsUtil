#pragma once
namespace Process
{
	namespace LazyLoad
	{
		namespace Detail
		{
			// ʹ����д��loadlibrary
			// �����Ҫʹ�ü��ܵ�dll���ƣ���Ҫ�޸Ĵ������ͺͽ���policy��GetStr��������
			struct DefaultGetDllModulePolicy
			{
				static HMODULE GetDllModule(LPCWSTR dllName);
			};
		}  // namespace Detail
	}  // namespace LazyLoad
}  // namespace Process
