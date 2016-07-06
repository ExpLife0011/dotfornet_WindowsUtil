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
		virtual bool IsEmpty() const = 0;
	};

	class OperandGroupStorage :public IInstructionStorage
	{
	public:
		// ���ֻ��4������
		static constexpr int MaxCount = 4;
		OperandGroupStorage()
		{
			isEmpty = true;
		}

		~OperandGroupStorage()
		{
		}
		virtual bool IsEmpty() const override
		{
			// ȡ��������Ҫ�жϲ���������Ϊ0��ʾ��
			return operandCount == 0;
		}
		virtual void Clear() override
		{
			memset(operandInfo, 0, MaxCount);
			memset(operandInfoType, OVT_RegOrOperandGroupID, MaxCount);

			isEmpty = true;
		}
		// �Ȼ����ò�����������
		// ֮������󸲸�Ϊ�����������
		void SetOperandGrp(unsigned char count, const unsigned char* grp)
		{
			assert(grp != NULL);
			assert(count <= MaxCount);
			operandCount = count;
			memcpy_s(operandInfo, MaxCount, grp, count);
		}
		
		unsigned char GetOperandCount() const
		{
			return operandCount;
		}
		SizeAttribute GetOperandSizeAttribute() { return operandSizeAttribute; }
		void SetOperandSizeAttribute(SizeAttribute size) { operandSizeAttribute = size; }
		SizeAttribute GetAddressSizeAttribute() { return addressSizeAttribute; }
		void SetAddressSizeAttribute(SizeAttribute size) { addressSizeAttribute = size; }
		
		
		
		// ʹ��OperandValueType�������֣������ֵ���ͣ���λ��bit
		void SetOperandInfo(int index, unsigned char info)
		{
			assert(index < MaxCount);
			operandInfo[index] = info;
		}
		// ֵ���͵ĵ�λ��bit
		unsigned char GetOperandInfo(int index)
		{
			return operandInfo[index];
		}
		OperandValueType GetOperandInfoType(int index)
		{
			return operandInfoType[index];
		}
		void SetOperandInfoType(int index, OperandValueType type)
		{
			operandInfoType[index] = type;
		}
	private:
		bool isEmpty;
		// �����Ƕ�ȡ��������Ҫ��¼����Ϣ
		//const unsigned char* operandGrp;
		unsigned char operandCount;
		SizeAttribute operandSizeAttribute;
		SizeAttribute addressSizeAttribute;
		// ��������������Ϣ
		// �����REG���͵ģ�ֵΪOperandType��reg���֣�ȥ������ѡ�
		unsigned char operandInfo[MaxCount];
		OperandValueType operandInfoType[MaxCount];
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
			tmpInstData = nullptr;
		}
		virtual bool IsEmpty() const override
		{
			return tmpInstType == OT_None && tmpInstData == nullptr;
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
			instName = nullptr;
			nameExt = Ext_None;

		}
		virtual bool IsEmpty() const override
		{
			return nameExt == Ext_None && instName == nullptr;
		}
		void SetNameExt(NameExt val)
		{
			nameExt = val;
		}
		NameExt GetNameExt() const
		{
			return nameExt;
		}
	private:
		// ���ָ����ָ��洢������
		LPCSTR instName;
		// ���ݳ�������ѡ������ֺ�׺�ַ�
		NameExt nameExt;
	};

	struct PrefixInstData_Hex_Pair
	{
		const PrefixInstData* PfxData;
		const unsigned char* Hex;
		PrefixInstData_Hex_Pair(const unsigned char* hex, const PrefixInstData* pfxData)
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
		bool Push(const unsigned char* hex, const PrefixInstData* pfxData)
		{
			if (HasRex())
			{
				// rexǰ׺������opcodeǰ����׼������ǰ׺����
				return false;
			}
			// �жϳ�ͻ
			if (hasGrp[pfxData->PfxGrp])
			{
				return false;
			}
			if (isEmpty)
			{
				isEmpty = false;
			}

			hasPfx[*hex] = true;
			hasGrp[pfxData->PfxGrp] = true;
			// ����rexǰ׺��ʱȡ��
			if ((unsigned char)pfxData->PfxGrp == PfxGrp_Rex)
			{
				rex = hex;
			}
			// �洢ǰ׺
			pfxQueue.push(make_unique<PrefixInstData_Hex_Pair>(hex, pfxData));
			return true;
		}
		virtual void Clear() override
		{
			isEmpty = true;
			pfxQueue.swap(_STD queue<unique_ptr<PrefixInstData_Hex_Pair>>());
			rex = nullptr;
			memset(hasGrp, false, sizeof(hasGrp));
			memset(hasPfx, false, sizeof(hasPfx));
		}
		virtual bool IsEmpty() const override
		{
			return isEmpty;
		}

		bool HasRex() const
		{
			return hasGrp[PfxGrp_Rex];
		}
		const RexPrefix* GetRex() const
		{
			return reinterpret_cast<const RexPrefix*>(rex);
		}
		bool IsOverrideSegment() const
		{
			return hasGrp[PfxGrp_2];
		}

		bool IsOverrideAddressSize() const
		{
			return hasPfx[G4_address_size];
		}

		bool IsOverrideOperandSize() const
		{
			return hasPfx[G3_operand_size];
		}
		// ʹ�üĴ����Ķ��巵��
		OperandType GetOverrideSegment() const
		{
			if (hasPfx[G2_seg_cs])
			{
				return SEG_CS;
			}
			if (hasPfx[G2_seg_ds])
			{
				return SEG_DS;
			}
			if (hasPfx[G2_seg_es])
			{
				return SEG_ES;
			}
			if (hasPfx[G2_seg_fs])
			{
				return SEG_FS;
			}
			if (hasPfx[G2_seg_gs])
			{
				return SEG_GS;
			}
			if (hasPfx[G2_seg_ss])
			{
				return SEG_SS;
			}
			assert(false);
			return OT_NULL;
		}

		// ȡ�õ�ǰǰ׺�ж�������������ǰ׺,ֻ��66��f2��f3��ʶ��
		unsigned char GetCurrentMandatoryPrefix() const
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
		const unsigned char* rex;
	};

	// ��Ҫ�Ĵ洢��
	class AsmStorage :public StorageBase
	{
	public:

		AsmStorage();

		void SetSizeMode(bool is32)
		{
			is32Bit = is32;
		}

		OperandGroupStorage* GetOperandGroupStorage();
		OpcodeDataStorage* GetOpcodeDataStorage();
		NameStorage* GetNameStorage();
		PrefixStorage* GetPrefixStorage();
		bool Is32() const
		{
			return is32Bit;
		}
		virtual void Clear() override;
	private:
		OperandGroupStorage operandGrpStorage;
		OpcodeDataStorage opcodeDataStorage;
		NameStorage nameStorage;
		PrefixStorage prefixStorage;
		bool is32Bit;



	};


}  // namespace Disassembler
