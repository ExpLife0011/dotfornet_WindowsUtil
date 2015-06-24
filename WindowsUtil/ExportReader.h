#pragma once
#include "PeDecoder.h"
namespace PE{
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
		DWORD currentIndex;
	};
}