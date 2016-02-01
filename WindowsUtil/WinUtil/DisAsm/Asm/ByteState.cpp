#include "ByteState.h"
#include "StateFactory.h"
const unique_ptr<IState>&  ByteState::Next(shared_ptr<Instruction>& inst)
{
	auto asmInst = inst->Cast<AsmInstruction>();
	// �����¸�״̬
	auto asmFac = asmInst->GetFactory<StateFactory>();
	// ��Ҫ�����ϸ�ָ�������ȷ��Ӧ�ö�ȡ�ĸ������ֽ�ָ�
	auto lastInstType = asmInst->GetTmpInstType();
	auto currentInstType = asmInst->ReadInst(lastInstType);
	return asmFac->GetState(currentInstType);
}
