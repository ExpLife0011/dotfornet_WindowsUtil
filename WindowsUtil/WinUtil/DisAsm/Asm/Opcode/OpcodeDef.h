#pragma once
#include <Windows.h>
#pragma region �������洢�ṹ
#pragma pack(push, 1)
typedef struct
{
	union
	{
		union
		{
			struct
			{
				unsigned char Operand : 7;
				unsigned char IsReg : 1;
			};
			struct
			{
				unsigned char Hex : 4;
				unsigned char LenType : 3;
				unsigned char : 1;
			}Reg;
		};
		unsigned char Val;
	};
}RegOrOperand, *PRegOrOperand;
typedef struct
{
	RegOrOperand H;
	RegOrOperand L;
}RegOrOperandGroup, *PRegOrOperandGroup;
#pragma pack(pop)
#pragma endregion

enum RegisterLength :unsigned char
{
	Len_8,
	Len_16,
	Len_32,
	Len_64,
	Len_64_MM,
	Len_128_XMM
};

// ���α�ʶ����һ�����Լһ�¿ռ�
extern const char Registers[16][6][6];

#define _REG(hex, type) (unsigned char)((1<<7)|(((type)&0x7)<<4)|((hex)&0x0f))

// �Ĵ������壬��Ӧֵ�������ַ��������ҵ�
// ���ĵ�������һ�����ο������ܲ�׼
enum OperandType :unsigned char
{
	OT_NULL = 0,

	// OperandTypes ����������

	// ����WORD������DWORD�ڴ��������ȡ���ڲ�������С���ԣ�ֻ����BOUNDָ���У�
	L_a,  // ֻ��Ma���

	// BYTE�����ܲ�������С����
	L_b,

	// BYTE��WORD��ȡ���ڲ�������С����
	L_c,  // û��ʹ��

	// DWORD�����Ӵ�С����
	L_d,  // ֻ�������RM��Ѱַ��ʽ

	// 2*QWORD����������
	L_dq,

	// 32λ��48λ����80λ��ָ�룬ȡ���ڲ�������С���ԡ�
	L_p,

	// 128λ��256λ����˫���ȸ�������
	L_pd,

	// QWORD MMX�Ĵ�������mm0��
	L_pi,  // ֻ�������RM��Ѱַ��ʽ

	// 128λ��256λ���������ȸ�������
	L_ps,

	// QWORD����������
	L_q,

	// 4*QWORD��256λ������������
	L_qq,

	// 6�ֽڻ�10�ֽڵ�α������
	L_s,

	// 128λ˫���ȸ������ı���Ԫ��
	L_sd,

	// 128λ�����ȸ������ı���Ԫ��
	L_ss,

	// DWORD�����Ĵ�������eax��
	L_si,  // û��ʹ�ã�Ϊʲô��

	// WORD��DWORD��QWORD��64λ����ȡ������
	L_v,

	// WORD����������
	L_w,

	// ����dq��qq�Ĳ�������С����
	L_x,

	// DWORD��QWORD��ȡ��������
	L_y,

	// 16λ��СʱΪWORD��32λ��64λ��СʱΪDWORD
	L_z,

	// AddressingMethods Ѱַ��ʽ
	H_1,  // ��֪����ʲô

	// ֱ��Ѱַ����ָ��û��ModR/M�ֽڣ��������ĵ�ַ��������ָ���С�
	// û�л�ַ�Ĵ�������ַ�Ĵ�����Ҳû�б�����������Ӧ�á�
	H_A,  // ֻ�����p

	// ��VEXǰ׺��VEX.vvvv�ֶα�ʾһ��ͨ�üĴ���
	H_B,  // ֻ�����y

	// ��ModR/M�ֽڵ�reg���ʾ���ƼĴ���
	H_C,  // ֻ�����d

	// ��ModR/M�ֽڵ�reg���ʾ���ԼĴ���
	H_D,  // ֻ�����d

