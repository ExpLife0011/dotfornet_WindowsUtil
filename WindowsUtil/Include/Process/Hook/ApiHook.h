#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
namespace Process
{
	namespace Hook
	{
		// hook����������ԭ�Ⱥ���
		bool HookApi(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc);
	}
}