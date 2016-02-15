#pragma once
#include "../Common/Common.h"
namespace PE
{
	// �������ȡ��
	// ֻ�����ֱ���, ��Ϊ�ṹ��ϵ, û�����ֵĺ����ᱻ©��

	class ExportDirectory;
	class ExportIterator
	{
		ExportDirectory* exportDir;
		int currentIndex;
	public:
		explicit ExportIterator(ExportDirectory* exportDir);
		~ExportIterator();

		PDWORD CurrentFuncRva();
		PDWORD CurrentNameRva();
		PWORD CurrentNameOrdinals();
		bool Next();
		void Reset();
	};

}  // namespace PE
