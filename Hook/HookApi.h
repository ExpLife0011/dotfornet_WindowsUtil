#pragma once
#include "Common.h"
namespace Hook
{
#pragma region ��������ע�ͣ���ʱ��������ⲿ�ֺ�������ɾ��

	//// UNDONE: �����ȱ���ɴ��룬֮��ȫ
	//// ��ǰд�ĵķ�������������⣨ɾ���ˣ������µ����������ٸ�������Ĵ���

	//// ע�⣺������Hook������ִ��Hook���API��ַ�����������ѭ������Ҫִ����ʹ�÷��صĵ�ַ
	//// Ϊ��֧��64λ,ʹ��ff25��jmp,��ַд������ָ�����,���ʹ��e9��jmp��64λʱ����������(����̫Զ��)
	//// ��hook�и�������Ȩ
	//// ���hook����γ�һ����������,�м���һ���������·�,����ĺ���������ִ��
	//// ������ٵ���ԭ����Ҳ����UnHook����delete[]�����ص�ַ�����������ڴ�й¶

	//// api :ԭ������ַ
	//// hook :hook������ַ,�䶨����Ҫ��ԭ����һ��
	//// backupLen :ԭ������Ҫ���ݵ�ָ���,��Ҫ��ȷ�ָ���>=10(64λΪ14,ʹ��ff25 jmp[xxx],���Ե�ַ��������ָ���)
	//// return :���ر��ݺ��Api��ַ��ԭ��������,�����ַunhook��Ҫ�ã�,����ʱ����NULL
	//PVOID _HookApi(PVOID api, PVOID hook, int backupLen);
	//// �Զ�ȷ�������ֳ��İ汾
	//// �����ظ�ʹ�ã�ֻҪ�м��hook������һ��������ԭ����������������Ͽ�
	//PVOID HookApi(PVOID api, PVOID hook);

	//// ֻhookһ�εİ汾,��֧�ֶ��hook,��֧�ָ���������
	//PVOID HookApiOnce(PVOID api, PVOID hook);

	//template<typename T>
	//T HookApiEx(T api, T hook)
	//{
	//	return (T)HookApi(api, hook);
	//}
#pragma endregion


	// ʹ�� jmp[addr]��ת, ���洢��ʽΪ
	//		ff 25 [end]
	// end: addr

	// UNDONE: ֮��Ჹ���Զ��жϱ��ݳ��ȣ�ֻ��hookһ�Σ�hook��ε��п����޸�
	// 
	// @api: ��hook�ĺ�����ַ
	// @hook: hook������ַ����Ҫ������ԭ����һ�£�����ȡ������
	// @backupLen: ����api��ͷָ��ȣ���Ҫ����api��ͷ��ȷ�Ļ��ָ��ݳ��ȣ����ܽضϡ�
	//			   ������ȷ�ı��ݳ�����Ҫ��������棬*δд��*�������÷���๤�ߵõ���ȷ����
	//			   ������Сֵ32λ��10��64λ��14����Ҫ����ʵ��api��ͷ���ָ��ȵ���
	//			   ������С���ݳ���Ŀ���ǵ���ԭʼ����ʱ�ܵõ���ȷ������������Ҫ����ԭʼ���������Ժ���
	// @oldFunc: ����ԭʼ��������λ��,�����Ҫ����ԭʼ�����͵��������ַ������ʱ��Ҫ����������������Ҫ����ԭ�����ʹ�nullptr
	//			 ע�⣺�˷��ؿ�����unhook���õ����غ��������Ҫ����ԭ����ʱ��Ҫdelete[]���������ڴ�
	// @return: �����Ƿ�ɹ�
	bool HookApi_FF25(_In_ _Notnull_ PVOID api,
		_In_ _Notnull_  PVOID hook,
		int backupLen,
		_Outptr_opt_ PVOID* oldFunc);

	// ʹ��e9 jmp�İ汾,��hook��ַ��api��ַ�����Զ�����ã�64λ�������֣�,�������޸ĵĴ���û��ô��= =
	// @backuplen: api������ַ��hook������ַ���벻�ܹ�Զ����С���ݳ�����5
	bool HookApi_E9(_In_ _Notnull_ PVOID api,
		_In_ _Notnull_  PVOID hook,
		int backupLen,
		_Outptr_opt_ PVOID* oldFunc);

	// �����ж�api��hook����֮��ľ��룬̫Զ����ff25��Զ�������ã�
	bool IsLongDistance(PVOID addr1, PVOID addr2);
}  // namespace Hook