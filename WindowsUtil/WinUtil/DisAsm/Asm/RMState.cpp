#include "..\Common\Common.h"
#include "StateFactory.h"
// ���������������ʽ������
// ����ת��End��Operand��Sib
const State* RmState::Next(const shared_ptr<Instruction>& inst) const 
{ 
	auto asmInst = inst->Cast<AsmInstruction>();
	
	// TODO: ��������Prefix������������Ҫ��Ūһ�����Է���ת�ַ����ı�
	return NULL;
}
