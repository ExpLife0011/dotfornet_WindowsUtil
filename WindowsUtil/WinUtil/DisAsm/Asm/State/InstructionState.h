#pragma once
// �����ﴦ��ָ��
// ����������ƣ�����ָ����Ϣ������ת����ȡ���������Ƕ�ȡRM
// ����ת��������RM״̬

#include "AsmState.h"
#include "AsmStateFactory.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Instruction> :public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param);
	};
	 
}  // namespace Disassembler

