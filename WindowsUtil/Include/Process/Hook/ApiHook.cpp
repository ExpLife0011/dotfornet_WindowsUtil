#include "ApiHook.h"

namespace Process
{
	namespace Hook
	{
		bool HookApi(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc)
		{
			auto funcAddr = Process::LazyLoad::_GetProcAddressEx(dllName, procName);
			if (!funcAddr)
			{
				return false;
			}
			// A ���渲�ǵ�ǰ�����ֽ�,Hook
			// api -> jmp B
			// B �ָ�ǰ�����ֽ�,pop��ǰret��ַ(������ջ��)(C->����api�ķ��ص�ַ),push A,push C
			// 
		}
	}
}