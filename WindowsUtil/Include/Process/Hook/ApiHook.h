#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "Opcode\GetInstructionLen.h"
namespace Process
{
	namespace Hook
	{

		using LazyLoad::_VirtualProtect;
		using Process::Hook::GetInstructionLen;
		
		// ע�⣺������Hook������ִ��ԭAPI�����������ѭ������Ҫִ����ʹ�÷��صĵ�ַ
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

		// TODO: UnHook
	}
}