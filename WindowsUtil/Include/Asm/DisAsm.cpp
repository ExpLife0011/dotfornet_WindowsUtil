#include "DisAsm.h"
namespace Asm
{
	DisAsm::_PrefixRecord::_PrefixRecord()
	{
		Reset();
	}
	void DisAsm::_PrefixRecord::Reset()
	{
		Exist[0] = Exist[1] = Exist[2] = Exist[3] = false;
	}

	BYTE DisAsm::_PrefixRecord::Record(BYTE prefix)
	{
		auto group = PrefixByteToGroup(prefix);
		assert(group > 0);
		if (Exist[group - 1])
		{
			// ����
			return group;
		}
		Exist[group - 1] = true;
		return 0;
	}

	// ��ʼ���ṹ
	DisAsm::DisAsm()
	{
	}

	bool DisAsm::PushPrefix(BYTE prefix)
	{
		auto group = prefixRecord.Record(prefix);
		if (group)
		{
			// ��ͻ
			BYTE tmpPrefix;
			do
			{
				tmpPrefix = prefixs.front();
				prefixs.pop();
				// TODO: ���tmpPrefix
			} while (PrefixByteToGroup(tmpPrefix) != group);
			// TODO: ʣ�����������Ϊ��Чǰ׺,���do����Ҫ�����ֳ���
			return false;
		}
		prefixs.push(prefix);
		return true;
	}
	DisAsm::~DisAsm()
	{
	}
}