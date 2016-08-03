#pragma once
#include "Common.h"

namespace Process
{
	namespace Overwrite
	{
		// NOTICE: ����ĺ���ֻ֧������������, ��ʹ������
		// ���ֲ���(����������)
		void* GetProcAddress(HMODULE module, LPCSTR lpProcName);
		// ˳�����
		// function�����Ƕ������ַ�
		void* GetProcAddress(HMODULE module,const _STD function<bool(LPCSTR)>& comp);

		// ���ֲ���, �Զ��ƱȽϺ���
		// @lpProcName: ��ʾ����ָ�룬�����Ǽ���ʲô�ģ���Ҫ�ڻص����Լ�����
		// @comp: function��һ����Ϊ������ڵ㺯�������ڶ�����ΪlpProcName�����ش�С��ϵ,С����<0,��>0,��==0
		void* GetProcAddress(HMODULE module, const void* lpProcName, const _STD function<int(LPCSTR, const void*)>& comp);

	}  // namespace Overwrite
}  // namespace Process
