#pragma once
#include "Common.h"
namespace Hook
{
	// ��֧������,�ɹ��᷵���ӳٵ������ָ��Table�ĵ�ַ
	// �޸�ָ��ģ����ӳٵ����
	// @module: Ҫ�޸ĵ�ģ�飬NULL��ʾ�������
	// @dllName: �ӳٵ����dll��
	// @return: �ɺ�����ַ
	PVOID HookDelayLoad(HMODULE module, LPCSTR dllName, LPCSTR procName, PVOID hookFunc, OUT PVOID* oldFuncAddr = NULL);
}  // namespace Hook