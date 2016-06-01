#pragma once
#include "Common.h"
namespace Hook
{
	// ���̰߳�ȫ
	// �޸�ָ��ģ��ĵ����洢�ĺ���ָ�룬ֻ���ֱ�ӵ��õĺ�����Ч
	// @module: Ŀ��MODULE, NULL��ʾ�������
	// @dllName: hook�������ڵ�dll
	// @procName: hook�ĺ�����
	// @hookFunc: ��Ҫд��ĺ�����ַ
	// @unhookAddress: �ɹ�hook������thunk��ַ,unhook��ʱ���õ�(��oldFuncAddressд��Ϳ���),����NULL����Ե�
	// @return:  �ɹ��᷵�ؾɺ�����ַ��hook�󲻻��Զ�����ԭ�Ⱥ���, �����Ҫ���Ե��ô�ָ��, ʧ�ܷ���NULL
	PVOID HookIat(HMODULE module, LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* unhookAddress);

	bool UnHookIat(PVOID unhookAddress, PVOID oldFunctionAddress);
}  // namespace Hook