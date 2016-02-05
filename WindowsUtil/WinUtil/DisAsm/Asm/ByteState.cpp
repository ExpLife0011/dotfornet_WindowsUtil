#include "ByteState.h"
#include "StateFactory.h"
// ��Hex��״̬������HexInst������ת�����ܻ��ν���
// Grp��Escָ���¼��ʽ��ͬ�������ɸ��Ե�״̬�ֱ��ȡ
// ��������״̬��Instruction��Group��Byte��Escape��Prefix��End
const State*  ByteState::Next(const shared_ptr<Instruction>& inst) const
{
	auto asmInst = inst->Cast<AsmInstruction>();
	// �����¸�״̬
	auto asmFac = asmInst->GetFactory<StateFactory>();
	// ��Ҫ�����ϸ�ָ�������ȷ��Ӧ�ö�ȡ�ĸ������ֽ�ָ�
	auto lastInstType = asmInst->GetTmpInstType();
	auto currentInstType = asmInst->ReadInst(lastInstType);
	return asmFac->GetState(currentInstType);
}
