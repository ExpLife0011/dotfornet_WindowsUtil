#pragma once
#include "Common.h"
#include "Disassembler_Trait.h"
namespace Disassembler
{


	// ����Ϊ��Ҫʹ�ô�������ͣ�Disassembler��
	template<typename T, typename TTrait = Disassembler_Trait<T>>
	struct StateFactory
	{
		typedef typename TTrait::TStateUsed ParamType;
		typedef int (*NextStateFunction)(ParamType*);
		
		// ������������Ҫ��д�ĺ���

		/// <summary>
		/// ��ȡ����״̬
		/// </summary>
		/// <param name="stateId">״̬ID</param>
		/// <returns>״̬������ָ��,����0��ʾ�˳�</returns>
		// static NextStateFunction GetStateFunction(unsigned char stateId);

		/// <summary>
		/// ��ȡ״̬���
		/// </summary>
		// static int GetBeginStateID();

		/// <summary>
		/// ��ȡ״̬��ֹID
		/// </summary>
		// static int GetEndStateID();

	};
}  // namespace Disassembler

