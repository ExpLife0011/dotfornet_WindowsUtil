#pragma once

#include "AsmState.h"
#include "AsmStateFactory.h"
#include "..\Opcode\OpcodeDef.h"
#include "..\Opcode\AsmOpcodeDataWapper.h"
#include "..\AsmStorage.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Operand> :public IState
	{
	public:
		typedef AsmState<AsmStateFactory::State_Operand> Self;
		static int Next(AsmStateFactory::ParamType* param)
		{
			auto wapper = param->GetOpcodeDataWapper();
			auto storage = param->GetStorage();
			auto operandGrpStorage = storage->GetOperandGroupStorage();

			auto operandGrp = operandGrpStorage->GetOperandGrp();
			auto grpCount = operandGrpStorage->GetOperandCount();

			// ��ʱ�Ķ�ȡλ����ָ��Hex��RM�������Hexǰ
			// ��RM��sib������������Ჽ�������͵ĳ��ȣ�
			// ����ǲ���������Ҫ��¼������ʼ��ַ�����ͳ��Ⱥ����ͣ�����������ʱ�ã�������ָ���͵�����˫���ȸ���ɶ�ģ�
			// ����ǼĴ��������¼regö��ֵ���ɱ䳤�Ļ�ѡ������ȷ�ֳ��ļĴ�����
			// TODO: ��Ҫȷ���ô洢ʲô���ݣ�Dflag��ô�õ�

			for (auto i = 0; i < grpCount; i++)
			{
				auto& tmpOperand = wapper->GetOperands(operandGrp[i]);
				ReadOperand(param, i, tmpOperand);
			}

			storage->SetSuccess();
			return AsmStateFactory::State_PreEnd;
		}
	private:
		static void ReadOperand(AsmStateFactory::ParamType* param, int index, const RegOrOperandGroup& pair)
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

		typedef void(*HandleFunction)(AsmStateFactory::ParamType*, int);
		static void Handle_NULL(AsmStateFactory::ParamType* param, int index);

		static void Handle_L_a(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_b(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_c(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_d(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_dq(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_p(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_pd(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_pi(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_ps(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_q(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_qq(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_s(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_sd(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_ss(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_si(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_v(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_w(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_x(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_y(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_L_z(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_1(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_A(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_B(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_C(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_D(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_E(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_F(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_G(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_H(AsmStateFactory::ParamType* param, int index)
		{
			// ���Ե����������
		}
		static void Handle_H_I(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_J(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_L(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_M(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_N(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_O(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_P(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_Q(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_R(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_S(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_U(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_V(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_W(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_X(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_H_Y(AsmStateFactory::ParamType* param, int index) {}

		static void Handle_SPC_AL_R8L(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_CL_R9L(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_DL_R10L(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_BL_R11L(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_AH_R12L(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_CH_R13L(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_DH_R14L(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_BH_R15L(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_AL_rAX(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_rAX_r8(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_rCX_r9(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_rDX_r10(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_rBX_r11(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_rSP_r12(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_rBP_r13(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_rSI_r14(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_rDI_r15(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_RAX_EAX_R8_R8D(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_RCX_ECX_R9_R9D(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_RDX_EDX_R10_R10D(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_RBX_EBX_R11_R11D(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_RSP_ESP_R12_R12D(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_RBP_EBP_R13_R13D(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_RSI_ESI_R14_R14D(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_RDI_EDI_R15_R15D(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Ib_Iz(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Mw_Rv(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Rd_Mb(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Rd_Mw(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Rv_Mw(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Ry_Mb(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Ry_Mw(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Udq_Md(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Ux_Md(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Ux_Mq(AsmStateFactory::ParamType* param, int index) {}
		static void Handle_SPC_Ux_Mw(AsmStateFactory::ParamType* param, int index) {}

		// change��ʶ�ϲ���reg
		static void Handle_SEG(AsmStateFactory::ParamType* param, int index, const RegOrOperand& seg)
		{
			//	// asmInst->opcodeDataWapper.GetSegName((OperandType)seg.Val);
		}
		static void Handle_REG(AsmStateFactory::ParamType* param, int index, const RegOrOperand& reg, bool isChange)
		{
			//	auto ot = (OperandType)reg.Val;
			//	auto tmpReg = reinterpret_cast<RegOrOperand*>(&ot);
			//	assert(tmpReg->IsReg);
			//	// GetRegisterName(tmpReg->Reg.Hex, (RegisterLength)tmpReg->Reg.LenType);
			//	// ѡ��̵ľͰ�tmpReg->Reg.LenType����������
		}
		static const HandleFunction HandleFunctions[];
	};



}  // namespace Disassembler

