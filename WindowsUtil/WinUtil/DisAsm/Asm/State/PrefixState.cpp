#include "PrefixState.h"
#include "..\Opcode\OpcodeDef.h"
#include "..\AsmStorage.h"

namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Prefix>::Next(AsmStateFactory::ParamType * param)
	{
		auto storage = param->GetStorage();
		auto opcodeDataStorage = storage->GetOpcodeDataStorage();
		//assert(opcodeDataStorage.GetType() == OT_Prefix);
		auto pfxHex = storage->GetCurrentPosition();
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
}  // namespace Disassembler