	// һ��ModR/M�ֽڸ���Opcode֮��ָ�������������������������ͨ�üĴ������ڴ��ַ��
	// ��������ڴ��ַ���õ�ַ�öμĴ����������κ�ֵ����ַ�Ĵ�������ַ�Ĵ���������������λ�����������
	H_E,

	// EFLAGS/RFLAGS �Ĵ���
	H_F,  // ֻ�����v

	// ��ModR/M�ֽڵ�reg���ʾͨ�üĴ���
	H_G,

	// ��VEXǰ׺��VEX.vvvv�ֶ�ѡ��һ��128λ��XMM�Ĵ�����256λ��YMM�Ĵ�����ȡ���ڲ��������͡�
	// ���ھɰ�SSE�������������������
	H_H,

	// ������
	H_I,

	// ��ָ�����һ�����ָ��ָ��Ĵ�����ƫ��
	H_J,

	// 8λ�������ĸ�4λ������ʾ128λ��XMM�Ĵ�����256λ��YMM�Ĵ�����ȡ���ڲ��������ͣ���32λģʽ�º���MSB��
	H_L,  // ֻ�����x

	// ModR/M�ֽڿ���ֻ�����ڴ�(����, BOUND, LES, LDS, LSS, LFS, LGS,CMPXCHG8B)
	H_M,

	// ModR/M�ֽڵ�R/M���ʾһ������4��MMX�Ĵ���
	H_N,  // ֻ�����q

	// ��ָ��û��ModR/M�ֽڡ���������ƫ�Ʊ�����Ϊ�ֻ�˫��(ȡ���ڵ�ַ��С����)��
	// û�л�ַ�Ĵ�������ַ�Ĵ����������������Ӧ�á�
	H_O,

	// ModR/M�ֽڵ�reg���ʾһ������4��MMX�Ĵ���
	H_P,

	// һ��ModR/M�ֽڸ���Opcode֮��ָ�������������������������MMX�Ĵ������ڴ��ַ��
	// ������ڴ��ַ���õ�ַ�öμĴ����������κ�ֵ����ַ�Ĵ�������ַ�Ĵ���������������λ�����������
	H_Q,

	// ModR/M�ֽڿ���ֻ����ͨ�üĴ���
	H_R,

	// ModR/M�ֽڵ�reg���ʾһ���μĴ���
	H_S,  // ֻ�����w

	// ModR/M�ֽڵ�R/M���ʾ128λ��XMM�Ĵ�����256λ��YMM�Ĵ�����ȡ���ڲ���������
	H_U,

	// ModR/M�ֽڵ�reg���ʾ128λ��XMM�Ĵ�����256λ��YMM�Ĵ�����ȡ���ڲ���������
	H_V,

	// һ��ModR/M�ֽڸ���Opcode֮��ָ��������������������Ϊһ��128λ��XMM�Ĵ�����256λ��YMM�Ĵ�����ȡ���ڲ��������ͣ����ڴ��ַ��
	// ������ڴ��ַ���õ�ַ�öμĴ����������κ�ֵ����ַ�Ĵ�������ַ�Ĵ���������������λ�����������
	H_W,

	// �ڴ�ѰַΪDS:rSI�Ĵ�����
	H_X,
	// �ڴ�ѰַΪES:rDI�Ĵ�����
	H_Y,

	// ���⣬�Ĵ������������С�������
	// ����eAX��16��AX����32λ��EAX�����֣�rAX����ΪAX��16����EAX��32����RAX��64��
	// ��REX.B�����ڸı�opcode��reg��ʱ��ʹ�� /xxx ��ʾ�������
	SPC_AL_R8L,
	SPC_CL_R9L,
	SPC_DL_R10L,
	SPC_BL_R11L,
	SPC_AH_R12L,
	SPC_CH_R13L,
	SPC_DH_R14L,
	SPC_BH_R15L,
	SPC_AL_rAX,
	SPC_rAX_r8,
	SPC_rCX_r9,
	SPC_rDX_r10,
	SPC_rBX_r11,
	SPC_rSP_r12,
	SPC_rBP_r13,
	SPC_rSI_r14,
	SPC_rDI_r15,

