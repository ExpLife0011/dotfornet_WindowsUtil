#pragma once
#include "..\Common\Common.h"
#include "Opcode\AsmOpcodeWapper.h"

class StateFactory;
class AsmInstruction
	:public Instruction
{
	friend class InitState;
	friend class SibState;
	friend class RmState;
	friend class EscapeState;
	friend class GroupState;
	friend class ParameterState;
	friend class PrefixState;
	friend class ByteState;
	friend class EndState;
	friend class AsmOpcodeWapper;
	_STD shared_ptr<AsmOpcodeWapper> wapper;
	bool isX32;

	// ������״̬����Ҫ���ݵ���ʱ������ֻ������OpcodeData��Ķ�����
	const void* tmpInstData;
	OpcodeType tmpInstType;
	// ȡ��ʱ����ָ��
	template<typename TOpcodeData>
	const TOpcodeData* GetTmpData()
	{
		return static_cast<const TOpcodeData*>(tmpInstData);
	}
	OpcodeType GetTmpInstType();
	void SetTmpData(OpcodeType type, const void* ptr);
	void ClearTmpData();
	// end


	_STD shared_ptr<AsmOpcodeWapper>& GetOpcodeDataWapper();
	bool IsX32();
	// TODO:ȡ�õ�ǰǰ׺�ж�������������ǰ׺��
	int GetCurrentPfxcdt();
	// �Ե�ǰ�α�λ����Ϊ��ʼ��ȡָ���123ָ�������, ������ʾ�����ͣ�ֻ��1(��None��ʾ)��0F��0F38��0F3A��
	OpcodeType ReadInst(OpcodeType table);
	// �ж��Ƿ�ѡ���ָ���ϵ ,��Ҫ�жϵ�ǰ��ȡ����ǰ׺��ϣ�ֻ��66��F2��F3��
	// �ɹ��󷵻�true�����Ӧ���ݴ洢��������ʱ�������������Ϊѡ�񵽵�����
	// ����ʧ�ܷ���false��ʾָ����ڣ�ͬʱGetTmpInstType()ΪNULL
	bool SelectInst(const Hex_Inst& hexInst);
	bool VerifyCondition(Superscript ss, PrefixCondition pfx);
public:
	// ʵ����ʱ���ý���ָ���ֳ���Ĭ��32λ
	explicit AsmInstruction(shared_ptr<StateFactory> factory, bool isX32 = true);

	// ��ʼ��,������ʼ��ȡλ��
	virtual void Init(void* ptr) override;

	~AsmInstruction();

};
