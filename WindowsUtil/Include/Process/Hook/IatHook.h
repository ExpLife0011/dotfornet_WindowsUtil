#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "..\..\PE\Import\Import.h"
namespace Process
{
	namespace Hook
	{
		// �ɹ�hook����thunk��ַ, unhook��ʱ���õ�, ʧ�ܷ���NULL, hook�󲻻��Զ�����ԭ�Ⱥ���
		// hook�󲻻��Զ�����ԭ�Ⱥ���, �����Ҫ��ʹ��OUT����
		PVOID HookIat(LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress=NULL);
		PVOID HookIat(LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress = NULL);
		
	}
}