	SPC_RAX_EAX_R8_R8D,
	SPC_RCX_ECX_R9_R9D,
	SPC_RDX_EDX_R10_R10D,
	SPC_RBX_EBX_R11_R11D,
	SPC_RSP_ESP_R12_R12D,
	SPC_RBP_EBP_R13_R13D,
	SPC_RSI_ESI_R14_R14D,
	SPC_RDI_EDI_R15_R15D,

	SPC_Ib_Iz,
	SPC_Mw_Rv,
	SPC_Rd_Mb,
	SPC_Rd_Mw,
	SPC_Rv_Mw,
	SPC_Ry_Mb,
	SPC_Ry_Mw,
	SPC_Udq_Md,
	SPC_Ux_Md,
	SPC_Ux_Mq,
	SPC_Ux_Mw,

	// ��ʾ�Ĵ�������(�ַ���)�����ų����޶��ı�
	// �������Ϻ���REG�õı�ʶ
	CHANGE_REG,

	// SPL,BPL,SIL,DIL��Len_8���ȣ���ҪREXǰ׺�����滻��ah��ch��dh��bh��
	// ʹ�ó��ȸ�ֵ���������������,���������ʡ�ռ�
	// ע���С��ת����Ҫ���ǵ�����
	REG_SPL = _REG(8, Len_64_MM),
	REG_BPL = _REG(9, Len_64_MM),
	REG_SIL = _REG(10, Len_64_MM),
	REG_DIL = _REG(11, Len_64_MM),
	// ����
	REG_X12 = _REG(12, Len_64_MM),
	REG_X13 = _REG(13, Len_64_MM),
	REG_X14 = _REG(14, Len_64_MM),
	REG_X15 = _REG(15, Len_64_MM),

	// reg
	REG_AL = _REG(0, Len_8),
	REG_AX = _REG(0, Len_16),
	REG_EAX = _REG(0, Len_32),
	REG_RAX = _REG(0, Len_64),
	REG_MM0 = _REG(0, Len_64_MM),
	REG_XMM0 = _REG(0, Len_128_XMM),
	REG_CL = _REG(1, Len_8),
	REG_CX = _REG(1, Len_16),
	REG_ECX = _REG(1, Len_32),
	REG_RCX = _REG(1, Len_64),
	REG_MM1 = _REG(1, Len_64_MM),
	REG_XMM1 = _REG(1, Len_128_XMM),
	REG_DL = _REG(2, Len_8),
	REG_DX = _REG(2, Len_16),
	REG_EDX = _REG(2, Len_32),
	REG_RDX = _REG(2, Len_64),
	REG_MM2 = _REG(2, Len_64_MM),
	REG_XMM2 = _REG(2, Len_128_XMM),
	REG_BL = _REG(3, Len_8),
	REG_BX = _REG(3, Len_16),
	REG_EBX = _REG(3, Len_32),
	REG_RBX = _REG(3, Len_64),
	REG_MM3 = _REG(3, Len_64_MM),
	REG_XMM3 = _REG(3, Len_128_XMM),
	REG_AH = _REG(4, Len_8),
	REG_SP = _REG(4, Len_16),
	REG_ESP = _REG(4, Len_32),
	REG_RSP = _REG(4, Len_64),
	REG_MM4 = _REG(4, Len_64_MM),
	REG_XMM4 = _REG(4, Len_128_XMM),
	REG_CH = _REG(5, Len_8),
	REG_BP = _REG(5, Len_16),
	REG_EBP = _REG(5, Len_32),
	REG_RBP = _REG(5, Len_64),
	REG_MM5 = _REG(5, Len_64_MM),
	REG_XMM5 = _REG(5, Len_128_XMM),
	REG_DH = _REG(6, Len_8),
	REG_SI = _REG(6, Len_16),
	REG_ESI = _REG(6, Len_32),
	REG_RSI = _REG(6, Len_64),
	REG_MM6 = _REG(6, Len_64_MM),
	REG_XMM6 = _REG(6, Len_128_XMM),
	REG_BH = _REG(7, Len_8),
	REG_DI = _REG(7, Len_16),
	REG_EDI = _REG(7, Len_32),
	REG_RDI = _REG(7, Len_64),
	REG_MM7 = _REG(7, Len_64_MM),
	REG_XMM7 = _REG(7, Len_128_XMM),

