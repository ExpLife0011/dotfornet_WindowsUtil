#pragma once
#include <Windows.h>
#include <WinBase.h>
#include "SimpleOpcodeMap.h"
#include <queue>
#include <assert.h>
namespace Process
{
	namespace Hook
	{
		
		
		class GetOpcodeLen
		{
			enum NextStat
			{
				Stat_End,
				Stat_ReadHex,
				Stat_ReadRM,
				Stat_ReadSib
			};
		public:
			GetOpcodeLen(bool is32);
			~GetOpcodeLen();
			void Reset();
			int GetLen(PUINT8 hex);
		private:
			std::queue<OpcodePrefixGroup> prefix;
			bool is32;
			NextStat stat;
			OpcodeTables table;
			PUINT8 currentPos;
			int count; // ָ��ȼ���
			bool IsOpcodeExDefine(OpcodeEx& cmd);
			bool IsPrefixVerify(OpcodePrefixCondition && opc);
			void AddImmCount(OpcodeLenType len);
			bool has66; // �в�������С�л�ǰ׺
			bool has67; // �е�ַ��С�л�ǰ׺
			bool hasF2;
			bool hasF3;

			bool isGroupExist[4];
			// ��ȡ����
			// ��hex����1���ȣ������rm�ٶ�rm
			// ����������
			// ��ȡ��3�֣���1�ֽ�ʱ��ʶ��
			// ��RM����SIB��
			GetOpcodeLen::NextStat _ReadHex(BYTE hex);
			GetOpcodeLen::NextStat _ReadRM(BYTE hex);
			GetOpcodeLen::NextStat _ReadSib(BYTE hex);

			GetOpcodeLen::NextStat _SwitchTable(OpcodeTables table);
			GetOpcodeLen::NextStat _AnalyGroup(BYTE grpIndex);
			GetOpcodeLen::NextStat _AnalyPrefix(OpcodePrefixGroup prefixGroup,BYTE hex);

			GetOpcodeLen::NextStat _AnalyCmd(OpcodeCmd& cmd);
			
			GetOpcodeLen::NextStat _AnalyGroup_E(OpcodeGroup_E& grpe);
			GetOpcodeLen::NextStat _AnalyEsc(BYTE hex);
			
		};
		
	}
}