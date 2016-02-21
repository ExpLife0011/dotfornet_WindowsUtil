#include "OperandState.h"
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Operand>::Next(AsmStateFactory::ParamType * param)
	{
		auto wapper = param->GetOpcodeDataWapper();
		auto storage = param->GetStorage();
		auto operandGrpStorage = storage->GetOperandGroupStorage();

		auto grpCount = operandGrpStorage->GetOperandCount();

		// ��ʱ�Ķ�ȡλ����ָ��Hex��RM�������Hexǰ
		// ��RM��sib������������Ჽ�������͵ĳ��ȣ�
		// ����ǲ���������Ҫ��¼������ʼ��ַ�����ͳ��Ⱥ����ͣ�����������ʱ�ã�������ָ���͵�����˫���ȸ���ɶ�ģ�
		// ����ǼĴ��������¼regö��ֵ���ɱ䳤�Ļ�ѡ������ȷ�ֳ��ļĴ�����

		for (auto i = 0; i < grpCount; i++)
		{
			// ��ʱOperandInfo�洢���ǲ����������±�
			auto& tmpOperand = wapper->GetOperands(operandGrpStorage->GetOperandInfo(i));
			assert(operandGrpStorage->GetOperandInfoType(i) == OVT_RegOrOperandGroupID);
			ReadOperand(param, i, tmpOperand);
			assert(operandGrpStorage->GetOperandInfoType(i) != OVT_RegOrOperandGroupID);
		}

		storage->SetSuccess();
		return AsmStateFactory::State_PreEnd;
	}
	void AsmState<AsmStateFactory::State_Operand>::ReadOperand(
		AsmStateFactory::ParamType * param,
		int index,
		const RegOrOperandGroup & pair)
	{
		// ֻ��H�ſ���Ϊreg
		if (pair.H.IsReg)
		{
			// ��Ϊ�μĴ��������reg��һ������Ҫ��һ��
			if (param->GetOpcodeDataWapper()->IsSeg(pair.H.Val))
			{
				// LΪNULL������
				assert(pair.L.Val == NULL);
				Handle_SEG(param, index, pair.H);
			}
			else
			{
				// ��reg����ϵ�L����ҪôΪNULL��ҪôΪCHANGE_REG������ֱ������ָʾ�Ƿ���Ը��ݴ�С�ɱ�ı�ʶ
				Handle_REG(param, index, pair.H, pair.L.Val);
			}
		}
		else
		{
			assert(pair.H.Val >= NULL && pair.H.Val <= SPC_Ux_Mw);
			assert(pair.L.Val >= NULL && pair.L.Val <= SPC_Ux_Mw);
			// ��ȷ��������������ʹ��Ѱַ��ʽ
			Self::HandleFunctions[pair.L.Operand](param, index);
			Self::HandleFunctions[pair.H.Operand](param, index);
		}
	}
	void AsmState<AsmStateFactory::State_Operand>::SetOperandInfo(
		AsmStateFactory::ParamType* param,
		int index,
		const unsigned char* convertTable,
		OperandValueType type = OVT_Integer)
	{
		auto storage = param->GetStorage();
		auto oprandStorage = storage->GetOperandGroupStorage();
		auto opSizeAttr = oprandStorage->GetOperandSizeAttribute() - 1;
		oprandStorage->SetOperandInfo(index, convertTable[opSizeAttr]);
		oprandStorage->SetOperandInfoType(index, type);
	}
	void AsmState<AsmStateFactory::State_Operand>::SetOperandInfo(
		AsmStateFactory::ParamType* param,
		int index,
		unsigned char val,
		OperandValueType type = OVT_Integer)
	{
		auto storage = param->GetStorage();
		auto oprandStorage = storage->GetOperandGroupStorage();
		oprandStorage->SetOperandInfo(index, val);
		oprandStorage->SetOperandInfoType(index, type);

	}
	unsigned char AsmState<AsmStateFactory::State_Operand>::defaultSizeConvert[] =
	{ BIT_SIZE(WORD), BIT_SIZE(DWORD), BIT_SIZE(DWORD64) };

	// FIX: ע�⣡��û���ҵ��ڲ�ͬ�Ĵ�С������ѡ����ֳ��ȵ����������ڻ���Ҫ���ĵ����޸�����ĳ���ѡ��
	void AsmState<AsmStateFactory::State_Operand>::Handle_NULL(AsmStateFactory::ParamType * param, int index)
	{
		auto storage = param->GetStorage();
		storage->GetOperandGroupStorage()->SetOperandInfoType(index, OVT_NotSet);
	}
	unsigned char AsmState<AsmStateFactory::State_Operand>::l_a_SizeConvert[] =
	{ BIT_SIZE(WORD) * 2, BIT_SIZE(DWORD) * 2, BIT_SIZE(DWORD) * 2 };

	void AsmState<AsmStateFactory::State_Operand>::Handle_L_a(AsmStateFactory::ParamType * param, int index)
	{
		assert(MaxConvertTableSize == sizeof(l_a_SizeConvert));
		SetOperandInfo(param, index, l_a_SizeConvert);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_b(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(unsigned char));
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_c(AsmStateFactory::ParamType * param, int index)
	{
		// Ŀǰ����û�в�����ʹ��
		assert(false);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_d(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD));
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_dq(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD64) * 2);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_p(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 32λ��48λ����80λ��ָ�룬ȡ���ڲ�������С���ԡ�
		// SetOperandInfo(param, index,?,OVT_Pointer);

	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_pd(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 128λ��256λ����˫���ȸ�������
		// SetOperandInfo(param, index,?,OVT_Double);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_pi(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: QWORD MMX�Ĵ�������mm0��
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_ps(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 128λ��256λ���������ȸ�������
		// SetOperandInfo(param, index,?,OVT_Float);

	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_q(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD64));
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_qq(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(DWORD64) * 4);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_s(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: 6�ֽڻ�10�ֽڵ�α������
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_sd(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, 128,OVT_DoubleScalar);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_ss(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, 128, OVT_FloatScalar);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_si(AsmStateFactory::ParamType * param, int index)
	{
		// û��ʹ��
		assert(false);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_v(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, defaultSizeConvert);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_w(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, BIT_SIZE(WORD));
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_x(AsmStateFactory::ParamType * param, int index)
	{
		// TODO: ����dq��qq�Ĳ�������С����
	}
	
	unsigned char AsmState<AsmStateFactory::State_Operand>::l_y_SizeConvert[] =
	{ BIT_SIZE(DWORD), BIT_SIZE(DWORD), BIT_SIZE(DWORD64) };

	void AsmState<AsmStateFactory::State_Operand>::Handle_L_y(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, l_y_SizeConvert);
	}

	unsigned char AsmState<AsmStateFactory::State_Operand>::l_z_SizeConvert[] =
	{ BIT_SIZE(WORD), BIT_SIZE(DWORD), BIT_SIZE(DWORD) };
	void AsmState<AsmStateFactory::State_Operand>::Handle_L_z(AsmStateFactory::ParamType * param, int index)
	{
		SetOperandInfo(param, index, l_z_SizeConvert);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_1(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_A(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_B(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_C(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_E(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_F(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_G(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_H(AsmStateFactory::ParamType * param, int index)
	{
		// ���Ե����������
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_I(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_J(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_L(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_M(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_N(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_O(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_P(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_Q(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_R(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_S(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_U(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_V(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_W(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_X(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_H_Y(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_AL_R8L(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_CL_R9L(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_DL_R10L(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_BL_R11L(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_AH_R12L(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_CH_R13L(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_DH_R14L(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_BH_R15L(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_AL_rAX(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rAX_r8(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rCX_r9(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rDX_r10(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rBX_r11(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rSP_r12(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rBP_r13(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rSI_r14(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_rDI_r15(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RAX_EAX_R8_R8D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RCX_ECX_R9_R9D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RDX_EDX_R10_R10D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RBX_EBX_R11_R11D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RSP_ESP_R12_R12D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RBP_EBP_R13_R13D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RSI_ESI_R14_R14D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_RDI_EDI_R15_R15D(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ib_Iz(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Mw_Rv(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Rd_Mb(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Rd_Mw(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Rv_Mw(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ry_Mb(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ry_Mw(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Udq_Md(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ux_Md(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ux_Mq(AsmStateFactory::ParamType * param, int index)
	{}
	void AsmState<AsmStateFactory::State_Operand>::Handle_SPC_Ux_Mw(AsmStateFactory::ParamType * param, int index)
	{}

	void AsmState<AsmStateFactory::State_Operand>::Handle_SEG(AsmStateFactory::ParamType * param, int index, const RegOrOperand & seg)
	{
		//	// asmInst->opcodeDataWapper.GetSegName((OperandType)seg.Val);
	}
	void AsmState<AsmStateFactory::State_Operand>::Handle_REG(AsmStateFactory::ParamType * param, int index, const RegOrOperand & reg, bool isChange)
	{
		//	auto ot = (OperandType)reg.Val;
		//	auto tmpReg = reinterpret_cast<RegOrOperand*>(&ot);
		//	assert(tmpReg->IsReg);
		//	// GetRegisterName(tmpReg->Reg.Hex, (RegisterLength)tmpReg->Reg.LenType);
		//	// ѡ��̵ľͰ�tmpReg->Reg.LenType����������
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