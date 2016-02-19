#pragma once
#include "Common.h"
#include "Interface\IParseEngine.h"
#include "Interface\IInstruction.h"

class InstructionParser
{
public:
	/*/// <summary>
	/// �����������
	/// </summary>
	/// <param name="parseEngine">���������</param>
	InstructionParser(const shared_ptr<IParseEngine>& parseEngine);*/

	/// <summary>
	/// ��ָ��λ�õĻ�����ת����ָ���ʶ
	/// </summary>
	/// <param name="pos">��������ʼλ��</param>
	/// <param name="result">��ת��ʱ����ȡ���м����ݻḲ�ǲ��洢���ڣ���ʹת��ʧ���м�����Ҳ������մ���</param>
	/// <returns>ָʾ�Ƿ�ת���ɹ�</returns>
	bool TryParse(void* pos, _Out_ shared_ptr<IInstruction>& result);


private:
	shared_ptr<IParseEngine> engine;
};
//
//class InstructionParser
//{
//public:
//
//	InstructionParser()
//	{
//	}
//	// ���ض�ȡ����, ��ȡ��Ϣ������inst������
//	int Read(const shared_ptr<Instruction>& inst) const
//	{
//		auto current = inst->GetFactory()->GetBeginStateInstance();
//		while (current != NULL && current->IsEnd())
//		{
//			current = current->Next(inst);
//			assert(current);  // TODO: grp/esc��ָ�����δд����������ָ�����NULL
//		}
//		return inst->ReadCount();
//	}
//	~InstructionParser()
//	{
//	}
//};

