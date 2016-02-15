#include "OperandState.h"
#include "StateFactory.h"

// TODO: ���ĵ�63ҳCHAPTER 3 BASIC EXECUTION ENVIRONMENT ��ʼ��
// TODO: �������SSE�Ļ�ͦ�ҵģ��ȿ�һ��ʱ���ĵ���˵
// TODO: ȱ���ĵ�3A����������˵��

// �����������������Ϣ
const State* OperandState::Next(const shared_ptr<Instruction>& inst) const
{
	auto asmInst = inst->Cast<AsmInstruction>();
	auto operandGrp = asmInst->operandGrpStorage.GetOperandGrp();
	auto grpCount = asmInst->operandGrpStorage.GetOperandCount();
	// ��ʱ�Ķ�ȡλ����ָ��Hex��RM�������Hexǰ
	// ��RM��sib������������Ჽ�������͵ĳ��ȣ�
	// ����ǲ���������Ҫ��¼������ʼ��ַ�����ͳ��Ⱥ����ͣ�����������ʱ�ã�������ָ���͵�����˫���ȸ���ɶ�ģ�
	// ����ǼĴ��������¼regö��ֵ���ɱ䳤�Ļ�ѡ������ȷ�ֳ��ļĴ�����
	// TODO: ��Ҫȷ���ô洢ʲô���ݣ�Dflag��ô�õ�

	for (auto i = 0; i < grpCount; i++)
	{
		auto& tmpOperand = asmInst->GetOpcodeDataWapper()->GetOperands(operandGrp[i]);
		ReadOperand(asmInst, i, tmpOperand);
	}
	
	asmInst->SetSuccess();
	return inst->GetFactory()->GetState(StateFactory::State_End);
}

void OperandState::ReadOperand(AsmInstruction* asmInst, int index, const RegOrOperandGroup& pair) const
{
	// ֻ��H�ſ���Ϊreg
	if (pair.H.IsReg)
	{
		// ��Ϊ�μĴ��������reg��һ������Ҫ��һ��
		if (asmInst->GetOpcodeDataWapper()->IsSeg(pair.H.Val))
		{
			// LΪNULL������
			assert(pair.L.Val == NULL);
			Handle_SEG(asmInst, index, pair.H);
		}
		else
		{
			// ��reg����ϵ�L����ҪôΪNULL��ҪôΪCHANGE_REG������ֱ������ָʾ�Ƿ���Ը��ݴ�С�ɱ�ı�ʶ
			Handle_REG(asmInst, index, pair.H, pair.L.Val);
		}
	}
	else
	{
		assert(pair.H.Val >= NULL && pair.H.Val <= SPC_Ux_Mw);
		assert(pair.L.Val >= NULL && pair.L.Val <= SPC_Ux_Mw);
		// ��ȷ��������������ʹ��Ѱַ��ʽ
		OperandState::HandleFunctions[pair.L.Operand](asmInst, index);
		OperandState::HandleFunctions[pair.H.Operand](asmInst, index);
	}
}
void OperandState::Handle_NULL(AsmInstruction* asmInst, int index)
{
	// H��L���п���ѡ�����
}
void OperandState::Handle_L_a(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_b(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_c(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_d(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_dq(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_p(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_pd(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_pi(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_ps(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_q(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_qq(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_s(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_sd(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_ss(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_si(AsmInstruction* asmInst, int index)
{
	// û��ʹ��
}
void OperandState::Handle_L_v(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_w(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_x(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_y(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_L_z(AsmInstruction* asmInst, int index)
{

}


void OperandState::Handle_H_1(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_A(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_B(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_C(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_E(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_F(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_G(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_H(AsmInstruction* asmInst, int index)
{
	// ���Ե����������
}
void OperandState::Handle_H_I(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_J(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_M(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_N(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_O(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_P(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_Q(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_R(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_S(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_U(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_V(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_W(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_X(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_H_Y(AsmInstruction* asmInst, int index)
{

}

// ���������Ҫѡ��һ��Ȼ����ת��ǰ��ĺ���
void OperandState::Handle_SPC_AL_R8L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_CL_R9L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_DL_R10L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_BL_R11L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_AH_R12L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_CH_R13L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_DH_R14L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_BH_R15L(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_AL_rAX(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rAX_r8(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rCX_r9(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rDX_r10(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rBX_r11(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rSP_r12(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rBP_r13(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rSI_r14(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_rDI_r15(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RAX_EAX_R8_R8D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RCX_ECX_R9_R9D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RDX_EDX_R10_R10D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RBX_EBX_R11_R11D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RSP_ESP_R12_R12D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RBP_EBP_R13_R13D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RSI_ESI_R14_R14D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_RDI_EDI_R15_R15D(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ib_Iz(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Mw_Rv(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Rd_Mb(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Rd_Mw(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Rv_Mw(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ry_Mb(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ry_Mw(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Udq_Md(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ux_Md(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ux_Mq(AsmInstruction* asmInst, int index)
{

}
void OperandState::Handle_SPC_Ux_Mw(AsmInstruction* asmInst, int index)
{

}

void OperandState::Handle_SEG(AsmInstruction* asmInst, int index, const RegOrOperand& seg)
{
	// asmInst->opcodeDataWapper.GetSegName((OperandType)seg.Val);
}

void OperandState::Handle_REG(AsmInstruction* asmInst, int index, const RegOrOperand& reg, bool isChange)
{
	auto ot = (OperandType)reg.Val;
	auto tmpReg = reinterpret_cast<RegOrOperand*>(&ot);
	assert(tmpReg->IsReg);
	// GetRegisterName(tmpReg->Reg.Hex, (RegisterLength)tmpReg->Reg.LenType);
	// ѡ��̵ľͰ�tmpReg->Reg.LenType����������

}

// NOTICE: ˳������ö��ֵһ��
const OperandState::HandleFunction OperandState::HandleFunctions[] =
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
