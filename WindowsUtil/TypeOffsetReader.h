#pragma once
#include "BaseRelocationReader.h"
namespace PE
{
	class TypeOffsetReader
	{
	public:
		TypeOffsetReader();
		TypeOffsetReader(PIMAGE_BASE_RELOCATION reloc);		
		~TypeOffsetReader();
		void Init(PIMAGE_BASE_RELOCATION reloc); 
		PWORD Current();
		bool Next();
		void Reset();
		WORD CurrentType();
		DWORD CurrentRelocRva();
		void ApplyCurrentReloc(PVOID oldBase, PVOID currentBase);// �������Ѿ�ӳ����Ϻ�Ҫʹ��

	private:
		DWORD virtualAddress;
		PWORD endTypeOffset;
		PWORD typeOffset;
		PWORD currentTypeOffset;
	};
}

