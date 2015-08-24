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
		
		enum NextStat
			{
				Stat_End,
				Stat_ReadHex,
				Stat_ReadRM,
				Stat_ReadSib,
			/*	Stat_SwitchTable,
				Stat_ReadGroup,
				Stat_ReadPrefix,*/
				//Stat_ReadNone,

			};
		class GetOpcodeLen
		{
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
			PUINT8 startPos;
			PUINT8 currentPos;
			int count; // ָ��ȼ���
			bool IsOpcodeExDefine(OpcodeEx& cmd);
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
			NextStat _ReadHex(BYTE hex);
			NextStat _ReadRM(BYTE hex);
			NextStat _ReadSib(BYTE hex);

			NextStat _SwitchTable(OpcodeTables table);
			NextStat _AnalyGroup(BYTE grpIndex);
			NextStat _AnalyPrefix(OpcodePrefixGroup prefixGroup,BYTE hex);
			//NextStat _ReadNone();
			NextStat _AnalyCmd(OpcodeCmd& cmd);
			
			NextStat _AnalyGroup_E(OpcodeGroup_E& grpe);
			NextStat _AnalyEsc(BYTE hex);
			
		};
		
	}
}