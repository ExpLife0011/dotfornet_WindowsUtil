#include "EatHook.h"

namespace Process
{
	namespace Hook
	{
		PVOID HookEat(LPCWSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PDWORD oldFuncRva)
		{
			auto dllBase = LazyLoad::_LoadLibraryW(dllName);
			
			PE::PeDecoder dll;
			if (!dll.LoadPEImage(dllBase, true))
			{
				return NULL;
			}
			auto result = PE::Export::GetProcExportFuncTableAddress(dll, procName);
			if (!result)
			{
				return NULL;
			}
			// dll base + rva = funcRealAddress ���Ƶ���
			// base + setRva = hookAddress
			if (oldFuncRva)
			{
				*oldFuncRva = *result;
			}
			LONG setRva;
			if (dll.hasNtHeader32)
			{
				setRva = (LONG)hookFunc - (LONG)dllBase;
			}
			else
			{
				auto tmpDta = (LONGLONG)hookFunc - (LONGLONG)dllBase;
				if (tmpDta>0 && tmpDta<LONG_MAX)
				{
					setRva = (LONG)tmpDta;
				}
				else
				{
					// NOTICE: ��Ϊ������ṹԭ��,�洢����������DWORD,�����ڸ���64λ��base֮����ǰƫ��,�����޷�hook
					return NULL;
				}
				
			}
			Process::Overwrite::_WriteProcessMemory(NtCurrentProcess(), result, &setRva, sizeof(DWORD), NULL);
			return result;
		}
	}
}