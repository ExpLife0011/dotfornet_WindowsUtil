#include "EscapeState.h"
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Escape>::Next(AsmStateFactory::ParamType * param)
	{
		// TODO: ��û¼��, ������Ҫ��״̬
		return AsmStateFactory::State_PreEnd;
	}
}  // namespace Disassembler
