#pragma once
#include "Common.h"
#include "LdrDataTable.h"
namespace Process
{
	namespace EnvironmentBlock
	{
		// �����Ѿ������dll
		HMODULE __stdcall FindLoadedModuleHandle(LPCWSTR name);
	}  // namespace EnvironmentBlock
}  // namespace Process
