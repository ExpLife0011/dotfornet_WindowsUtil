#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
#include "..\..\PE\Import\Import.h"
#include "..\..\PE\PeDecoder.h"
#include "..\..\PE\DelayImport\DelayImport.h"
namespace Process
{
	namespace Hook
	{
		// ��֧������,�ɹ��᷵���ӳٵ������ָ��Table�ĵ�ַ
		PVOID HookDelayLoad(LPCSTR dllName, LPCSTR procName, PVOID hookFunc, OUT PVOID* oldFuncAddr = NULL);
	}
}