#include "AsmStateFactory.h"
#include "AsmState.h"
#include "InitState.h"
#include "ByteState.h"
#include "PreEndState.h"
#include "EscapeState.h"
#include "GroupState.h"
#include "InstructionState.h"
#include "ByteState.h"
#include "OperandState.h"
#include "PrefixState.h"
namespace Disassembler
{

	AsmStateFactory::NextStateFunction AsmStateFactory::stateFunctions[]=
	{
		AsmState<State_Init>::Next,
		AsmState<State_Operand>::Next,
		AsmState<State_Escape>::Next,
		AsmState<State_Group>::Next,
		AsmState<State_Instruction>::Next,
		AsmState<State_Prefix>::Next,
		AsmState<State_Byte>::Next,
		AsmState<State_PreEnd>::Next,
	};
	// FIX: �˴���Ҫ�������ѭ�����ã�����ʲô�������԰��Ǹ�����ȥ�����ֲ���switch
	// ״̬Nextֱ�ӷ��غ����Ļ�NextStateFunction�޷�����
	AsmStateFactory::NextStateFunction AsmStateFactory::GetStateFunction(unsigned char stateId)
	{
		assert(stateId < (sizeof(stateFunctions) / sizeof(NextStateFunction)));
		return stateFunctions[stateId];
	}

}  // namespace Disassembler

