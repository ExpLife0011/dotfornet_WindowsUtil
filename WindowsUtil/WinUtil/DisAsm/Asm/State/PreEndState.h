#pragma once
#include "AsmState.h"
#include "AsmStateFactory.h"
// ������һЩ��β����

namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_PreEnd>:public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param)
		{
			return AsmStateFactory::State_End;
		}
	};
}  // namespace Disassembler
