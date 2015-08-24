#pragma once
#include <windows.h>
#include <WinBase.h>
#include <queue>
#include "OpcodeTables.h"
namespace Asm
{
	class PrefixQueue
	{
	public:
		PrefixQueue();
		~PrefixQueue();
		void Reset(); 

		// ����0��ʾ�ɹ���ӣ�����0ֵ��ʾ��ͻ��������������
		int Push(OpcodePrefix prefix);
		std::queue<OpcodePrefix> ConflictQueues; // ��ͻ��ǰ׺���⣬�´�push��
		BYTE Pop();
	private:
		
		std::queue<OpcodePrefix> prefixQueues;
		

		bool Exist[4];

	};
}