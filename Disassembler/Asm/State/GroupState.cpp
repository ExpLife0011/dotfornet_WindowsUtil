#include "GroupState.h"
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Group>::Next(AsmStateFactory::ParamType * param)
	{
		// TODO: ��û¼��, ������Ҫ��״̬
		assert(false);
		return AsmStateFactory::State_PreEnd;
	}
}  // namespace Disassembler
