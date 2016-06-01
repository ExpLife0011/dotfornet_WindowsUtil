#pragma once
#include "AsmState.h"
#include "AsmStateFactory.h"
#include "..\Opcode\OpcodeDef.h"
#include "..\AsmDisassembler.h"
#include "..\AsmStorage.h"
namespace Disassembler
{
	template<>
	class AsmState<AsmStateFactory::State_Byte> :public IState
	{
	public:
		static int Next(AsmStateFactory::ParamType* param);
	private:
		// �Ե�ǰ�α�λ����Ϊ��ʼ��ȡָ���123ָ�
		// ������ʾ�����ͣ�ֻ��1(��None��ʾ)��0F��0F38��0F3A��
		static OpcodeType ReadInst(AsmStateFactory::ParamType* param, OpcodeType table);

		// �ж��Ƿ�ѡ���ָ���ϵ, ���ͨ����洢 ,��Ҫ�жϵ�ǰ��ȡ����ǰ׺��ϣ�ֻ��66��F2��F3��
		// �ɹ��󷵻�true��� OT_Inst\OT_Inst_Change\OT_Prefix\OT_Grp �Ķ�Ӧ����ָ�����opcodeDataStorage
		// ����ʧ�ܷ���false��ʾָ����ڣ�ͬʱGetType()ΪNULL
		// ��switch������ͻ�����������true
		static bool SelectInst(AsmStateFactory::ParamType* param, const Hex_Inst & hexInst);

		// �Ե�ǰ��ȡ������Ϣ��ָ֤���Ƿ����
		// ss��pfx��Ϊָ������
		static bool VerifyCondition(AsmStateFactory::ParamType* param, Superscript ss, PrefixCondition pfx);
		static int OpcodeTypeToStateID(OpcodeType opType);
		
	};

}  // namespace Disassembler