#include "OperandState.h"
//#include "StateFactory.h"
//
//// TODO: ���ĵ�63ҳCHAPTER 3 BASIC EXECUTION ENVIRONMENT ��ʼ��
//// TODO: �������SSE�Ļ�ͦ�ҵģ��ȿ�һ��ʱ���ĵ���˵
//// TODO: ȱ���ĵ�3A����������˵��
//
//// �����������������Ϣ
//const State* OperandState::Next(const shared_ptr<Instruction>& inst) const
//{
//	auto asmInst = inst->Cast<AsmInstruction>();
//	auto operandGrp = asmInst->operandGrpStorage.GetOperandGrp();
//	auto grpCount = asmInst->operandGrpStorage.GetOperandCount();
//	// ��ʱ�Ķ�ȡλ����ָ��Hex��RM�������Hexǰ
//	// ��RM��sib������������Ჽ�������͵ĳ��ȣ�
//	// ����ǲ���������Ҫ��¼������ʼ��ַ�����ͳ��Ⱥ����ͣ�����������ʱ�ã�������ָ���͵�����˫���ȸ���ɶ�ģ�
//	// ����ǼĴ��������¼regö��ֵ���ɱ䳤�Ļ�ѡ������ȷ�ֳ��ļĴ�����
//	// TODO: ��Ҫȷ���ô洢ʲô���ݣ�Dflag��ô�õ�
//
//	for (auto i = 0; i < grpCount; i++)
//	{
//		auto& tmpOperand = asmInst->GetOpcodeDataWapper()->GetOperands(operandGrp[i]);
//		ReadOperand(asmInst, i, tmpOperand);
//	}
//	
//	asmInst->SetSuccess();
//	return inst->GetFactory()->GetState(StateFactory::State_End);
//}
//
//void OperandState::ReadOperand(AsmInstruction* asmInst, int index, const RegOrOperandGroup& pair) const
//{
//	// ֻ��H�ſ���Ϊreg
//	if (pair.H.IsReg)
//	{
//		// ��Ϊ�μĴ��������reg��һ������Ҫ��һ��
//		if (asmInst->GetOpcodeDataWapper()->IsSeg(pair.H.Val))
//		{
//			// LΪNULL������
//			assert(pair.L.Val == NULL);
//			Handle_SEG(asmInst, index, pair.H);
//		}
//		else
//		{
//			// ��reg����ϵ�L����ҪôΪNULL��ҪôΪCHANGE_REG������ֱ������ָʾ�Ƿ���Ը��ݴ�С�ɱ�ı�ʶ
//			Handle_REG(asmInst, index, pair.H, pair.L.Val);
//		}
//	}
//	else
//	{
//		assert(pair.H.Val >= NULL && pair.H.Val <= SPC_Ux_Mw);
//		assert(pair.L.Val >= NULL && pair.L.Val <= SPC_Ux_Mw);
//		// ��ȷ��������������ʹ��Ѱַ��ʽ
//		OperandState::HandleFunctions[pair.L.Operand](asmInst, index);
//		OperandState::HandleFunctions[pair.H.Operand](asmInst, index);
//	}
//}

namespace Disassembler
{
	void AsmState<AsmStateFactory::State_Operand>::Handle_NULL(AsmStateFactory::ParamType * param, int index)
	{
		// H��L���п���ѡ�����
	}
	// NOTICE: ˳������ö��ֵһ��
	const AsmState<AsmStateFactory::State_Operand>::HandleFunction  AsmState<AsmStateFactory::State_Operand>::HandleFunctions[] =
	{
		Handle_NULL,
		Handle_L_a,
		Handle_L_b,
		Handle_L_c,
		Handle_L_d,
		Handle_L_dq,
		Handle_L_p,
		Handle_L_pd,
		Handle_L_pi,
		Handle_L_ps,
		Handle_L_q,
		Handle_L_qq,
		Handle_L_s,
		Handle_L_sd,
		Handle_L_ss,
		Handle_L_si,
		Handle_L_v,
		Handle_L_w,
		Handle_L_x,
		Handle_L_y,
		Handle_L_z,
		Handle_H_1,
		Handle_H_A,
		Handle_H_B,
		Handle_H_C,
		Handle_H_D,
		Handle_H_E,
		Handle_H_F,
		Handle_H_G,
		Handle_H_H,
		Handle_H_I,
		Handle_H_J,
		Handle_H_L,
		Handle_H_M,
		Handle_H_N,
		Handle_H_O,
		Handle_H_P,
		Handle_H_Q,
		Handle_H_R,
		Handle_H_S,
		Handle_H_U,
		Handle_H_V,
		Handle_H_W,
		Handle_H_X,
		Handle_H_Y,
		Handle_SPC_AL_R8L,
		Handle_SPC_CL_R9L,
		Handle_SPC_DL_R10L,
		Handle_SPC_BL_R11L,
		Handle_SPC_AH_R12L,
		Handle_SPC_CH_R13L,
		Handle_SPC_DH_R14L,
		Handle_SPC_BH_R15L,
		Handle_SPC_AL_rAX,
		Handle_SPC_rAX_r8,
		Handle_SPC_rCX_r9,
		Handle_SPC_rDX_r10,
		Handle_SPC_rBX_r11,
		Handle_SPC_rSP_r12,
		Handle_SPC_rBP_r13,
		Handle_SPC_rSI_r14,
		Handle_SPC_rDI_r15,
		Handle_SPC_RAX_EAX_R8_R8D,
		Handle_SPC_RCX_ECX_R9_R9D,
		Handle_SPC_RDX_EDX_R10_R10D,
		Handle_SPC_RBX_EBX_R11_R11D,
		Handle_SPC_RSP_ESP_R12_R12D,
		Handle_SPC_RBP_EBP_R13_R13D,
		Handle_SPC_RSI_ESI_R14_R14D,
		Handle_SPC_RDI_EDI_R15_R15D,
		Handle_SPC_Ib_Iz,
		Handle_SPC_Mw_Rv,
		Handle_SPC_Rd_Mb,
		Handle_SPC_Rd_Mw,
		Handle_SPC_Rv_Mw,
		Handle_SPC_Ry_Mb,
		Handle_SPC_Ry_Mw,
		Handle_SPC_Udq_Md,
		Handle_SPC_Ux_Md,
		Handle_SPC_Ux_Mq,
		Handle_SPC_Ux_Mw,
	};
}  // namespace Disassembler