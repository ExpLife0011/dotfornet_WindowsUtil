#pragma once
namespace Process
{
	namespace LazyLoad
	{
		namespace Detail
		{
			// ֻ�����Ѿ������dll
			struct NtDllGetDllModulePolicy
			{
				static HMODULE GetDllModule(LPCWSTR dllName);
			};
		}  // namespace Detail
	}  // namespace LazyLoad
}  // namespace Process
