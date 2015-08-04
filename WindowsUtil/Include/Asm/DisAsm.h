#pragma once
#include <windows.h>
#include <WinBase.h>
#include <queue>
#include "opcodes.h"
namespace Asm
{
	class DisAsm
	{
	public:
		DisAsm();
		~DisAsm();

	private:
		bool PushPrefix(BYTE prefix); // ʧ��ʱ��ʾ������ͻ
		std::queue<BYTE> prefixs;
		struct _PrefixRecord
		{
			_PrefixRecord();
			void Reset();
			BYTE Record(BYTE prefix); // ����ͻ����0��ʧ�ܷ������1-4
			bool Exist[4];
		}prefixRecord;
	};
}