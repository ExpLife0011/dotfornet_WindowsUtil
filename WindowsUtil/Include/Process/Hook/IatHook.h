#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "..\..\PE\Import\Import.h"
namespace Process
{
	namespace Hook
	{
		// �ɹ�hook����thunk��ַ, unhook��ʱ���õ�, ʧ�ܷ���NULL
		PVOID HookIat(LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress);
		PVOID HookIat(LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress); 
		
	}
}
