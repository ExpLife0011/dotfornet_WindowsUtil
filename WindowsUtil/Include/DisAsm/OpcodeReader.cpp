#include "OpcodeReader.h"
namespace Asm
{
	OpcodeReader::OpcodeReader(bool is32)
	{
		
		this->is32 = is32;
		table = OneByteTable;
		prefix.Reset();
		currentStat = ReadHex;
	}

	OpcodeReader::~OpcodeReader()
	{

	}

	OpcodeReader::AnalyticFunction OpcodeReader::OpTypeAnalyticFunction[] =
	{
		__OutputNone,
		__AnalyCmd,
		__QueuePrefix,
		__SwitchGroup,
		__SwitchTable,
		__ArraySelection,
		__SwitchESC,

		__ReadNextHex,
		__AnalyModRM,
		__AnalySIB,
		__AnalyOffset,
		__AnalyImm

	};

	int OpcodeReader::ReadCode(PUINT8 hex, std::string* output)
	{
		this->code = current = hex;
		//opcode1 = Hex2Opcode(current[0], table);
		tmpStr = output;
		do
		{
			currentStat =  OpTypeAnalyticFunction[currentStat](*this);
		} while (currentStat != AnalyEnd);
		// ���ù��´�ʹ��
		currentStat = ReadHex; 
		table = OneByteTable;
		 return current - code;
	}

	OpcodeReaderStat __ReadNextHex(OpcodeReader & tmpData)
	{
		// �ӵ�ǰ�������ȡopcode����tmpopcode
		tmpData.tmpCode = *Hex2Opcode(*tmpData.current, tmpData.table);
		tmpData.current++;
		// TODO: ����Ҫ�ж϶�ȡ���Ƿ�Ϊrm��sib
		return (OpcodeReaderStat)tmpData.tmpCode.OpType;
	}

	OpcodeReaderStat __AnalyModRM(OpcodeReader & tmpData)
	{
		return OpcodeReaderStat();
	}

	OpcodeReaderStat __AnalySIB(OpcodeReader & tmpData)
	{
		return OpcodeReaderStat();
	}

	OpcodeReaderStat __AnalyOffset(OpcodeReader & tmpData)
	{
		return OpcodeReaderStat();
	}

	OpcodeReaderStat __AnalyImm(OpcodeReader & tmpData)
	{
		return OpcodeReaderStat();
	}

	

	void OpcodeReader::AppendOutput(PSTR str, BYTE sizeOption)
	{
		if (tmpStr)
		{
			tmpStr->append(str);
			// TODO: �жϴ�Сѡ����ʵķ���

		}
	}
	
	// ������������
	void _AnalyOperand(const RegOrOperandGroup& operand, OpcodeReader & tmpData)
	{
	}
	OpcodeReaderStat _AnalyOperand0(const ZeroOperand& cmd, OpcodeReader & tmpData)
	{
		tmpData.AppendOutput((PSTR)InstructionNames[cmd.NameID], cmd.SizeOption);
		
		return AnalyEnd; // ����Ҫ��������Ϣ���������ֱ�ӷ���
	}

	OpcodeReaderStat _AnalyOperand1(const OneOperand& cmd, OpcodeReader & tmpData)
	{
		tmpData.AppendOutput((PSTR)InstructionNames[cmd.NameID],cmd.SizeOption);
		auto op = Operands[cmd.OperandIndex];
		_AnalyOperand(op, tmpData);////////////
		_AnalyOperand(Operands[cmd.OperandIndex_Ext], tmpData);

		return AnalyEnd;
	}

	OpcodeReaderStat _AnalyOperand2(const TwoOperands& cmd, OpcodeReader & tmpData)
	{
		//tmpData.AppendOutput((PSTR)InstructionNames[Opcode_2[cmd.Index].NameID]);
		// ȷ������������
		// ��������������ֱ���������
		return AnalyEnd;
	}

	OpcodeReaderStat _AnalyOperand3(const ThreeOperands& cmd, OpcodeReader & tmpData)
	{
		//tmpData.AppendOutput((PSTR)InstructionNames[Opcode_3[cmd.Index].NameID]);
		return AnalyEnd;
	}

