#pragma once
#include "Common.h"
namespace Hook
{
	// ʧ�ܷ���NULL, �ɹ����غ�����Ӧ�������е�funcTable��ַ(unhook�õ�)
	// hook�󲻻��Զ�����ԭ�Ⱥ���, �����Ҫ��ʹ��OUT����

	// ���̰߳�ȫ
	// �޸�������ģ��ĵ�����ֻ���֮���getprocaddress���ؽ����Ч
	// @module: ģ��ָ�룬����ΪNULL
	// @procName: ��ģ��ĵ���������
	// @return: �ɺ�����ַ
	PVOID HookEat(HMODULE module, LPCSTR procName, LPCVOID hookFunc, OUT PDWORD* oldFuncRva = NULL);
}  // namespace Hook