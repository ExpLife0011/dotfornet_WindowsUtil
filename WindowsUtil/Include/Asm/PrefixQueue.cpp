#include "PrefixQueue.h"
namespace Asm
{

	int PrefixQueue::Push(OpcodePrefix prefix)
	{
		auto group = prefix.PrefixGroup;
		if (!Exist[group -1])
		{
			ConflictQueues.swap(std::queue<OpcodePrefix>());
			Exist[group -1] = true;
			prefixQueues.push(prefix);
			return true;
		}
		else
		{
			// ���ڣ����ӵ�������ŵ��ڳ�ͻ���
			OpcodePrefix tmpPrefixQueue;
			do
			{
				tmpPrefixQueue = prefixQueues.front();
				Pop();
				ConflictQueues.push(tmpPrefixQueue);// ���
			} while (tmpPrefixQueue.PrefixGroup != group);

		}
		return false;
	}

	BYTE PrefixQueue::Pop()
	{
		Exist[prefixQueues.front().PrefixGroup - 1] = false;
		prefixQueues.pop();
		return 0;
	}


	PrefixQueue::PrefixQueue()
	{
	}

	//	bool PrefixQueue::PushPrefixQueue(BYTE PrefixQueue)
//	{
		//auto group = PrefixQueueRecord.Record(PrefixQueue);
		//if (group)
		//{
		//	// ��ͻ
		//	BYTE tmpPrefixQueue;
		//	do
		//	{
		//		tmpPrefixQueue = PrefixQueues.front();
		//		PrefixQueues.pop();
		//		// TODO: ���tmpPrefixQueue
		//	} while (PrefixByteToGroup(tmpPrefixQueue) != group);
		//	// TODO: ʣ�����������Ϊ��Чǰ׺,���do����Ҫ�����ֳ���
		//	return false;
		//}
		//PrefixQueues.push(PrefixQueue);
	//	return true;
//	}
	PrefixQueue::~PrefixQueue()
	{
	}
	void PrefixQueue::Reset()
	{
		for (int i = 0; i < 4; i++)
		{
			Exist[i] = false;
		}
		prefixQueues.swap(std::queue<OpcodePrefix>());
	}
}