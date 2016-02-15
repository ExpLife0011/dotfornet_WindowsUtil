#include "ByteState.h"
#include "StateFactory.h"
// ��Hex��״̬������HexInst������ת�����ܻ��ν���
// Grp��Escָ���¼��ʽ��ͬ�������ɸ��Ե�״̬�ֱ��ȡ
// ��������״̬��Instruction��Group��Byte��Escape��Prefix��End
const State*  ByteState::Next(const shared_ptr<Instruction>& inst) const
{
	auto asmInst = inst->Cast<AsmInstruction>();
	if (!asmInst->NextByte())
	{
		return asmInst->GetFactory()->GetState(StateFactory::State_End);
	}
	// �����¸�״̬
	auto asmFac = asmInst->GetFactory<StateFactory>();
	// ��Ҫ�����ϸ�ָ�������ȷ��Ӧ�ö�ȡ�ĸ������ֽ�ָ�
	auto lastInstType = asmInst->opcodeDataStorage.GetType();
	auto currentInstType = asmInst->ReadInst(lastInstType);
	return asmFac->GetState(currentInstType);  // ��ת����Ķ�ȡλ����û�в�����
}
