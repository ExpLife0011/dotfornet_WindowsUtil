#include "IatHook.h"
namespace Process
{
	namespace Hook
	{
		using EnvironmentBlock::PTEB_Ex;
		using EnvironmentBlock::PEB_Ex;
		PVOID HookIat(LPCSTR dllName, LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress)
		{
			auto currentProcessBaseAddress = NtCurrentPeb->ImageBaseAddress;
			PE::PeDecoder pe;
			if (!pe.LoadPEImage(currentProcessBaseAddress, true))
			{
				return NULL;
			}
			auto thunkAddress = PE::Import::GetProcImportThunkAddress(pe, dllName, procName);
			if (!thunkAddress)
			{
				return NULL;
			}
			if (pe.hasNtHeader32)
			{
				if (oldFuncAddress)
				{
					*oldFuncAddress = (PVOID)*(PDWORD)thunkAddress;
				}
				//*(PDWORD)thunkAddress = (DWORD)hookFunc;
			}
			else
			{
				if (oldFuncAddress)
				{
					*oldFuncAddress = (PVOID)*(PDWORDLONG)thunkAddress;
				}
				//*(PDWORDLONG)thunkAddress = (DWORDLONG)hookFunc;
			}
			DWORD size = sizeof(PVOID);
			// ԭ����Ҫ��������ɶ�д��, ����ʹ�������д�뺯��, ����������������
			if (Overwrite::_WriteProcessMemory(NtCurrentProcess(), thunkAddress, &hookFunc, size, NULL))
			{
				return thunkAddress;
			}
			return NULL;
		}
		PVOID HookIat(LPCSTR procName, LPCVOID hookFunc, OUT PVOID* oldFuncAddress)
		{
			return HookIat(NULL, procName, hookFunc, oldFuncAddress);
		}
	}
}