	OpcodeReaderStat _AnalyOperand4(const FourOperands& cmd, OpcodeReader & tmpData)
	{
		//tmpData.AppendOutput((PSTR)InstructionNames[Opcode_4[cmd.Index].NameID]);
		return AnalyEnd;
	}
	//OpcodeReader::AnalyOperand OpcodeReader::AnalyOperandFunction[]=
	//{
	//	_AnalyOperand0,
	//	_AnalyOperand1,
	//	_AnalyOperand2,
	//	_AnalyOperand3,
	//	_AnalyOperand4
	//};
	//
	bool IsOpcodeDefine(Superscripts s, OpcodeReader& tmpData)
	{
		if (s==S_o64)
		{
			return !tmpData.is32;
		}
		if (s==S_i64)
		{
			return tmpData.is32;
		}

		return true;
	}

	OpcodeReaderStat __OutputNone(OpcodeReader & tmpData)
	{
		tmpData.AppendOutput("???");
		//tmpData.current++;
		return AnalyEnd;
	}

	OpcodeReaderStat __AnalyCmd(OpcodeReader & tmpData)
	{
		// �����Ǽ���ϱ꣬�ж���Ŀ��ϵͳ��û�ж������ָ��
#define CHECK_OPCODE_DEFINE(opcount) \
	{\
		auto opcodeInfo = Opcode_##opcount[cmd.Index];\
		if (!IsOpcodeDefine((Superscripts)opcodeInfo.Superscript,tmpData))return OpNone;\
		return _AnalyOperand##opcount(opcodeInfo, tmpData);\
	}
		// ����Ƿ�Ϸ�
		auto cmd = tmpData.tmpCode.Command;
		

		assert(cmd.OpCount >= 0 && cmd.OpCount <= 4);
		switch (cmd.OpCount)
		{
		case 0:
			CHECK_OPCODE_DEFINE(0);
		case 1:
			CHECK_OPCODE_DEFINE(1);
		case 2:
			CHECK_OPCODE_DEFINE(2);
		case 3:
			CHECK_OPCODE_DEFINE(3);
		case 4:
			CHECK_OPCODE_DEFINE(4);

		default:
			break;
		}
		return AnalyEnd;
	}

	OpcodeReaderStat __QueuePrefix(OpcodeReader & tmpData)
	{
		// ������ֳ�ͻ��ת�����
		// ������Ӽ�����ȡ
		auto tmpPrefix = tmpData.tmpCode.Prefix;
		auto prefixOutput = tmpData.prefix.Push(tmpPrefix);
		if (prefixOutput)
		{
			// ǰ׺���ͻ,��ʱ�ѳ��ӵ�����ͻ��״̬�����ݷ��ص���ֵ�趨��ǰ��ͷ����ͷ֮ǰ��ǰ׺��ʾ��ͻ��ǰ׺���
			//tmpData.current += prefixOutput;
			// �����ͻǰ׺
			auto conflict = tmpData.prefix.ConflictQueues;
			do
			{
				auto conflictPrefix = conflict.front();				
				tmpData.AppendOutput((PSTR)InstructionNames[Opcode_Prefixs[conflictPrefix.Index].NameID]);
				conflict.pop();
			} while (conflict.empty());
			return AnalyEnd; // ��ʱǰ׺���п��ܻ�����ֵ,�ڶ�ȡ��cmdʱ���
		}
		else
		{
			return ReadHex;
		}
		
	}

	OpcodeReaderStat __SwitchGroup(OpcodeReader & tmpData)
	{
		return ReadHex;
	}

	OpcodeReaderStat __SwitchTable(OpcodeReader & tmpData)
	{
		// �л�������
		tmpData.table = (Tables)tmpData.tmpCode.Table.Index;
		//tmpData.current++;
		return ReadHex;
	}

	OpcodeReaderStat __ArraySelection(OpcodeReader & tmpData)
	{
		// �ж�ǰ׺
		// �ɹ���ȡ��ת��cmd���̣�ʧ�����???
		return ReadHex;
	}

	OpcodeReaderStat __SwitchESC(OpcodeReader & tmpData)
	{
		return ReadHex;
	}

}
