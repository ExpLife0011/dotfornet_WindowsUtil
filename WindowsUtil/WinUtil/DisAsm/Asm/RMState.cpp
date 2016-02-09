#include "..\Common\Common.h"
#include "StateFactory.h"
// ���������������ʽ������
// ����ת��End��Operand��Sib
const State* RmState::Next(const shared_ptr<Instruction>& inst) const 
{ 
	auto asmInst = inst->Cast<AsmInstruction>();
	
	// TODO: ��������Prefix������������Ҫ��Ūһ�����Է���ת�ַ����ı�
	// ��Ӳ�������ȡ������������״̬����
	for (auto i = 0; i < asmInst->GetOperandCount(); i++)
	{
		auto& tmpOperand = asmInst->wapper->GetOperands(asmInst ->GetOperandGrp()[i]);
		if (!tmpOperand.H.IsReg && HasRM((OperandType)tmpOperand.H.Operand))
		{
			return asmInst->GetFactory<StateFactory>()->GetState(StateFactory::State_Rm);
		}
	}
	return asmInst->GetFactory<StateFactory>()->GetState(StateFactory::State_Operand); 
	return NULL;
}

bool RmState::HasRM(OperandType ot)
{
	switch (ot)
	{
	case H_C:
	case H_D:
	case H_E:
	case H_G:
	case H_M:
	case H_N:
	case H_P:
	case H_Q:
	case H_R:
	case H_S:
	case H_U:
	case H_V:
	case H_W:
	case SPC_Mw_Rv:
	case SPC_Rd_Mb:
	case SPC_Rd_Mw:
	case SPC_Rv_Mw:
	case SPC_Ry_Mb:
	case SPC_Ry_Mw:
	case SPC_Udq_Md:
	case SPC_Ux_Md:
	case SPC_Ux_Mq:
	case SPC_Ux_Mw:
		return true;
	default:
		break;
	}
	return false;
}