	REG_R8L = _REG(8, Len_8),
	REG_R8W = _REG(8, Len_16),
	REG_R8D = _REG(8, Len_32),
	REG_R8 = _REG(8, Len_64),
	REG_XMM8 = _REG(8, Len_128_XMM),
	REG_R9L = _REG(9, Len_8),
	REG_R9W = _REG(9, Len_16),
	REG_R9D = _REG(9, Len_32),
	REG_R9 = _REG(9, Len_64),
	REG_XMM9 = _REG(9, Len_128_XMM),
	REG_R10L = _REG(10, Len_8),
	REG_R10W = _REG(10, Len_16),
	REG_R10D = _REG(10, Len_32),
	REG_R10 = _REG(10, Len_64),
	REG_XMM10 = _REG(10, Len_128_XMM),
	REG_R11L = _REG(11, Len_8),
	REG_R11W = _REG(11, Len_16),
	REG_R11D = _REG(11, Len_32),
	REG_R11 = _REG(11, Len_64),
	REG_XMM11 = _REG(11, Len_128_XMM),
	REG_R12L = _REG(12, Len_8),
	REG_R12W = _REG(12, Len_16),
	REG_R12D = _REG(12, Len_32),
	REG_R12 = _REG(12, Len_64),
	REG_XMM12 = _REG(12, Len_128_XMM),
	REG_R13L = _REG(13, Len_8),
	REG_R13W = _REG(13, Len_16),
	REG_R13D = _REG(13, Len_32),
	REG_R13 = _REG(13, Len_64),
	REG_XMM13 = _REG(13, Len_128_XMM),
	REG_R14L = _REG(14, Len_8),
	REG_R14W = _REG(14, Len_16),
	REG_R14D = _REG(14, Len_32),
	REG_R14 = _REG(14, Len_64),
	REG_XMM14 = _REG(14, Len_128_XMM),
	REG_R15L = _REG(15, Len_8),
	REG_R15W = _REG(15, Len_16),
	REG_R15D = _REG(15, Len_32),
	REG_R15 = _REG(15, Len_64),
	REG_XMM15 = _REG(15, Len_128_XMM),
	// ��223
	REG_END = REG_XMM15,
	// Segs
	// ��SEG_XX��˳�����,��Ҫ��һЩ�������ȡ���ַ���
	SEG_XX = 250,
	SEG_CS = SEG_XX,
	SEG_DS = SEG_XX + 1,
	SEG_ES = SEG_XX + 2,
	SEG_FS = SEG_XX + 3,
	SEG_GS = SEG_XX + 4,
	SEG_SS = SEG_XX + 5,
};

enum OpcodeType :unsigned char
{
	OT_None,
	OT_Inst,  //  ��ָͨ��
	OT_Inst_Change,  //  ���ݳ����޸�ָ������ָ��
	OT_Prefix,

	OT_Grp,
	OT_Table_0F,
	OT_Table_0F38,
	OT_Table_0F3A,
	OT_Esc
};

