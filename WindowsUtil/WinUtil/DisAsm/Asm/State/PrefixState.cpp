//#include "..\Common\Common.h"
//#include "StateFactory.h"
//const State*  PrefixState::Next(const shared_ptr<Instruction>& inst) const
//{
//	auto asmInst = inst->Cast<AsmInstruction>();
//	assert(asmInst->opcodeDataStorage.GetType() == OT_Prefix);
//	auto pfxHex = *asmInst->CurrentBytePtr();
//	// �洢��ȡ����ǰ׺
//	auto pfxInst = asmInst->opcodeDataStorage.GetData<PrefixInstData>();
//	if (!asmInst->prefixStorage.Push(pfxHex, pfxInst))
//	{
//		// ǰ׺��ͻ
//		asmInst->SetSuccess();
//		return inst->GetFactory<StateFactory>()->GetState(StateFactory::State_End);
//	}
//	return inst->GetFactory<StateFactory>()->GetState(StateFactory::State_Byte);
//}
