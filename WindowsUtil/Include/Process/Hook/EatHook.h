#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "..\..\PE\Export\Export.h"
namespace Process
{
	namespace Hook
	{
		// ʧ�ܷ���NULL, �ɹ����غ�����Ӧ�������е�funcTable��ַ(unhook�õ�)
		// hook�󲻻��Զ�����ԭ�Ⱥ���, �����Ҫ��ʹ��OUT����
		PVOID HookEat(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PDWORD oldFuncRva=NULL);

	}
}