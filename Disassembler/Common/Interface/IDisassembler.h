#pragma once
#include "InterfaceDefine.h"
#include "IInstruction.h"
namespace Disassembler
{
	/// <summary>
	/// ���������ӿ�
	/// </summary>
	interface IDisassembler :public Interface
	{
		/// <summary>
		/// ��ָ��λ�õĻ�����ת����ָ��,ת����ɺ���Ҫ��
		/// </summary>
		/// <param name="pos">��������ʼλ��</param>
		/// <returns>���ض�ȡ��ָ��ȣ�0��ʾת��ʧ��</returns>
		virtual unsigned int Parse(void* pos) PURE;

		/// <summary>
		/// ��ȡ���ؽ��
		/// </summary>
		virtual unique_ptr<IInstruction> GetResult() const PURE;

	};
}  // namespace Disassembler
