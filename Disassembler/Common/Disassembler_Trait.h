#pragma once

namespace Disassembler
{
	// ��Ӧʹ�õ�״̬������ϵ������wapper���͵�
	template<typename TDisassembler>
	struct Disassembler_Trait;
	// typedef ״̬ѡ���ࣨ��֮ǰ�Ĺ����ĳ��������������������ɣ� TStateFactory;
	// typedef ״̬���õ�opcode���Һ�����װ TOpcodeDataWapper;
	// typedef ״̬���õĴ洢�ṹ TStorage;
	// typedef IStateUsed<Disassembler_Trait<���������>> TStateUsed; // �ڲ�ͬ״̬�������������ݵ�����
	
	// ״̬ʹ�����µ�������ʽ��ʹ���ػ��ڹ�����ʹ��
	// template<int stateID>
	// class XXXState;
}  // namespace Disassembler