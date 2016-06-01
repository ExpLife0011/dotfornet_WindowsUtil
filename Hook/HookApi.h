#pragma once
#include "Common.h"
namespace Hook
{
#define UNDONE
	// UNDONE: �����ȱ���ɴ��룬֮��ȫ
	// ��ǰд�ĵķ�������������⣨ɾ���ˣ������µ����������ٸ�������Ĵ���
#ifndef UNDONE

	// ע�⣺������Hook������ִ��Hook���API��ַ�����������ѭ������Ҫִ����ʹ�÷��صĵ�ַ
	// Ϊ��֧��64λ,ʹ��ff25��jmp,��ַд������ָ�����,���ʹ��e9��jmp��64λʱ����������(����̫Զ��)
	// ��hook�и�������Ȩ
	// ���hook����γ�һ����������,�м���һ���������·�,����ĺ���������ִ��
	// ������ٵ���ԭ����Ҳ����UnHook����delete[]�����ص�ַ�����������ڴ�й¶

	// api :ԭ������ַ
	// hook :hook������ַ,�䶨����Ҫ��ԭ����һ��
	// backupLen :ԭ������Ҫ���ݵ�ָ���,��Ҫ��ȷ�ָ���>=10(64λΪ14,ʹ��ff25 jmp[xxx],���Ե�ַ��������ָ���)
	// return :���ر��ݺ��Api��ַ��ԭ��������,�����ַunhook��Ҫ�ã�,����ʱ����NULL
	PVOID _HookApi(PVOID api, PVOID hook, int backupLen);
	// �Զ�ȷ�������ֳ��İ汾
	// �����ظ�ʹ�ã�ֻҪ�м��hook������һ��������ԭ����������������Ͽ�
	PVOID HookApi(PVOID api, PVOID hook);

	// ֻhookһ�εİ汾,��֧�ֶ��hook,��֧�ָ���������
	PVOID HookApiOnce(PVOID api, PVOID hook);

	template<typename T>
	T HookApiEx(T api, T hook)
	{
		return (T)HookApi(api, hook);
	}

#endif // UNDONE
}  // namespace Hook