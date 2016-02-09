#include "InstructionState.h"
#include "StateFactory.h"
// Ԥ����Ҫ�Ĳ�������Ϣ�����ָ����
// ��������״̬��End��Rm
const State*  InstructionState::Next(const shared_ptr<Instruction>& inst) const
{
	auto asmInst = inst->Cast<AsmInstruction>();
	auto type = asmInst->GetTmpInstType();

	if (asmInst->outputStr)
	{
		// TODO: �������
	}
	// �����InstChangeData���ýṹ���������ṹ��Ա�������ʹ�С˳�������ͬ
	// InstChangeData�����һ����Ա����������������ֺ�׺�õģ����ﲻ��Ҫ
	auto instData = asmInst->GetTmpData<InstData>();
	if (instData->ParamCount == 0)
	{
		asmInst->operandGrp = NULL;
		asmInst->SetSuccess();
		return asmInst->GetFactory<StateFactory>()->GetState(StateFactory::State_End);
	}
	auto operandGrp = asmInst->wapper->GetOperandGroup(instData->ParamCount, instData->ParamID);
	assert(operandGrp != NULL);
	asmInst->SetOperandGrp(instData->ParamCount, operandGrp);
	return asmInst->GetFactory<StateFactory>()->GetState(StateFactory::State_Operand);

	// TODO: ������ȷ��rm���ڣ����ϵ���������������߶��������߶�rm������rm�ȶ��������õ��ٲ飩��
	// ���ڶ���3�ֽ�ָ�������ʣ�66 0F3A 0F C1 08HΪʲô��palignr Vdq, Wdq, Ib
	// ������palignr Pq, Qq, Ib ��vpalignr Vx,Hx,Wx,Ib
	// ����趨����û�м�¼������Vs�Ľ������ʹ����3�����������ǲ�����©����ʲô��
	// ��ǿ��ǰ׺�鵽��Ӧ���ǵ�3����4�������������ٲ�Ҫǰ׺Ҳ�ǵڶ��������Ϊʲô����д���Ǳ���û��¼�ĵ�һ�������
	// TODO: Ū����ǰ�޷����±࣬��ʱ�����ȣ����ܸ�SSE�汾�йأ�H����Ϊ�ɰ治���ڣ��õ�����ͻ������һ����
	// ����4��������ҪVexǰ׺, ������һ�£�64λ����vexǰ׺vs�������������÷����ԡ�64λ�µ�ָ��Ǹ�32λ��һ��

	/*for (auto i = 0; i < instData->ParamCount; i++)
	{
		auto& tmpOperand = asmInst->wapper->GetOperands(operandGrp[i]);
		if (!tmpOperand.H.IsReg && HasRM((OperandType)tmpOperand.H.Operand))
		{
			return asmInst->GetFactory<StateFactory>()->GetState(StateFactory::State_Rm);
		}
	}
	return asmInst->GetFactory<StateFactory>()->GetState(StateFactory::State_Operand);*/
}

