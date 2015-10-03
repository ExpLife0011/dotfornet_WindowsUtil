#pragma once
#include "..\OverwriteWinApi\OverwriteWinApi.h"
#include "Opcode\GetInstructionLen.h"
namespace Process
{
	namespace Hook
	{

		// ע�⣺������Hook������ִ��ԭAPI�����������ѭ������Ҫִ����ʹ�÷��صĵ�ַ
		// ���hook����γ�һ����������,�м���һ���������·�,����ĺ���������ִ��
		// ������ٵ���ԭ����Ҳ����UnHook����delete[]�����ص�ַ
		
		// backupLen>5
		// api :ԭ������ַ
		// hook :hook������ַ,�䶨����Ҫ��ԭ����һ��
		// backupLen :ԭ������Ҫ���ݵ�ָ���,��Ҫ��ȷ�ָ���>=5(ʹ��E9XXXXXXXX jmp)
		// return :���ر��ݺ��Api��ַ��ԭ��������,�����ַunhook��Ҫ�ã�,����ʱ����NULL
		PVOID _HookApi32(PVOID api, PVOID hook, int backupLen);
		
		// �Զ�ȷ�������ֳ��İ汾
		// �����ظ�ʹ�ã�ֻҪ�м��hook������һ��������ԭ����������������Ͽ�
		PVOID HookApi32(PVOID api, PVOID hook);

		// ���hook�ض�λjmp��ֵ�õģ����Ӿͺ�
		void _RelocJmp(PVOID des, PVOID oldAddr, int offset);

		template<typename T>
		T HookApi32Ex(T api, T hook)
		{
			return (T)HookApi32(api, hook);
		}


		// TODO: UnHook
	}
}