enum PrefixGroup :unsigned char
{
	PfxGrp_1 = 1,
	PfxGrp_2,
	PfxGrp_3,
	PfxGrp_4,
	PfxGrp_Rex,
	// Instructions that include a VEX prefix are organized relative to the 2-byte and 3-byte opcode maps, 
	// based on the VEX.mmmmm field encoding of implied 0F, 0F38H, 0F3AH, respectively. 
	// Each entry in the opcode map of a VEX-encoded instruction is based on the value of the opcode byte, 
	// similar to non-VEX-encoded instructions.
	// A VEX prefix includes several bit fields that encode implied 66H, F2H, F3H prefix functionality(VEX.pp) 
	// and operand size / opcode information(VEX.L).See chapter 4 for details.
	// Opcode tables A2 - A6 include both instructions with a VEX prefix and instructions without a VEX prefix.
	// Many entries are only made once, but represent both the VEX and non - VEX forms of the instruction.
	// If the VEX prefix is present all the operands are valid and the mnemonic is usually prefixed with a ��v��.
	// If the VEX prefix is not present the VEX.vvvv operand is not available and the prefix ��v�� is dropped from the mnemonic.
	// A few instructions exist only in VEX form and these are marked with a superscript ��v��.
	// Operand size of VEX prefix instructions can be determined by the operand type code. 
	// 128 - bit vectors are indicated by 'dq', 256 - bit vectors are indicated by 'qq', 
	// and instructions with operands supporting either 128 or 256 - bit,
	// determined by VEX.L, are indicated by 'x'.
	// For example, the entry "VMOVUPD Vx,Wx" indicates both VEX.L = 0 and VEX.L = 1 are supported.
	PfxGrp_Vex,
	PfxGrp_End
};
enum Prefix :unsigned char
{
	Rex = 0x40,
	Rex_B = 0x41,
	Rex_X = 0x42,
	Rex_XB = 0x43,
	Rex_R = 0x44,
	Rex_RB = 0x45,
	Rex_RX = 0x46,
	Rex_RXB = 0x47,
	Rex_W = 0x48,
	Rex_WB = 0x49,
	Rex_WX = 0x4a,
	Rex_WXB = 0x4b,
	Rex_WR = 0x4c,
	Rex_WRB = 0x4d,
	Rex_WRX = 0x4e,
	Rex_WRXB = 0x4f,
	Vex_2Byte = 0xC4,
	Vex_1Byte = 0xC5,
	G4_address_size = 0x67,
	G1_lock = 0xf0,
	G3_operand_size = 0x66,
	G1_repne_xacquire = 0xf2,
	G1_reprepe_xrelease = 0xf3,
	G2_seg_cs = 0x2e,
	G2_seg_ds = 0x3e,
	G2_seg_es = 0x26,
	G2_seg_fs = 0x64,
	G2_seg_gs = 0x65,
	G2_seg_ss = 0x36,
};
enum OpcodeGroup :unsigned char
{
	Grp_1 = 1,  // _80x83
	Grp_1A,  // _8F
	Grp_2,  // _C0C1_D0D1_D2D3,
	Grp_3,  // _F6F7,
	Grp_4,  // _FE,
	Grp_5,  // _FF,
	Grp_6,  // _0F00,
	Grp_7,  // _0F01,
	Grp_8,  // _0FBA,
	Grp_9,  // _0FC7,
	Grp_10,  // _0FB9,
	Grp_11_C6,
	Grp_11_C7,
	Grp_12,  // _0F71,
	Grp_13,  // _0F72,
	Grp_14,  // _0F73,
	Grp_15,  // _0FAE,
	Grp_16,  // _0F18,
	Grp_17,  // _VEX_0F38_F3
};


// ָ���������
enum PrefixCondition :unsigned char
{
	C_None,
	C_66 = 1,
	C_F2 = 1 << 1,
	C_F3 = 1 << 2,
	/*C_x32,
	C_x64*/
};

enum Mod210Condition :unsigned char
{
	C_Mod_210_000 = 1,
	C_Mod_210_001,
	C_Mod_210_010,
	C_Mod_210_011,
	C_Mod_210_100,
	C_Mod_210_101,
	C_Mod_210_110,
	C_Mod_210_111,
};
enum Mod76Condition :unsigned char
{
	C_Mod_76_mem = 1,
	C_Mod_76_11B,
	C_Mod_76_mem_11B
};

