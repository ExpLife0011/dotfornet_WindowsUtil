#pragma once
#include "..\Common\Storage.h"
#include "Opcode\OpcodeDef.h"
#include <queue>
namespace Disassembler
{
	// ������ʱ�洢һЩ����
	class IInstructionStorage
	{
	public:
		IInstructionStorage()
		{
		}

		virtual ~IInstructionStorage()
		{
		}
		virtual void Clear() = 0;
		virtual bool IsEmpty() = 0;
	};

	class OperandGroupStorage :public IInstructionStorage
	{
	public:
		OperandGroupStorage()
		{
		}

		~OperandGroupStorage()
		{
		}
		virtual bool IsEmpty() override
		{
			return operandCount == 0 && operandGrp == NULL;
		}
		virtual void Clear() override
		{
			SetOperandGrp(0, NULL);
		}
		void SetOperandGrp(unsigned char count, const unsigned char* grp)
		{
			operandCount = count;
			operandGrp = grp;
		}
		const unsigned char* GetOperandGrp() const
		{
			return operandGrp;
		}
		unsigned char GetOperandCount() const
		{
			return operandCount;
		}
	private:
		// �����Ƕ�ȡ��������Ҫ��¼����Ϣ
		const unsigned char* operandGrp;
		unsigned char operandCount;
	};

	class OpcodeDataStorage :public IInstructionStorage
	{
	public:
		OpcodeDataStorage()
		{
		}

		~OpcodeDataStorage()
		{
		}
		// ȡ��ʱ����ָ��,�±�Ϊ��Ӧ����
		// OT_Inst - InstData
		// OT_Inst_Change - InstChangeData
		// OT_Prefix - PrefixInstData
		// OT_Grp - GrpInstData
		// OT_Table_0F - ��
		// OT_Table_0F38 - ��
		// OT_Table_0F3A - ��
		// OT_Esc - ��
		template<typename TOpcodeData>
		const TOpcodeData* GetData()
		{
			return reinterpret_cast<const TOpcodeData*>(tmpInstData);
		}
		void SetData(OpcodeType type, const void* ptr)
		{
			tmpInstType = type;
			tmpInstData = ptr;
		}
		OpcodeType GetType()
		{
			return tmpInstType;
		}
		virtual void Clear() override
		{
			tmpInstType = OT_None;
			tmpInstData = NULL;
		}
		virtual bool IsEmpty() override
		{
			return tmpInstType == OT_None && tmpInstData == NULL;
		}
	private:
		// ������״̬����Ҫ���ݵ���ʱ������ֻ������OpcodeData��Ķ�����
		const void* tmpInstData;
		OpcodeType tmpInstType;
	};

	class NameStorage :public IInstructionStorage
	{
	public:
		NameStorage()
		{
		}

		~NameStorage()
		{
		}
		void SetInstName(LPCSTR name)
		{
			// ��ʱ���ӵ�ָ����������ֻѡ���һ��
			instName = name;
		}

		virtual void Clear() override
		{
			instName = NULL;
			nameExt = Ext_None;
		}
		virtual bool IsEmpty() override
		{
			return nameExt == Ext_None && instName == NULL;
		}
	private:
		// ���ָ����ָ��洢������
		LPCSTR instName;
		// ���ݳ�������ѡ������ֺ�׺�ַ����������ɾ����
		NameExt nameExt;
	};

	struct PrefixInstData_Hex_Pair
	{
		const PrefixInstData* PfxData;
		unsigned char Hex;
		PrefixInstData_Hex_Pair(unsigned char hex, const PrefixInstData* pfxData)
			:Hex(hex), PfxData(pfxData)
		{

		}
	};
	class PrefixStorage :public IInstructionStorage
	{
	public:
		PrefixStorage()
		{
		}

		~PrefixStorage()
		{
		}
		// �����Ƿ����push���洢��
		// false����Ϊǰ׺���ͻ����Ҫ��ն���
		bool Push(unsigned char hex, const PrefixInstData* pfxData)
		{
			// �жϳ�ͻ
			if (hasGrp[pfxData->PfxGrp])
			{
				return false;
			}
			if (isEmpty)
			{
				isEmpty = false;
			}
			hasPfx[hex] = true;
			hasGrp[pfxData->PfxGrp] = true;

			// �洢ǰ׺
			pfxQueue.push(make_unique<PrefixInstData_Hex_Pair>(hex, pfxData));
			return true;
		}
		virtual void Clear() override
		{
			isEmpty = true;
			pfxQueue.swap(_STD queue<unique_ptr<PrefixInstData_Hex_Pair>>());

			memset(hasGrp, false, sizeof(hasGrp));
			memset(hasPfx, false, sizeof(hasPfx));
		}
		virtual bool IsEmpty() override
		{
			return isEmpty;
		}
		bool HasPrefix(Prefix pfx)
		{
			return hasPfx[pfx];
		}

		// ȡ�õ�ǰǰ׺�ж�������������ǰ׺,ֻ��66��f2��f3��ʶ��
		unsigned char GetCurrentPfxcdt() const
		{
			return (hasPfx[G3_operand_size] ? C_66 : 0) |
				(hasPfx[G1_repne_xacquire] ? C_F2 : 0) |
				(hasPfx[G1_reprepe_xrelease] ? C_F3 : 0);
		}
	private:
		_STD queue<unique_ptr<PrefixInstData_Hex_Pair>> pfxQueue;
		bool isEmpty;
		PrefixCondition pfxcdt;
		bool hasGrp[PfxGrp_End];
		bool hasPfx[0x100];  // ֻ�õ�ǰ׺��Ӧhex�±��Ԫ��
	};

	// ��Ҫ�Ĵ洢��
	class AsmStorage :public StorageBase
	{
	public:

		AsmStorage();

		void SetX32(bool is32);
		bool IsX32() const;
		OperandGroupStorage* GetOperandGroupStorage();
		OpcodeDataStorage* GetOpcodeDataStorage();
		NameStorage* GetNameStorage();
		PrefixStorage* GetPrefixStorage();
		virtual void Clear() override;
	private:
		OperandGroupStorage operandGrpStorage;
		OpcodeDataStorage opcodeDataStorage;
		NameStorage nameStorage;
		PrefixStorage prefixStorage;
		bool isX32;


	};
}  // namespace Disassembler
