#include "GroupState.h"
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Group>::Next(AsmStateFactory::ParamType * param)
	{
		// TODO: ��û¼��, ������Ҫ��״̬
		return AsmStateFactory::State_PreEnd;
	}
}  // namespace Disassembler
