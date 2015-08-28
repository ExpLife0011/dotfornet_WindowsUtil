#pragma once
#include <Windows.h>
#include <WinBase.h>
#include "PrefixQueue.h"
#include "OpcodeTables.h"
#include <string>
// TODO: ��ʱ��һ��
namespace Asm
{
	
	// ��״̬����ȡ����hex������ֵȡoptype�ģ�����ת��
	enum OpcodeReaderStat
	{
		OpNone = OT_None, // ����δ����
		OpCommand = OT_Command, // ����ָ��
		OpPrefix = OT_Prefix, // ����ǰ׺
		OpGroup = OT_Group, // ������
		OpTable = OT_Table, // �����л���
		OpArray = OT_Array, // ������ָ����
		OpEsc = OT_ESC, // ����Э������ָ��
		ReadHex, // ��hex
		ReadModRM,
		ReadSIB,
		ReadOffset,
		ReadImm,
		AnalyEnd // ����ָ����ϣ�����������ַ���
	};

	using std::string;
	class OpcodeReader
	{
		
	public:
		OpcodeReader( bool is32=true);
		~OpcodeReader();
		// ���ض�ȡ��ָ���
		int ReadCode(PUINT8 hex, string* output = NULL);
		// TODO: ��ȡʱ���ǰ׺���У�ǰ׺��ͻ����ʶ������ݣ���Ϊ��û������һ��ָ�����Բ����ظ���ȡ
	private:
		PUINT8 code; // ��ͷ��ʼλ��
		PUINT8 current; // ��ͷ

		OpcodeReaderStat currentStat; 
		Tables table; // ��ǰ��ȡ�ı�
		Opcode tmpCode; // ��״̬���õĵ�ǰ��Ҫ�����ָ��
		string* tmpStr; // ��״̬���õ�����ַ���
		bool is32; // 32 or 64


		Asm::PrefixQueue prefix;
	
		ModRM mod;
		ModRM sib;

		void AppendOutput(PSTR str, BYTE sizeOption = 0);
		
		//typedef OpcodeReaderStat(*AnalyOperand)(OpcodeCommand& cmd, OpcodeReader & tmpData);

		friend OpcodeReaderStat _AnalyOperand0(const ZeroOperand& cmd, OpcodeReader & tmpData);
		friend OpcodeReaderStat _AnalyOperand1(const OneOperand& cmd, OpcodeReader & tmpData);
		friend OpcodeReaderStat _AnalyOperand2(const TwoOperands& cmd, OpcodeReader & tmpData);
		friend OpcodeReaderStat _AnalyOperand3(const ThreeOperands& cmd, OpcodeReader & tmpData);
		friend OpcodeReaderStat _AnalyOperand4(const FourOperands& cmd, OpcodeReader & tmpData);
		//static AnalyOperand AnalyOperandFunction[];

		typedef OpcodeReaderStat(*AnalyticFunction)(OpcodeReader& tmpData);

		// ״̬��
		friend OpcodeReaderStat __OutputNone(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalyCmd(OpcodeReader& tmpData);
		friend OpcodeReaderStat __QueuePrefix(OpcodeReader& tmpData);
		friend OpcodeReaderStat __SwitchGroup(OpcodeReader& tmpData);
		friend OpcodeReaderStat __SwitchTable(OpcodeReader& tmpData);
		friend OpcodeReaderStat __ArraySelection(OpcodeReader& tmpData);
		friend OpcodeReaderStat __SwitchESC(OpcodeReader& tmpData);

		friend OpcodeReaderStat __ReadNextHex(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalyModRM(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalySIB(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalyOffset(OpcodeReader& tmpData);
		friend OpcodeReaderStat __AnalyImm(OpcodeReader& tmpData);
		
		static AnalyticFunction OpTypeAnalyticFunction[];

		friend void  _AnalyOperand(const RegOrOperandGroup& operand, OpcodeReader& tmpData);
		friend bool IsOpcodeDefine(Superscripts s, OpcodeReader& tmpData);
		


		/* L_a = 1  2word��2dword�ڴ�����������ݲ��������Ծ���*/
		/* L_b byte��������*/
		/* L_c byte|word ���Ծ���*/
		/* L_d dword����*/
		/* L_dq dqword��8�֣�*/
		/* L_p 32 48 80λָ�룬���Ծ���*/
		/* L_pd 128 double*/
		/* L_pi 4word mmx*/
		/* L_ps 128 float*/
		/* L_q  qword����*/
		/* L_qq */
		/* L_s 6|10byteα������*/
		/* L_sd */
		/* L_ss 128 float��������*/
		/* L_si dword*/
		/* L_v word dword qword �������ߴ����*/
		/* L_w word����*/
		/* L_x */
		/* L_y */
		/* L_z 16λʱword 32|64Ϊdword*/
		/* H_A  !ModRM,!SIB,addr*/ /*addr imm offset ��������*/
		/* H_B  ��VEXǰ׺ȡ�Ĵ���*/
		/* H_C  ModRM reg=���ƼĴ���cr* */
		/* H_D  ModRM reg=���ԼĴ���dr* */
		/* H_E  +ModRM  reg|addr*/
		/* H_F  flag regs */
		/* H_G  ModRM ѡ��reg�Ƿ�*/
		/* H_H  */
		/* H_I  imm*/
		/* H_J  offset*/
		/* H_L  */
		/* H_M  ModRM mem*/
		/* H_N  ModRM reg=4��mmx*/
		/* H_O  !ModRM��ƫ���ֻ�˫��*/
		/* H_P  ModR/M reg=4��MMX*/
		/* H_Q  +ModRM  mmx���ڴ��ַ*/
		/* H_R  ModRM rm=128xmm*/
		/* H_S  ModRM reg��Ϊ�μĴ���*/
		/* H_U  ModRM rm=xmm*/
		/* H_V  ModRM reg=xmm*/
		/* H_W	+ModRM 128mmx addr*/
		/* H_X  DS:rSI*/
		/* H_Y  ES:rDI*/
		/* HL_Ux  */
		/* HL_Mb */
		/* HL_Md */
		/* HL_Mw */
		/* HL_Mq */
		/* HL_Rd */
		/* HL_Ry */
		/* HL_Udq */
		/* Seg_cs  */
		/* Seg_ds */
		/* Seg_es */
		/* Seg_fs */
		/* Seg_gs */
		/* Seg_ss */
		/* Rex  */
		/* Rex_B */
		/* Rex_X */
		/* Rex_XB */
		/* Rex_R */
		/* Rex_RB */
		/* Rex_RX */
		/* Rex_RXB */
		/* Rex_W */
		/* Rex_WB */
		/* Rex_WX */
		/* Rex_WXB */
		/* Rex_WR */
		/* Rex_WRB */
		/* Rex_WRX */
		/* Rex_WRXB */
		/* Grp_1 = 74	 */

	};
	
	
}