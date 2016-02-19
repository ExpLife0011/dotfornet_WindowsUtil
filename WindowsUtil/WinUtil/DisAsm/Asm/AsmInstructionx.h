//#pragma once
//#include "..\Common\Common.h"
//#include "Opcode\AsmOpcodeDataWapper.h"

//
//
//
//class StateFactory;
//// �����洢״̬��תʱ��һЩ�м����
//class AsmInstruction
//	:public Instruction
//{
//	friend class InitState;
//	friend class EscapeState;
//	friend class GroupState;
//	friend class InstructionState;
//	friend class PrefixState;
//	friend class ByteState;
//	friend class EndState;
//	friend class OperandState;
//	friend class AsmOpcodeDataWapper;
//private:
//	AsmOpcodeDataWapper opcodeDataWapper;
//	const AsmOpcodeDataWapper* GetOpcodeDataWapper() const;
//
//	bool isX32;
//	bool IsX32() const;
//
//	OperandGroupStorage operandGrpStorage;
//	OpcodeDataStorage opcodeDataStorage;
//	NameStorage nameStorage;
//	PrefixStorage prefixStorage;
//
//
//
//
//	// �Ե�ǰ�α�λ����Ϊ��ʼ��ȡָ���123ָ�������,
//	// ������ʾ�����ͣ�ֻ��1(��None��ʾ)��0F��0F38��0F3A��
//	OpcodeType ReadInst(OpcodeType table);
//
//	// �ж��Ƿ�ѡ���ָ���ϵ, ���ͨ����洢 ,��Ҫ�жϵ�ǰ��ȡ����ǰ׺��ϣ�ֻ��66��F2��F3��
//	// �ɹ��󷵻�true��� OT_Inst\OT_Inst_Change\OT_Prefix\OT_Grp �Ķ�Ӧ����ָ�����opcodeDataStorage
//	// ����ʧ�ܷ���false��ʾָ����ڣ�ͬʱGetType()ΪNULL
//	// ��switch������ͻ�����������true
//	bool SelectInst(const Hex_Inst& hexInst);
//
//	// �Ե�ǰ��ȡ������Ϣ��ָ֤���Ƿ����
//	bool VerifyCondition(Superscript ss, PrefixCondition pfx) const;
//
//	// �Ƿ��¼��ȡ�����ַ�����Ϣ(�ȳ��������¼��Ϣ��������һ�����)
//	bool needOutput;
//	bool IsNeedOutput() const;
//
//
//public:
//	// ʵ����ʱ��isX32���ý���ָ���ֳ�, 
//	// needOutput��ʾ�Ƿ�����������Ϊ�ַ��������Ϊfalse��ֻ�����ָ��ȣ������м����ݶ��������
//	explicit AsmInstruction(const shared_ptr<StateFactory>& factory, bool isX32, bool needOutput);
//
//	~AsmInstruction();
//
//};
