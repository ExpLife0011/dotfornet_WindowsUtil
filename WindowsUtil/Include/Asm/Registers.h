#pragma once
#include <Windows.h>
#include <WinBase.h>
#include <assert.h>
namespace Asm
{
#pragma region �Ĵ�����
	enum RegisterLength
	{
		Len_8,
		Len_16,
		Len_32,
		Len_64,
		Len_64_MM,
		Len_128_XMM
	};

	extern const PCSTR Registers[16][6];

	// ȡ�Ĵ�����
	// hex 0-15 type 0-5
	PCSTR GetRegisterName(BYTE hex, RegisterLength type);
#pragma endregion
}