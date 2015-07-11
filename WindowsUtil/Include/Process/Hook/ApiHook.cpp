#include "ApiHook.h"

namespace Process
{
	namespace Hook
	{

	
		PApiHookStruct HookApi(PVOID desFunc, PVOID hookFunc)
		{
			assert(desFunc&&hookFunc);
			auto result = new ApiHookStruct;
			auto fff = Process::LazyLoad::_VirtualProtect(result, sizeof(_ApiHookStruct), PAGE_EXECUTE_READWRITE, NULL);
			result->Init(desFunc, hookFunc);
			((void(__stdcall*)())&result->Hook)();
			return result;
			// ��ͣ���, �������ڶ��̻߳����»������!! ����Ҫ��ͨ�÷���,����Ҫдdisasm, ��ʱ��һ��
			// api -> jmp B
			// address
			// 
			// A ���渲�ǵ�ǰ�����ֽ�,
			// Hook() ret
			// B �ָ�ǰ�����ֽ�,����ջ��C,pop push A                                                 //XXX pop��ǰret��ַ(������ջ��)(C->����api�ķ��ص�ַ),push C,
			// jmp hook���� ��ѡreturn ԭ����() 
			// 
			// ִ��A,ret��C

		}
	}
}