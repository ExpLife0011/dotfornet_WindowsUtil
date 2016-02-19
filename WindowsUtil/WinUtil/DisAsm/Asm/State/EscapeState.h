#pragma once

#include "AsmState.h"
#include "AsmStateFactory.h"
#include "..\AsmInstruction.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Escape>:public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param)
		{
			// TODO: ��û¼��, ������Ҫ��״̬
			return AsmStateFactory::State_PreEnd;
		}
	};
}  // namespace Disassembler

