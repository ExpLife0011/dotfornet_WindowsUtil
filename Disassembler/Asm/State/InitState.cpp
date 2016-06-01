#include "InitState.h"
// ��������״̬��Byte
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Init>::Next(AsmStateFactory::ParamType * param)
	{
		auto storage = param->GetStorage();
		storage->Clear();
		return AsmStateFactory::State_Byte;
	}
}  // namespace Disassembler