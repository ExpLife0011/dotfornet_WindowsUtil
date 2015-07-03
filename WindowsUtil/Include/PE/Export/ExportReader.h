#pragma once
#include "..\PeDecoder.h"
namespace PE{
	namespace Export{

		// �������ȡ�� TODO: ���һ��c++�������Ʒ�����,����һ��ϵͳ������û���ֳɺ���
		// ֻ�����ֱ���, ��Ϊ�ṹ��ϵ, û�����ֵĺ����ᱻ©��
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
			PDWORD FuncTable();
			PDWORD NameTable();
			PWORD OrdinalTable();
			PDWORD NumberOfFunctions();
			PDWORD NumberOfNames();
		private:
			PIMAGE_EXPORT_DIRECTORY exportDirectory;
			PDWORD numberOfFunctions;
			PDWORD numberOfNames;
			PDWORD funcs;
			PDWORD names;
			PWORD nameOrdinals;
			int currentIndex;
		};
		FARPROC GetProcAddress(PeDecoder& pe, LPCSTR lpProcName); // ���ֲ���
		FARPROC GetProcAddress(HMODULE module, LPCSTR lpProcName);
		FARPROC GetProcAddress(HMODULE module, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName)); // ˳�����, ���Ƚ���, ����true��ʾֵ��ͬ
		FARPROC GetProcAddress(PeDecoder& pe, PVOID compareName, bool compareCallback(PVOID compare, LPCSTR procName));
	}
}