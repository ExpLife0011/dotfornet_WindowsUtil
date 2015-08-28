#pragma once
#include <cassert>
#include "..\Process\LazyLoad\LazyLoadSystemApi.h"
namespace Asm
{

#ifndef _WIN64
#endif
	enum class Registers
	{
		// ���ֽ�
		al,
		bl,
		cl,
		dl,
		ah,
		bh,
		ch,
		dh,
		// 64
		r8b,
		r9b,
		r10b,
		r11b,
		r12b,
		r13b,
		r14b,
		r15b,

		// �ֽ�
		ax,
		bx,
		cx,
		dx,
		si,
		di,
		bp,
		sp,
		// 64
		r8w,
		r9w,
		r10w,
		r11w,
		r12w,
		r13w,
		r14w,
		r15w,

		// ˫�ֽ�
		eax,
		ebx,
		ecx,
		edx,
		esi,
		edi,
		ebp,
		esp,
		// 64
		r8d,
		r9d,
		r10d,
		r11d,
		r12d,
		r13d,
		r14d,
		r15d,

		// ���ֽ� 64
		rax,
		rbx,
		rcx,
		rdx,
		rsi,
		rdi,
		rbp,
		rsp,
		r8,
		r9,
		r10,
		r11,
		r12,
		r13,
		r14,
		r15
	};


	class AsmGenerator
	{
		PUINT8 binBuff;
		bool isGenerated;
		DWORD buffSize;
		PUINT8 oldCur;
		PUINT8 writeCur; // binд���α�
		PUINT8 endBuff;

		template<typename T>
		void Write(T val);

		void SaveCur(OUT PVOID* save);
		//AsmGenerator& __stdcall OneByteCmd(UINT8 cmdCode, OUT PVOID* currentCodeAddr);
	public:
		AsmGenerator(PVOID buff,DWORD size); // ��������һ����������д�����
		~AsmGenerator();
		bool IsGeneratedSuccess();// ��ʾ�Ƿ�ɹ�����
		template<typename T>
		T GetCode();
		DWORD CodeSize();
		bool SetWriteCur(PVOID addr); // �����α�λ��, Խ�緵��false, �����α����ڱ߽�ֵ
		bool MoveWriteCur(DWORD addr);// �ƶ��α�λ��, Խ�緵��false, �����α����ڱ߽�ֵ
		const PUINT8 CurrCur();
		const PUINT8 PrevCur();

		// ������Ҫʵ�ֵľ�̫����
		//// ��ת��������
		//AsmGenerator& __stdcall Jmp_Address(DWORD address, OUT PVOID* currentCodeAddr = NULL);
		//AsmGenerator& __stdcall Jmp_Short_Address(INT8 pos, OUT PVOID* currentCodeAddr = NULL);

		//// push ������
		//AsmGenerator& __stdcall Push_Value(DWORD value, OUT PVOID* currentCodeAddr = NULL);
		//// valueС��0Ϊret,����Ϊret value
		//AsmGenerator& __stdcall Retn(SHORT value = -1, OUT PVOID* currentCodeAddr = NULL);
		//
		//AsmGenerator& __stdcall Pushad(OUT PVOID* currentCodeAddr = NULL);

		//AsmGenerator& __stdcall Cld(OUT PVOID* currentCodeAddr = NULL);
		//// mov �Ĵ���,������
		//AsmGenerator& __stdcall Mov_Reg_Value(OUT PVOID* currentCodeAddr = NULL);

		//AsmGenerator& __stdcall Nop(OUT PVOID* currentCodeAddr = NULL);

		template<typename T>
		AsmGenerator& __stdcall Emit(T val, OUT PVOID* currentCodeAddr = NULL);

		template<typename T>
		AsmGenerator& __stdcall operator<<(T val);
	};
}
