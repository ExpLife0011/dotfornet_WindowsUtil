#include "InstructionState.h"
#include "..\AsmStorage.h"
#include "..\Opcode\AsmOpcodeDataWapper.h"
namespace Disassembler
{
	int AsmState<AsmStateFactory::State_Instruction>::Next(AsmStateFactory::ParamType * param)
	{
		auto storage = param->GetStorage();
		auto opcodeDataStorage = storage->GetOpcodeDataStorage();
		// �鿴�ϸ�״̬�����ָ������
		auto type = opcodeDataStorage->GetType();
		assert(type == OT_Inst || type == OT_Inst_Change);

		// �����InstChangeData���ýṹ���������ṹ��Ա�������ʹ�С˳�������ͬ
		// InstChangeData�����һ����Ա����������������ֺ�׺�õģ����ﲻ��Ҫ
		auto instData = opcodeDataStorage->GetData<InstData>();
		auto wapper = param->GetOpcodeDataWapper();

		// �������
		auto nameStorage = storage->GetNameStorage();
		nameStorage->SetInstName(wapper->GetInstructionNames(instData->NameID));
		if (type == OT_Inst_Change)
		{
			// ������׺
			auto instChange = reinterpret_cast<const InstChangeData*>(instData);
			// TODO: ��Ҫprefix�������жϲ��������ȴ�ѡ����ѡ������׺��
		}
		// ����޲�����ֱ�ӷ���
		auto operandGrpStorage = storage->GetOperandGroupStorage();
		if (instData->ParamCount == 0)
		{
			operandGrpStorage->SetOperandGrp(0, NULL);
			storage->SetSuccess();
			return AsmStateFactory::State_PreEnd;
		}
		// ���Ҳ��������
		auto operandGrp = wapper->GetOperandGroup(instData->ParamCount, instData->ParamID);
		assert(operandGrp != NULL);
		// �������
		operandGrpStorage->SetOperandGrp(instData->ParamCount, operandGrp);

		// ���ô�С����
		auto pfxStorage = storage->GetPrefixStorage();
		bool is32 = storage->Is32();
		bool hasRexW = pfxStorage->HasRex() ? pfxStorage->GetRex()->W : false;
		bool hasOPfx = pfxStorage->IsOverrideOperandSize();
		bool hasAPfx = pfxStorage->IsOverrideAddressSize();
		auto sizeAttribute = wapper->FindSizeAttribute(is32, hasRexW, hasOPfx, hasAPfx);
		// ��������С
		operandGrpStorage->SetOperandSizeAttribute(sizeAttribute[EffectiveOperand]);
		// ��ַ��С
		operandGrpStorage->SetOperandSizeAttribute(sizeAttribute[EffectiveAddress]);

		return AsmStateFactory::State_Operand;

		// TODO: 
		// ���ڶ���3�ֽ�ָ�������ʣ�66 0F3A 0F C1 08HΪʲô��palignr Vdq, Wdq, Ib
		// ������palignr Pq, Qq, Ib ��vpalignr Vx,Hx,Wx,Ib
		// ����趨����û�м�¼������Vs�Ľ������ʹ����3�����������ǲ�����©����ʲô��
		// ��ǿ��ǰ׺�鵽��Ӧ���ǵ�3����4�������������ٲ�Ҫǰ׺Ҳ�ǵڶ��������Ϊʲô����д���Ǳ���û��¼�ĵ�һ�������
		// TODO: Ū����ǰ�޷����±࣬��ʱ�����ȣ����ܸ�SSE�汾�йأ�H����Ϊ�ɰ治���ڣ��õ�����ͻ������һ����
		// ����4��������ҪVexǰ׺, ������һ�£�64λ����vexǰ׺vs�������������÷����ԡ�64λ�µ�ָ��Ǹ�32λ��һ��

	}
}  // namespace Disassembler