enum Superscript :unsigned char
{
	// S_None,
	// S_1A ,  // ModRM3-5Ϊ��չ������,�������ϱ�
	S_1B = 1,  // ʹ��0F0B�����루UD2ָ���0FB9H������ʱ������������Ч�Ĳ������쳣��#UD����
	S_1C,  // ��Щָ��ʹ����ͬ�������ֽ��롣�����ָ���б仯�����߲������ʾ��ͬ��ָ���MODR/ M�ֽڽ��������ָ�ָ�

	// ����
	S_i64,  // ��64λ�Ƿ���δ���룬40-4f��64λ����REXǰ׺��ʹ��FE/FF/Grp4 5����inc/dec
	S_o64,  // ��64λ����

	S_d64,  // ��64λ�в�����Ĭ��64λ�����ܱ���32λ����
	S_f64,  // 64λʱ������ǿ��64λ���������ߴ�ǰ׺��64λ����Ч

	S_v,  // ֻ����vex��ʽ��û�оɵ�SSEָ����ʽ����������GPRָ������ʾVEXǰ׺
	S_v1,  // �����ܴ����ݴ�С�ƶ�ʱ��ֻ����VEX128��SSE��ʽ��û��VEX256��
};

// ���ֺ�׺
enum NameExt :unsigned char
{
	Ext_None = 0,
	Ext_B = 1,
	Ext_W = Ext_B << 1,
	Ext_D = Ext_W << 1,
	Ext_Q = Ext_D << 1
};

#pragma pack(push, 1)
// 1b\2b ����Ԫ�ؽṹ,Count��ʾ��ѡ���ָ������0��ʾָ�����
struct OpcodeData
{
	unsigned short Hex_InstIndex : 12;
	unsigned short Count : 4;
};
// 3b ����Ԫ�ؽṹ
struct ZipOpcodeData
{
	unsigned short Hex_InstIndex : 12;
	unsigned short Count : 4;
	unsigned char Index;  // OpcodeData�±�
};

// hex��inst�Ĺ�ϵ��Ԫ��
struct Hex_Inst
{
	unsigned short Type : 6;
	unsigned short InstIndex : 10;

};

// ע������InstData��InstChangeData�Ĳ���˳������ʹ�С������ͬ��
// �ڲ���Ҫʹ��ָ�����ĳ��Ͽ��԰����ǵ���ͬһ����
struct InstData
{
	unsigned char Pfxcdt : 4;  // ǰ׺����PrefixCondition
	unsigned char Ss : 4;  // Superscript
	unsigned char ParamID;
	unsigned short ParamCount : 3;
	unsigned short NameCount : 3;
	unsigned short NameID : 10;
	// unsigned char Ext:4; // Inst_Change ��������NameExt
};
struct InstChangeData
{
	unsigned char Pfxcdt : 4;  // ǰ׺����PrefixCondition
	unsigned char Ss : 4;  // Superscript
	unsigned char ParamID;
	unsigned short ParamCount : 3;
	unsigned short NameCount : 3;
	unsigned short NameID : 10;
	unsigned char Ext : 4;   // Inst_Change ��������NameExt
};
struct PrefixInstData
{
	unsigned short Ss : 4;  // Superscript
	unsigned short PfxGrp : 3;
	unsigned short NameID : 9;  // prefix ���ֿ�ǰ����9λ�㹻
};

struct GrpInstData
{
	unsigned char Ss : 4;  // Superscript
	unsigned char : 4;
	unsigned char ParamID;
	unsigned char ParamCount : 3;
	unsigned char GrpID : 5;
};
typedef struct
{
	BYTE Rm : 3;
	BYTE Reg : 3;
	BYTE Mod : 2;
}OpcodeModRM, *POpcodeModRM;
#pragma pack(pop)
