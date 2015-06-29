#pragma once
#include "..\PeDecoder.h"
namespace PE{
	namespace Export{

		// �������ȡ�� TODO: ���һ��c++�������Ʒ�����,����һ��ϵͳ������û���ֳɺ���
		class ExportReader
		{
		public:
			ExportReader(PeDecoder& pe);
			ExportReader(PeDecoder& pe, PIMAGE_EXPORT_DIRECTORY exportDirectory);
			~ExportReader();
			PIMAGE_EXPORT_DIRECTORY GetExportDirectory();
			PDWORD CurrentFuncRva();
			PDWORD CurrentNameRva();
			PWORD CurrentNameOrdinals();
			bool Next();
			void Reset();
		private:
			PIMAGE_EXPORT_DIRECTORY exportDirectory;
			PDWORD numberOfFunctions;
			PDWORD funcs;
			PDWORD names;
			PWORD nameOrdinals;
			int currentIndex;
		};
		FARPROC GetProcAddress(PeDecoder& pe, LPCSTR lpProcName);
		FARPROC GetProcAddress(HMODULE module, LPCSTR lpProcName);
		FARPROC GetProcAddress(HMODULE module, PVOID compareName, bool compareCallback(PVOID compare, LPSTR procName)); // ���Ƚ���, ����true��ʾֵ��ͬ
		FARPROC GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPSTR procName));
	}
}