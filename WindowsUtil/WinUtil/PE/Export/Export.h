#pragma once
#include <cassert>
#include "ExportReader.h"

namespace PE
{
	namespace Export
	{
		PDWORD GetProcExportFuncTableAddress(PeDecoder& pe, LPCSTR lpProcName); // ���ֲ���
		// NOTICE: ����ĺ���ֻ֧������������, ��ʹ������
		FARPROC GetProcAddress(PeDecoder& pe, LPCSTR lpProcName);
		FARPROC GetProcAddress(HMODULE module, LPCSTR lpProcName);
		FARPROC GetProcAddress(HMODULE module, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName)); // ˳�����, ���Ƚ���, ����true��ʾֵ��ͬ
		FARPROC GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName));
	}
}