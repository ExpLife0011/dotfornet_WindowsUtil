#pragma once
#include <Windows.h>
#include "../../Common/Common.h"
#include "OpcodeDef.h"

namespace Disassembler
{
	// OpcodeData��װ
	class AsmOpcodeDataWrapper
	{
	public:
		AsmOpcodeDataWrapper();

		~AsmOpcodeDataWrapper();
		/// <summary>
		/// ��ѹOpcodeData��
		/// </summary>
		/// <param name="zipArray">ѹ���������</param>
		/// <param name="count">���鳤��</param>
		/// <returns>��ѹ��ı���Byte1��Byte2ͬ�ṹ</returns>
		static _STD unique_ptr<OpcodeData[]> UnzipOpcodeData(const ZipOpcodeData zipArray[], int count);

		/// <summary>
		/// ȡ���������
		/// </summary>
		/// <param name="opCount">����������</param>
		/// <param name="index">������ID</param>
		/// <returns>��������ϣ���RegOrOperandGroup����±���ϣ�����ΪopCount</returns>
		const unsigned char* GetOperandGroup(int opCount, int index) const;

		/// <summary>
		/// �жϲ����Ƿ���OperandTypeö���ж���ΪSEG
		/// </summary>
		bool IsSeg(unsigned char val) const;


		/// <summary>
		/// ȡָ���
		/// </summary>
		/// <param name="tableType">
		/// <para><paramref name="tableType"/>��ȡֵ�ʹ���ʽ���£�</para>
		/// <para>OT_Table_0F:ȡ2�ֽڱ�</para>
		/// <para>OT_Table_0F38:ȡ3�ֽ�38��</para>
		/// <para>OT_Table_0F3A:ȡ3�ֽ�3A��</para>
		/// <para>����:ȡ1�ֽڱ�</para>
		/// </param>
		/// <param name="hex">��ID��ָ�������</param>
		/// <returns>ָ���Ԫ�أ����ܻ�ָ����ָ��</returns>
		const OpcodeData& GetOpcodeData(OpcodeType tableType, int hex);

		/// <summary>
		/// ȡ�ֽ�-ָ���Ӧ��ϵ��
		/// </summary>
		/// <param name="index">OpcodeData��¼���±�</param>
		/// <returns>�ֽ�-ָ���Ӧ��ϵ</returns>
		const Hex_Inst& GetHex_Inst(int index) const;

		/// <summary>
		/// ȡָ��-���Ӧ��ϵ��
		/// </summary>
		/// <param name="index">Hex_Inst��¼���±�</param>
		/// <returns>ָ��-���Ӧ��ϵ</returns>
		const GrpInstData& GetGrpInst(int index) const;

		/// <summary>
		/// ȡǰ׺��
		/// </summary>
		/// <param name="index">Hex_Inst��¼���±�</param>

		const PrefixInstData& GetPfxInst(int index) const;

		/// <summary>
		/// ȡָ�������׺�ַ�����
		/// </summary>
		/// <param name="index">Hex_Inst��¼���±�</param>
		const InstChangeData& GetInstChange(int index) const;

		/// <summary>
		/// ȡָ���
		/// </summary>
		/// <param name="index">Hex_Inst��¼���±�</param>
		const InstData& GetInst(int index) const;

		/// <summary>
		/// ȡ������
		/// </summary>
		/// <param name="index">ͨ��GetOperandGroupȡ��</param>
		const RegOrOperandGroup& GetOperands(int index) const;

		/// <summary>
		/// ȡָ������
		/// </summary>
		/// <param name="index">ָ��ṹ�м�¼������ID</param>
		const LPCSTR& GetInstructionNames(int index) const;

		/// <summary>
		/// ȡ�Ĵ�������
		/// </summary>
		const char* GetRegisterName(OperandType reg) const;

		/// <summary>
		/// ȡ�μĴ�������
		/// </summary>
		const char* GetSegName(OperandType seg) const;

		// [REX.W Prefix] 32λ�²���
		// [Operand Prefix Is Present]
		// [Address Prefix Is Present]
		// [Effective Operand Size/Effective Address Size]
		// ��Ϊ���������ַ��С������ʱ����һ���õģ����Է���ָ�룬��EffectiveSizeIndexƫ��ȡ���Ե�ֵ
		const SizeAttribute* FindSizeAttribute(bool is32, bool hasRexW, bool hasOPfx, bool hasAPfx) const;
	private:
		unique_ptr<OpcodeData[]> table0F38;
		unique_ptr<OpcodeData[]> table0F3A;
		AsmOpcodeDataWrapper(const AsmOpcodeDataWrapper& obj) = delete;
	};

}  // namespace Disassembler

