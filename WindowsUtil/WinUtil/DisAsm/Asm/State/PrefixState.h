#pragma once

#include "AsmState.h"
#include "AsmStateFactory.h"
#include "..\Opcode\OpcodeDef.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Prefix> :public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param)
		{
			auto storage = param->GetStorage();
			auto opcodeDataStorage = storage->GetOpcodeDataStorage();
			//assert(opcodeDataStorage.GetType() == OT_Prefix);
			auto pfxHex = *storage->GetCurrentPosition();
			// �洢��ȡ����ǰ׺
			auto pfxInst = opcodeDataStorage->GetData<PrefixInstData>();
			if (!storage->GetPrefixStorage()->Push(pfxHex, pfxInst))
			{
				// ǰ׺��ͻ
				storage->SetSuccess();
				return AsmStateFactory::State_End;
			}
			return AsmStateFactory::State_Byte;
		}
	};
}  // namespace Disassembler

